#ifndef DRAW_H
#define DRAW_H
#include "drawBlock.h"

class Draw
{
public:
    Draw(int w, int h);
    void setBlock(drawBlock b);
    void writeBuf();

private:
    int height, width;
    char **buf;
    void clearBuf();
};

#endif // DRAW_H
