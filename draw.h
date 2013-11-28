#ifndef DRAW_H
#define DRAW_H
#include "drawBlock.h"
#include "status.h"

class Draw
{
public:
    Draw(int w, int h);
    void setBlock(drawBlock b);
    void setStatus(Status s);
    void writeBuf();

private:
    int height, width;
    char **buf;
    void clearBuf();
    Status st;
};

#endif // DRAW_H
