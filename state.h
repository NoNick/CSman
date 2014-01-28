#ifndef STATE_H
#define STATE_H
#include "pellet.h"
#include "player.h"
#include "levelmap.h"
#include <vector>

// very very frightful class: all data are stored here & all calculations are doing here
class State
{
public:
    State();
    // move (if it possible) player on d vector: player.pos += d*player.move (player speed per tact) for each coordinate
    void move(std::pair <double, double> d);
    // init jump for player
    void jump(int playerID);
    // routine calculations for each tact
    void tic();
    // set enviroment (blocks)
    void setLevelMap(LevelMap *map);
    // p throws a new pellet (create a new pellet using player's data)
    void throwPellet(Player *p);

    // set mob (#i) active or inactive
    void setActive(int i, bool var);

    std::vector <Player> players;
    std::vector <Pellet> pellets;

    LevelMap *m;

private:
    struct pathState {
        // const path
        std::vector < std::pair <int, int> > path;
        // isActive is true if player can see object;
        // if isActive is true mob changes coordinates and might chase player
        // isOnPath is true if mob's coords is one of path vector
        bool isActive, isOnPath;
        // if isOnPath is true, path[pathIndex] is mob's position
        int pathIndex;
        // if isOnPath is false, player[i].pos is mob's position
    };

    // it's all about player & blocks positions
    bool isOnBlock(Player *p);
    bool isUnderBlock(Player *p);
    bool isBlockBeside(Player *p);
    // routine calculation for each tact for pellet
    bool handlePellet(Pellet *p);
    // load data
    void loadMobs(const char *path);
    // move player up/down (if he isn't on a block)
    // end player's jump if he's on a block
    void gravity(Player *p);

    std::vector <pathState> mob;
};

#endif // STATE_H
