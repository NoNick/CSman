#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <vector>
#include "levelmap.h"
#include "state.h"

class GC
{
public:
    GC();
    void run();
    void setControl();

private:
    int getch();
    void handle(int c);
    void drawScene();
    LevelMap m;
    State state;

    // area of sight
    std::pair <int, int> begin, end;

    // control queue
    std::vector <int> cq;

};

#endif // GAMECONTROLLER_H
