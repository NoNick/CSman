#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>

// just a data type
struct drawBlock {
    std::pair <int, int> begin, end;
    std::vector <std::string> texture;
    // add or sub hp per tact
};

#endif
