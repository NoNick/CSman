#ifndef STATE_H
#define STATE_H
#include "pellet.h"
#include "player.h"
#include "levelmap.h"
#include <vector>

class State
{
public:
    State();
    void move(std::pair <double, double> d);
    void jump(Player *player);
    void tic();
    void shoot(Player *shooter);
    void setLevelMap(LevelMap *map);

    std::vector <Player> players;
    std::vector <Pellet> pellets;

    LevelMap *m;

private:
    bool isOnBlock(Player p);
    bool isBlockBeside(Player p);
};

#endif // STATE_H
