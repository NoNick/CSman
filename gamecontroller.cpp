#include "gamecontroller.h"
#include <termios.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include "keys.cpp"
#include "state.h"

//Game Controller
GC::GC(State st)
{
    state = st;
}

void GC::handle(int c) {
    switch(c) {
    case UP:
        std::cout << "def";
        break;
    }
}

void GC::drawScene() {
    std::cout << "abc" << std::endl;
}

void GC::run() {
    while (cq.size() == 0 || (cq[0] != int('e') && cq[0] != int('q'))) {
        while (cq.size() > 0) {
            handle(cq[0]);
            cq.erase(cq.begin());
        }

//        state.tic();
        drawScene();
    }
}

int GC::getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

void GC::setControl() {
    int c;
    do {
        c = getch();
        cq.push_back(c);
    } while (c != int('q') && c != int('e'));
}
