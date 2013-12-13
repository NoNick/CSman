#ifndef LEVELMAP_H
#define LEVELMAP_H
#include "mapBlock.h"
#include <vector>

class LevelMap
{
public:
    // init using pathTex & pathBlock files
    LevelMap(const char *pathTex, const char *pathBlock);
    // get all blocks from [begin, end] rectangle
    std::vector <mapBlock> getBlocks(std::pair <int, int> begin, std::pair <int, int> end);
    std::vector <mapBlock> blocks;
    std::vector <texture> texs;
    std::pair <int, int> mapEnd;

private:
    // load data, file format description inside
    void loadTextures(const char *path);
    // load data, file format description inside
    void loadBlocks(const char *path);
};

#endif // LEVELMAP_H
