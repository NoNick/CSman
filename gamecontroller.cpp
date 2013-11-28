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
        break;
    case LEFT:
        state->move(std::make_pair(-1, 0));
        break;
    case SPACE:
        state->jump(0);
        break;
    }
}

void GC::drawScene() {
    drawBlock out;
    mapBlock b;

    for (int i = 0; i < m->blocks.size(); i++) {
        b = m->blocks[i];
        if ((b.begin.first < end.first && b.begin.second < end.second) &&
                (b.end.first > begin.first && b.end.second > begin.second)) {
            out.begin = std::make_pair(std::max(b.begin.first - begin.first, 0), std::max(b.begin.second - begin.second, 0));
            out.end = std::make_pair(b.end.first - begin.first, b.end.second - begin.second);
            out.texture = b.tex->data;
            draw->setBlock(out);
        }
    }

    out.begin = std::make_pair((int)state->players[0].pos.first - begin.first,
                            (int)state->players[0].pos.second - begin.second);
    out.end = std::make_pair(out.begin.first + state->players[0].size.first,
                            out.begin.second + state->players[0].size.second);
    out.texture = state->players[0].texture[playerTact];
    draw->setBlock(out);

    draw->writeBuf();

    usleep(125000);
}

void GC::run() {
    bool activity;
    while (cq.size() == 0 || (cq[0] != int('e') && cq[0] != int('q'))) {
        activity = false;
        while (cq.size() > 0) {
            handle(cq[0]);
            cq.erase(cq.begin());
            activity = true;
        }

        if (activity) {
            playerTact++;
            playerTact %= state->players[0].texture.size();
        }
        state->tic();
        scroll();
        drawScene();
    }

    std::cout << "\x1b[H\x1b[J";
}

void GC::scroll() {
    std::pair <int, int> size = std::make_pair(end.first - begin.first, end.second - begin.second),
            player = std::make_pair((int)state->players[0].pos.first, (int)state->players[0].pos.second);

    if (player.first < begin.first + (end.first - begin.first) / 3) {
        begin.first = std::max(player.first - size.first / 3, 0);
        end.first = begin.first + size.first;
    }
    else if (player.first > end.first - (end.first - begin.first) / 3) {
        end.first = std::min(player.first + size.first / 3, 100);
        begin.first = end.first - size.first;
    }

    if (player.second < begin.second + (end.second - begin.second) / 3) {
        begin.second = std::max(player.second - size.second / 3, 0);
        end.second = begin.second + size.second;
    }
    else if (player.second > end.second - (end.second - begin.second) / 3) {
        end.second = std::min(player.second + size.second / 3, 100);
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

void GC::setControl() {
    int c;
    do {
        c = getch();
        cq.push_back(c);
    } while (c != int('q') && c != int('e'));
}
