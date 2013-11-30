#include "levelmap.h"
#include "texture.h"
#include "mapBlock.h"
#include <fstream>
#include <string>
#include <vector>

void LevelMap::loadTextures(const char *path) {
    /* Read textures in following format:
     * (num of textures)
     * for i in range(1, (num of textures)):
     *     (x length) (y length)
     *     for (j in range (1, (y length)):
     *         (some char) * (x length) time */

    std::ifstream fin(path);
    int n, sizeX, sizeY;
    std::vector <std::string> tex;
    std::string tmp;
    fin >> n;
    for (int i = 0; i < n; i++) {
        tex.clear();
        fin >> sizeX >> sizeY;

        char next;
        while(fin.get(next))
            if (next == '\n')
                break;

        for (int j = 0; j < sizeY; j++) {
            std::getline(fin, tmp);
            tex.push_back(tmp);
        }

        texs.push_back(texture(tex));
    }

}

void LevelMap::loadBlocks(const char *path) {
    /* Read textures in following format:
     * (num of blocks)
     * for i in range(1, (num of blocks)):
     *     (begin x) (begin y) (end x) (end y) (hpBal) (texture's ID)*/

    std::ifstream fin(path);
    int n, id;
    std::pair <int, int> begin, end;
    mapEnd = std::make_pair(0, 0);
    double hpBal;
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> begin.first >> begin.second >> end.first >> end.second >> hpBal >> id;
        if (end.first > mapEnd.first && end.second > mapEnd.second)
            mapEnd = end;
        blocks.push_back(mapBlock(begin, end, hpBal, &(texs[id])));
    }
    mapEnd.first++;
    mapEnd.second++;
}

LevelMap::LevelMap(const char *pathTex, const char *pathBlock)
{
    loadTextures(pathTex);
    loadBlocks(pathBlock);
}
