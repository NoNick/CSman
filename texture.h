#ifndef TEXTURE_H
#define TEXTURE_H
#include <vector>
#include <string>

// just a data type
class texture
{
public:
    texture(std::vector <std::string> d);
    std::vector <std::string> data;
};

#endif // TEXTURE_H
