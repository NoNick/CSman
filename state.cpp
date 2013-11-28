#include "state.h"
#include "levelmap.h"
#include "mapBlock.h"
#include <fstream>

State::State() {
    Player p = Player("./player", std::make_pair(0, 0));
    players.push_back(p);
    goLngMAX = 5;
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
        if (b.begin.second == y &&
           (std::min(b.begin.first, b.end.first) <= x2 &&
            std::max(b.begin.first, b.end.first) >= x1))
            return true;
    }

    return false;
}

bool State::isUnderBlock(Player p) {
    int y = (int)p.pos.second, x1 = (int)p.pos.first,
        x2 = (int)p.pos.first + p.size.first;
    mapBlock b;

    for (int i = 0; i < m->blocks.size(); i++) {
        b = m->blocks[i];
        if (b.end.second == y + 1 &&
           (std::min(b.begin.first, b.end.first) <= x2 &&
            std::max(b.begin.first, b.end.first) >= x1))
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
        if ((std::min(b.begin.second, b.end.second) < y2 &&
             std::max(b.begin.second, b.end.second) > y1) &&
           (std::min(b.begin.first, b.end.first) <= x2 &&
            std::max(b.begin.first, b.end.first) >= x1))
            return true;
    }

    return false;
}

void State::move(std::pair<double, double> d) {
    if (isOnBlock(players[0]) || goLng > 0) {
        if (goLng > 0)
            goLng--;

        players[0].pos.first += d.first * players[0].mov.first;
        if (players[0].pos.first < 0)
            players[0].pos.first = 0;

        if (isBlockBeside(players[0]))
            players[0].pos.first -= d.first * players[0].mov.first;
    }
}

void State::jump(int playerID) {
    if (isOnBlock(players[0])) {
        players[playerID].jump = players[playerID].mov.second;
        goLng = goLngMAX;
    }
}

void State::tic() {
    if (!isOnBlock(players[0]) && players[0].jump <= 0)
        players[0].pos.second += 1;

    if (players[0].jump > 0) {
        players[0].pos.second--;
        players[0].jump--;
        if (isUnderBlock(players[0]) || players[0].pos.second <= 0) {
            players[0].pos.second++;
            players[0].jump = 0;
        }
    }

}
