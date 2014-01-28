#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>

// just a data type
class Player
{
public:
    Player();
    // p is initial position
    Player(const char *path, std::pair <double, double> p);
    std::pair <double, double> pos, mov;
    std::pair <int, int> size;
    std::vector < std::vector <std::string> > texture;
    std::string pelletPath;
    int hp, melee, ranged, nFrames, jump, goLng;
    // if player looks right
    bool right;
};

#endif // PLAYER_H
