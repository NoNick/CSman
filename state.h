#ifndef STATE_H
#define STATE_H
#include "pellet.h"
#include "player.h"
#include <vector>

class State
{
public:
    State();
    void move(std::pair <double, double> d);
    void jump(Player *player);
    void tic();
    void shoot(Player *shooter);

    std::vector <Player> players;
    std::vector <Pellet> pellets;
};

#endif // STATE_H
