#include <iostream>
#include "gamecontroller.h"
#include "state.h"
#include "draw.h"

using namespace std;

int main()
{
    GC* game = new GC(new State(), new Draw(30, 30), "./textures", "./blocks");

    #pragma omp parallel sections
    {
        #pragma omp section
        game->run();
        #pragma omp section
        game->setControl();
    }

    return 0;
}
