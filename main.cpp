#include <iostream>
#include "gamecontroller.h"

using namespace std;

int main()
{
    GC* game = new GC();

    #pragma omp parallel sections
    {
        #pragma omp section
        game->run();
        #pragma omp section
        game->setControl();
    }

    return 0;
}
