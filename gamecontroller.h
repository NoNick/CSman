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
    // main exec cycle (main thread)
    void run();
    // thread for getting controls from player
    void setControl();

private:
    // linux version of windows.h function
    // TODO: need IFDEF WIN32/LINUX for windows compatibility
    int getch();
    // call functions depend on user input; keys stored in the keys.cpp file
    void handle(int c);
    // send blocks (drawBlock) data into draw class
    void drawScene();
    // scroll map using setting offset (begin) and end of drawble area (end)
    // player coords must be in center (begin + (end - begin) / 3; end - (end - begin) / 3)
    //                                  OR
    // end of drawble area is end of map OR begin of drawble area is begin of map
    void scroll();
    LevelMap *m;
    State *state;
    Draw *draw;

    // area of sight
    std::pair <int, int> begin, end;

    // control queue
    std::vector <int> cq;

    // player change texture (animation) only if he was moving
    // enemies and blocks are changing it all the time
    int playerTact, worldTact;
};

#endif // GAMECONTROLLER_H
