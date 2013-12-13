#ifndef DRAW_H
#define DRAW_H
#include "drawBlock.h"
#include "status.h"

class Draw
{
public:
    // init with w colunms & h rows
    Draw(int w, int h);
    // set block into a buffer
    // there are a very instresting not-a-bug-but-a-feature:
    // if b.end < b.begin blocks will be drew reflected (various kinds of reflexion: (b.end.first < b.begin.second),
    // (b.end.first < b.begin.second), (b.end.first < b.begin.second && b.end.first < b.begin.second)
    // that's why you cannot use (for example) slash in player's textures: |\ ---> \| (symbols aren't reflecting)
    void setBlock(drawBlock b);
    // set data for status bar (TODO: status bar)
    void setStatus(Status s);
    // write all received data in stdout; clear block's buffer, DON'T clear status bar data
    void writeBuf();
    int height, width;

private:
    char **buf;
    void clearBuf();
    Status st;
};

#endif // DRAW_H
