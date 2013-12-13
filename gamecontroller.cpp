#include "gamecontroller.h"
#include "drawBlock.h"
#include "mapBlock.h"
#include "keys.cpp"
#include <termios.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <time.h>

//Game Controller
GC::GC(State *st, Draw *d, const char *texPath, const char *blockPath)
{
    draw = d;
    state = st;
    m = new LevelMap(texPath, blockPath);
    st->setLevelMap(m);
    begin = std::make_pair(0, 0);
    // temp
    end = std::make_pair(30, 30);
    playerTact = worldTact = 0;
}

void GC::handle(int c) {
    switch(c) {
    case RIGHT:
        state->move(std::make_pair(1, 0));
        state->players[0].right = true;
        break;
    case LEFT:
        state->move(std::make_pair(-1, 0));
        state->players[0].right = false;
        break;
    case SPACE:
        state->jump(0);
        break;
    case TAB:
        state->throwPellet(&state->players[0]);
        break;
    }
}

// send blocks (drawBlock) data into draw class
void GC::drawScene() {
    drawBlock out;
    mapBlock b;

    // let's draw mapBlocks!
    for (unsigned int i = 0; i < m->blocks.size(); i++) {
        b = m->blocks[i];
        if ((b.begin.first < end.first && b.begin.second < end.second) &&
                (b.end.first > begin.first && b.end.second > begin.second)) {
            out.begin = std::make_pair(std::max(b.begin.first - begin.first, 0), std::max(b.begin.second - begin.second, 0));
            out.end = std::make_pair(b.end.first - begin.first, b.end.second - begin.second);
            out.texture = b.tex->data;
            draw->setBlock(out);
        }
    }

    // let's draw pellets!
    Pellet p;
    for (unsigned int i = 0; i < state->pellets.size(); i++) {
        p = state->pellets[i];
        if (((int)p.pos.first < end.first && (int)p.pos.second < end.second) &&
                ((int)p.pos.first > begin.first && (int)p.pos.second > begin.second)) {
            out.begin = std::make_pair(std::max((int)p.pos.first - begin.first, 0), std::max((int)p.pos.second - begin.second, 0));
            out.end = std::make_pair((int)p.pos.first + p.size.first - begin.first, (int)p.pos.second + p.size.second - begin.second);
            out.texture = p.texture[worldTact % p.nFrames];
            draw->setBlock(out);
        }
    }

    // let's draw player & mobs!
    Player pl;
    for (unsigned int i = 0; i < state->players.size(); i++) {
        pl = state->players[i];
        if (((int)pl.pos.first < end.first && (int)pl.pos.second < end.second) &&
                ((int)pl.pos.first >= begin.first && (int)pl.pos.second >= begin.second)) {
            out.begin = std::make_pair((int)pl.pos.first - begin.first,
                                    (int)pl.pos.second - begin.second);
            out.end = std::make_pair(out.begin.first + pl.size.first,
                                    out.begin.second + pl.size.second);
            if (!pl.right) {
                int tmp = out.begin.first;
                out.begin.first = out.end.first;
                out.end.first = tmp;
            }

            if (i == 0)
                out.texture = pl.texture[playerTact];
            else
                out.texture = pl.texture[worldTact % state->players[i].texture.size()];
            draw->setBlock(out);
        }
    }

    draw->writeBuf();

    worldTact++;
}

void GC::run() {
    bool activity;
    while (cq.size() == 0 || (cq[0] != int('e') && cq[0] != int('q'))) {
        activity = false;
        // cq contains recieved from other thread data
        while (cq.size() > 0) {
            handle(cq[0]);
            cq.erase(cq.begin());
            activity = true;
        }

        // player changes texture only if he was moving
        if (activity) {
            playerTact++;
            playerTact %= state->players[0].texture.size();
        }
        state->tic();
        scroll();
        drawScene();
        usleep(100000);
    }

    std::cout << "\x1b[H\x1b[J";
}

// scroll map using setting offset (begin) and end of drawble area (end)
// player coords must be in center (begin + (end - begin) / 3; end - (end - begin) / 3)
//                                  OR
// end of drawble area is end of map OR begin of drawble area is begin of map
void GC::scroll() {
    std::pair <int, int> size = std::make_pair(end.first - begin.first, end.second - begin.second),
            player = std::make_pair((int)state->players[0].pos.first, (int)state->players[0].pos.second);

    if (player.first < begin.first + (end.first - begin.first) / 3) {
        begin.first = std::max(player.first - size.first / 3, 0);
        end.first = begin.first + size.first;
    }
    else if (player.first > end.first - (end.first - begin.first) / 3) {
        end.first = std::min(player.first + size.first / 3, m->mapEnd.first);
        begin.first = end.first - size.first;
    }

    if (player.second < begin.second + (end.second - begin.second) / 3) {
        begin.second = std::max(player.second - size.second / 3, 0);
        end.second = begin.second + size.second;
    }
    else if (player.second > end.second - (end.second - begin.second) / 3) {
        end.second = std::min(player.second + size.second / 3, m->mapEnd.second);
        begin.second = end.second - size.second;
    }
}

int GC::getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

// thread for getting controls from player
void GC::setControl() {
    int c;
    do {
        c = getch();
        cq.push_back(c);
    } while (c != int('q') && c != int('e'));
}
