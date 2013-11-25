#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <vector>
#include "levelmap.h"
#include "draw.h"
#include "state.h"

class GC
{
public:
    GC(State *st, Draw *d, const char *texPath, const char *blockPath);
    void run();
    void setControl();

private:
    int getch();
    void handle(int c);
    void drawScene();
    LevelMap *m;
    State *state;
    Draw *draw;

    // area of sight
    std::pair <int, int> begin, end;

    // control queue
    std::vector <int> cq;

    int playerTact, worldTact;
};

#endif // GAMECONTROLLER_H
