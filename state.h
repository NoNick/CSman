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
    void jump(int playerID);
    void tic();
    void shoot(Player *shooter);
    void setLevelMap(LevelMap *map);
    void throwPellet(Player *p);

    std::vector <Player> players;
    std::vector <Pellet> pellets;

    LevelMap *m;

private:
    bool isOnBlock(Player p);
    bool isUnderBlock(Player p);
    bool isBlockBeside(Player p);
    bool handlePellet(Pellet *p);
    int jumpLng, goLng, goLngMAX;
};

#endif // STATE_H
