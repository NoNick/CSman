#include <string>
#include <vector>
#include <string>

struct block {
    std::pair <int, int> begin, end;
    std::vector <std::string> texture;
    // add or sub hp per tact
    double hpBal;
};
