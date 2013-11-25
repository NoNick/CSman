#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>

class Player
{
public:
    Player(const char *path, std::pair <double, double> p);
    std::pair <double, double> pos, mov;
    std::pair <int, int> size;
    std::vector < std::vector <std::string> > texture;
    int hp, melee, ranged, nFrames, jump;
};

#endif // PLAYER_H
