#include <iostream>
#include "gamecontroller.h"
#include "state.h"

using namespace std;

int main()
{
    GC* game = new GC(State());

    #pragma omp parallel sections
    {
        #pragma omp section
        game->run();
        #pragma omp section
        game->setControl();
    }

    return 0;
}
