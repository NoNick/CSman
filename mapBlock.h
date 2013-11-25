#ifndef MAPBLOCK_H
#define MAPBLOCK_H
#include "texture.h"

struct mapBlock {
    mapBlock();
    mapBlock(std::pair <int, int> b, std::pair <int, int> e,
             double hp, texture *t);

    std::pair <int, int> begin, end;
    double hpBal;
    texture *tex;
};

#endif // MAPBLOCK_H
