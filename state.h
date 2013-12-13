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

    std::vector <Player> players;
    std::vector <Pellet> pellets;

    LevelMap *m;

private:
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
    // TODO: it's not working
    // calculate path from one point to another for player p using bfs
    std::vector < std::pair <int, int> > findPath(std::pair <int, int> source,
                                        std::pair <int, int> target, Player p);

    std::vector < std::vector <std::pair <int, int> > > mobPath, currPath;
    std::vector <int> mobPlace;
};

#endif // STATE_H
