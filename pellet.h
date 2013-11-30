#ifndef PELLET_H
#define PELLET_H
#include <vector>
#include <string>
#include "player.h"

class Pellet
{
public:
    Pellet();
    Pellet(const char *path);
    Player *parent;
    std::pair <double, double> pos, mov;
    std::vector < std::vector <std::string> > texture;
    std::pair <int, int> size;
    int timeLeft, timeLeftMax, nFrames;
};

#endif // PELLET_H
