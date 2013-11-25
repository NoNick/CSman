#include "draw.h"
#include "drawBlock.h"
#include <cmath>
#include <iostream>
#include <stdio.h>

Draw::Draw(int w, int h)
{
    width = w;
    height = h;
    buf = new char*[w];
    for (int i = 0; i < w; i++)
        buf[i] = new char[h];

    clearBuf();
}

int getN(int b, int e, int n) {
    int lng = (int)std::abs(b - e);
    n %= lng;
    if (b < e)
        return n;
    return lng - n - 1;
}

void Draw::clearBuf() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++)
            buf[i][j] = ' ';
    }

}

void Draw::setBlock(drawBlock b) {
    int w = 0, h = b.texture.size();
    if (h > 0)
        w = b.texture[0].size();
    char tmp;

    int lngX = std::abs(b.begin.first - b.end.first),
        lngY = std::abs(b.begin.second - b.end.second),
        sourceX = std::min(b.begin.first, b.end.first),
        sourceY = std::min(b.begin.second, b.end.second);

    for (int j = 0; j < lngY && sourceY + j < height; j++) {
        for (int i = 0; i < lngX && sourceX + i < width; i++) {
            tmp = b.texture[getN(b.begin.second, b.end.second, j) % h][getN(b.begin.first, b.end.first, i) % w];
            if (tmp != ' ')
                buf[sourceX + i][sourceY + j] = tmp;
        }
    }
}

void Draw::writeBuf() {
    std::cout << "\x1b[H";

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            std::cout << buf[i][j];
        }
        std::cout << std::endl;
    }

    clearBuf();
}
