#include "player.h"
#include <fstream>
#include <iostream>

Player::Player() {
}

Player::Player(const char *path, std::pair <double, double> p)
{
    /* Read player data in following format:
     * (hp) (melee damage) (ranged damage) (movement speed x) (height of jump/num of movements in jump)
     * (path to pellet data file)
     * (number of animation frames) (width of frame) (height of frame)
     *
     * ...
     * (frames)
     * ...
     */

    pos = p;
    std::ifstream fin(path);
    fin >> hp >> melee >> ranged >> mov.first >> mov.second;
    char next;
    while(fin.get(next))
        if (next == '\n')
            break;
    std::getline(fin, pelletPath);
    fin >> nFrames >> size.first >> size.second;
    jump = 0;

    while(fin.get(next))
        if (next == '\n')
            break;

    std::vector <std::string> t;
    for (int i = 0; i < nFrames; i++)
        texture.push_back(t);
    std::string tmp;
    for (int i = 0; i < nFrames; i++) {
        for (int j = 0; j < size.second; j++) {
            std::getline(fin, tmp);
            texture[i].push_back(tmp);
        }
    }

    right = true;
}
