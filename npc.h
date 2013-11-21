#ifndef NPC_H
#define NPC_H

class NPC
{
public:
    NPC();

private:
    point pos, mov, size;
    vector <string> texture;
    int hp, melee, ranged;
};

#endif // NPC_H
