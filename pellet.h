#ifndef PELLET_H
#define PELLET_H
#include <vector>
#include <string>

class Pellet
{
public:
    Pellet();
private:
    std::pair <double, double> pos, mov;
    std::pair <int, int> size;
    std::vector <std::string> texture;
    int damage;
};

#endif // PELLET_H
