#include "pellet.h"
#include <fstream>
#include <vector>
#include <string>

Pellet::Pellet()
{
}

Pellet::Pellet(const char *path) {
    /* read pellet data in the following format:
     * (movement speed x) (movement speed y)
     * (size x) (size y) (max existing time) (nFrames)
     * for i = 0 to nFrames - 1:
     *     for j = 0 to (size y) - 1:
     *          (texture string) */

    std::ifstream fin(path);
    fin >> mov.first >> mov.second >> size.first
        >> size.second >> timeLeftMax >> nFrames;

    char next;
    while(fin.get(next))
        if (next == '\n')
            break;

    for (int i = 0; i < nFrames; i++) {
        std::vector <std::string> tmp(size.second);
        for (int j = 0; j < size.second; j++)
            fin >> tmp[j];
        texture.push_back(tmp);
    }
}
