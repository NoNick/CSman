#include "state.h"
#include "levelmap.h"
#include "mapBlock.h"
#include "pellet.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

State::State() {
    Player p = Player("./player", std::make_pair(0, 0));
    players.push_back(p);
    loadMobs("./mobs");

}

void State::setLevelMap(LevelMap *map) {
    m = map;
}

void State::loadMobs(const char *path) {
    /* read mobs data in following format:
     * (num of mobs)
     * for i = 0 to (num of mobs):
     *     (mob's player file) (num of points in its path)
     *     for j = 0 to (num of points in its path):
     *         (point x) (point y)
     */

    srand(time(NULL));
    std::ifstream fin(path);
    std::string s;
    pathState tmp;
    std::pair <int, int> tmp2;
    int n, m;
    fin >> n;
    for (int i = 0; i < n; i++) {
        tmp.path.clear();
        fin >> s >> m;
        for (int j = 0; j < m; j++) {
            fin >> tmp2.first >> tmp2.second;
            tmp.path.push_back(tmp2);
        }

        if (m > 0) {
            tmp.isOnPath = true;
            tmp.pathIndex = rand() % m;
            tmp.isActive = false;
            players.push_back(Player(s.c_str(), tmp.path[tmp.pathIndex]));
            mob.push_back(tmp);
        }
    }
}

void State::throwPellet(Player *p) {
    Pellet pel(p->pelletPath.c_str());
    pel.parent = p;
    if (p->right) {
        pel.pos = std::make_pair(p->pos.first + p->size.first,
                             p->pos.second + p->size.second / 2);
    }
    else {
        pel.pos = std::make_pair(p->pos.first,
                                 p->pos.second + p->size.second / 2);
        pel.mov.first *= -1;
    }
    pel.timeLeft = pel.timeLeftMax;
    pellets.push_back(pel);
}

bool State::isOnBlock(Player *p) {
    int y = p->pos.second + p->size.second, x1 = p->pos.first,
        x2 = p->pos.first + p->size.first;
    mapBlock b;
    Player pl;

    for (unsigned int i = 0; i < m->blocks.size(); i++) {
        b = m->blocks[i];
        if (b.begin.second == y &&
           (std::min(b.begin.first, b.end.first) <= x2 &&
            std::max(b.begin.first, b.end.first) >= x1))
            return true;
    }
    for (unsigned int i = 0; i < players.size(); i++) {
        pl = players[i];
        if (p->pos.first != pl.pos.first || p->pos.second != pl.pos.second) {
            if ((int)pl.pos.second == y && (int)pl.pos.first <= x2 &&
               (int)pl.pos.first + pl.size.first >= x1)
                return true;
        }
    }


    return false;
}

bool State::isUnderBlock(Player *p) {
    int y = p->pos.second, x1 = p->pos.first,
        x2 = p->pos.first + p->size.first;
    mapBlock b;
    Player pl;

    for (unsigned int i = 0; i < m->blocks.size(); i++) {
        b = m->blocks[i];
        if (b.end.second == y + 1 &&
           (std::min(b.begin.first, b.end.first) <= x2 &&
            std::max(b.begin.first, b.end.first) >= x1))
            return true;
    }

    for (unsigned int i = 0; i < players.size(); i++) {
        pl = players[i];
        if (p->pos.first != pl.pos.first || p->pos.second != pl.pos.second) {
            if ((int)pl.pos.second + pl.size.second == y + 1 && (int)pl.pos.first <= x2 &&
                (int)pl.pos.first + pl.size.first >= x1)
                return true;
        }
    }

    return false;
}

bool State::isBlockBeside(Player *p) {
    int y1 = p->pos.second, y2 = p->pos.second + p->size.second,
        x1 = p->pos.first, x2 = p->pos.first + p->size.first;
    mapBlock b;
    Player pl;

    for (unsigned int i = 0; i < m->blocks.size(); i++) {
        b = m->blocks[i];
        if ((std::min(b.begin.second, b.end.second) < y2 &&
             std::max(b.begin.second, b.end.second) > y1) &&
           (std::min(b.begin.first, b.end.first) <= x2 &&
            std::max(b.begin.first, b.end.first) >= x1))
            return true;
    }

    for (unsigned int i = 0; i < players.size(); i++) {
        pl = players[i];
        if (p->pos.first != pl.pos.first || p->pos.second != pl.pos.second) {
            if (((int)pl.pos.second < y2 && (int)pl.pos.second + pl.size.second > y1) &&
               ((int)pl.pos.first <= x2 && (int)pl.pos.first + pl.size.first >= x1))
                return true;
        }
    }

    return false;
}

void State::move(std::pair<double, double> d) {
    if (isOnBlock(&players[0]) || players[0].goLng > 0) {
        if (players[0].goLng > 0)
            players[0].goLng--;

        players[0].pos.first += d.first * players[0].mov.first;
        if (players[0].pos.first < 0)
            players[0].pos.first = 0;

        if (isBlockBeside(&players[0]))
            players[0].pos.first -= d.first * players[0].mov.first;
    }
}

void State::jump(int playerID) {
    if (isOnBlock(&players[playerID])) {
        players[playerID].jump = players[playerID].mov.second;
        players[playerID].goLng = players[playerID].jump;
    }
}

int sign(double a) {
    if (a > 0)
        return 1;
    if (a < 0)
        return -1;
    return 0;
}

// return true if need to erase this pellet
bool State::handlePellet(Pellet *p) {
    bool changeX = false, changeY = false;
    double x1 = p->pos.first, x2 = p->pos.first + p->size.first,
        y1 = p->pos.second, y2 = p->pos.second + p->size.second;

    mapBlock b;

    for (unsigned int i = 0; i < m->blocks.size(); i++) {
        b = m->blocks[i];

        if (!changeY) {
            // if block bottom
            if ((double)b.begin.second >= y2 && (double)b.begin.second < (y2 + p->mov.second) &&
               (std::min(b.begin.first, b.end.first) <= x2 + p->mov.first &&
               std::max(b.begin.first, b.end.first) >= x1 + p->mov.first)) {
                if (sign(p->mov.second) == 1) {
                    // can't rotate Pi
                    if (p->mov.first == 0)
                        return true;

                    p->mov.second *= -1;
                    p->pos.second += p->mov.second - ((double)b.begin.second - y2);
                }
                changeY = true;
            }
            // if block up
            else if ((double)b.end.second <= y1 && (double)b.end.second > (y1 + p->mov.second) &&
                     (std::min(b.begin.first, b.end.first) <= x2 + p->mov.first &&
                      std::max(b.begin.first, b.end.first) >= x1 + p->mov.first)) {
                if (sign(p->mov.second) == -1) {
                    // can't rotate Pi
                    if (p->mov.first == 0)
                        return true;

                    p->mov.second *= -1;
                    p->pos.second += p->mov.second - (y1 - (double)b.end.second);
                }
                changeY = true;
            }
        }

        if (!changeX) {
            // if block left
            if ((std::min(b.begin.second, b.end.second) <= y2 + p->mov.second &&
                 std::max(b.begin.second, b.end.second) >= y1 + p->mov.second) &&
                 x1 >= (double)b.end.first && (x1 + p->mov.first) < (double)b.end.first) {
                if (sign(p->mov.first) == -1) {
                    // can't rotate Pi
                    if (p->mov.second == 0)
                        return true;

                    p->mov.first *= -1;
                    p->pos.first += p->mov.first - (x1 - (double)b.end.first);
                }
                changeX = true;
            }
            // if block right
            if ((std::min(b.begin.second, b.end.second) <= y2 + p->mov.second &&
                 std::max(b.begin.second, b.end.second) >= y1 + p->mov.second) &&
                 x2 <= (double)b.begin.first && (x2 + p->mov.first) > (double)b.begin.first) {
                if (sign(p->mov.first) == 1) {
                    // can't rotate Pi
                    if (p->mov.second == 0)
                        return true;

                    p->mov.first *= -1;
                    p->pos.first += p->mov.first - ((double)b.begin.first - x2);
                }
                changeX = true;
            }
        }
    }

    if (!changeX)
        p->pos.first += p->mov.first;
    if (!changeY)
        p->pos.second += p->mov.second;
    p->timeLeft--;

    return false;
}

void State::setActive(int i, bool var){
    mob[i].isActive = var;
}

void State::gravity(Player *p) {
    if (!isOnBlock(p) && p->jump <= 0)
        p->pos.second += 1;

    if (p->jump > 0) {
        p->pos.second--;
        p->jump--;
        if (isUnderBlock(p) || p->pos.second <= 0) {
            p->pos.second++;
            p->jump = 0;
        }
    }
}

void State::tic() {
    gravity(&players[0]);
    for (unsigned int i = 0; i < players.size() - 1; i++) {
        if (mob[i].isActive) {
            // TODO: chase player if can see him
            // TODO: find path if mob isn't on it
            // TODO: find path if mob can't go
            if (mob[i].isOnPath) {
                players[i + 1].pos = mob[i].path[(mob[i].pathIndex + 1) % mob[i].path.size()];
                if (!isBlockBeside(&players[i + 1])) {
                    if (mob[i].path[mob[i].pathIndex].first - players[i + 1].pos.first < 0)
                        players[i + 1].right = true;
                    else if (mob[i].path[mob[i].pathIndex].first - players[i + 1].pos.first > 0)
                        players[i + 1].right = false;

                    mob[i].pathIndex++;
                    mob[i].pathIndex %= mob[i].path.size();
                }
                else
                    players[i + 1].pos = mob[i].path[mob[i].pathIndex];
            }
        }
    }

    for (unsigned int i = 0; i < pellets.size(); i++) {
        if (handlePellet(&pellets[i]) | pellets[i].timeLeft <= 0) {
            pellets.erase(pellets.begin() + i);
            i--;
        }
    }
}
