#ifndef LEVELMAP_H
#define LEVELMAP_H
#include "block.cpp"
#include <vector>

class LevelMap
{
public:
    LevelMap();
    // get all blocks from [begin, end] rectangle
    std::vector <block> getBlocks(std::pair <int, int> begin, std::pair <int, int> end);

private:
    std::vector <block> blocks;
    void load(const char *path);
};

#endif // LEVELMAP_H
