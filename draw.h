#ifndef DRAW_H
#define DRAW_H
#include "block.cpp"


class Draw
{
public:
    Draw(int h, int w);
    void setBlock(block b);
    void writeBuf();

private:
    int height, width;
};

#endif // DRAW_H
