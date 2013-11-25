#ifndef LEVELMAP_H
#define LEVELMAP_H
#include "mapBlock.h"
#include <vector>

class LevelMap
{
public:
    LevelMap(const char *pathTex, const char *pathBlock);
    // get all blocks from [begin, end] rectangle
    std::vector <mapBlock> getBlocks(std::pair <int, int> begin, std::pair <int, int> end);
    std::vector <mapBlock> blocks;
    std::vector <texture> texs;

private:
    void loadTextures(const char *path);
    void loadBlocks(const char *path);
};

#endif // LEVELMAP_H
