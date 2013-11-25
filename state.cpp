#include "state.h"
#include "levelmap.h"
#include "mapBlock.h"

State::State() {
    Player p = Player("./player", std::make_pair(0, 0));
    players.push_back(p);
}

void State::setLevelMap(LevelMap *map) {
    m = map;
}

bool State::isOnBlock(Player p) {
    int y = (int)p.pos.second + p.size.second, x1 = (int)p.pos.first,
        x2 = (int)p.pos.first + p.size.first;
    mapBlock b;

    for (int i = 0; i < m->blocks.size(); i++) {
        b = m->blocks[i];
        if (b.begin.first == y &&
           (std::min(b.begin.second, b.end.second) <= x2 &&
            std::max(b.begin.second, b.end.second) >= x1))
            return true;
    }

    return false;
}

bool State::isBlockBeside(Player p) {
    int y1 = (int)p.pos.second, y2 = (int)p.pos.second + p.size.second,
        x1 = (int)p.pos.first, x2 = (int)p.pos.first + p.size.first;
    mapBlock b;

    for (int i = 0; i < m->blocks.size(); i++) {
        b = m->blocks[i];
        if ((std::min(b.begin.first, b.end.first) < y2 &&
             std::max(b.begin.first, b.end.first) > y1) &&
           (std::min(b.begin.second, b.end.second) <= x2 &&
            std::max(b.begin.second, b.end.second) >= x1))
            return true;
    }

    return false;
}

void State::move(std::pair<double, double> d) {
    players[0].pos.first += d.first * players[0].mov.first;
    if (players[0].pos.first < 0)
        players[0].pos.first = 0;

    if (isBlockBeside(players[0]))
        players[0].pos.first -= d.first * players[0].mov.first;
}

void State::tic() {
    if (!isOnBlock(players[0]))
        players[0].pos.second += 1;

}
