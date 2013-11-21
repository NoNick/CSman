#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>

class Player
{
public:
    Player();

private:
    std::pair <double, double> pos, mov;
    std::pair <int, int> size;
    std::vector <std::string> texture;
    int hp, melee, ranged;
};

#endif // PLAYER_H
