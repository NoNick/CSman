#include "state.h"
#include <vector>
#include "player.h"
#include <stdio.h>

struct pathState {
    Player pl;
    std::vector < std::pair <int, int> > path;
};

std::vector < std::pair <int, int> > State::findPath(std::pair <int, int> source,
                                            std::pair <int, int> target, Player p) {
    std::vector <pathState> queue;
    pathState curr, tmp;
    curr.pl = p;
    curr.path.push_back(source);
    queue.push_back(curr);
    while (!queue.empty()) {
        curr = queue[0];
        queue.erase(queue.begin());

        if ((int)curr.pl.pos.first == target.first && (int)curr.pl.pos.second == target.second)
            return curr.path;

        if (curr.pl.goLng < 0 && !isOnBlock(&curr.pl)) {
            tmp = curr;
            gravity(&tmp.pl);
            tmp.path.push_back(std::make_pair((int)tmp.pl.pos.first, (int)tmp.pl.pos.second));
            queue.push_back(tmp);
        }
        else {
            if (isOnBlock(&curr.pl)) {
                tmp = curr;
                tmp.pl.goLng = tmp.pl.mov.second;
                tmp.pl.jump = tmp.pl.mov.second;
                gravity(&tmp.pl);
                tmp.path.push_back(std::make_pair((int)tmp.pl.pos.first, (int)tmp.pl.pos.second));
                queue.push_back(tmp);
            }

            tmp = curr;
            tmp.pl.pos.first -= tmp.pl.mov.first;
            printf("%lf %lf\n", tmp.pl.pos.first, tmp.pl.pos.second);
            // if left way open
            if (!isBlockBeside(&tmp.pl)) {
                tmp.path.push_back(std::make_pair((int)tmp.pl.pos.first, (int)tmp.pl.pos.second));
                queue.push_back(tmp);
            }
            tmp = curr;
            tmp.pl.pos.first += tmp.pl.mov.first;
            // if right way open
            if (!isBlockBeside(&tmp.pl)) {
                tmp.path.push_back(std::make_pair((int)tmp.pl.pos.first, (int)tmp.pl.pos.second));
                queue.push_back(tmp);
            }
        }
    }

    std::vector < std::pair <int, int> > empty;
    return empty;
}
