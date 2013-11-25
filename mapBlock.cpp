#include "mapBlock.h"

mapBlock::mapBlock() {
}

mapBlock::mapBlock(std::pair <int, int> b, std::pair <int, int> e,
                   double hp, texture *t) {
    begin = b;
    end = e;
    hpBal = hp;
    tex = t;
}
