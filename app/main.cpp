#include "skiplist.hpp"


int main()
{

    std::vector<int> d = {200, 120, 30, 55, -1, 21, 76, 98, 111, 82};

    SKLT::SkipList<int, int> sl;

    for (unsigned int i = 0; i < d.size(); i++) {

        std::cout << "insert:" << d[i] << std::endl;

        sl.insert(d[i], i);
    }

    std::cout << "remove 55" << std::endl;

    sl.remove(55);

    sl.find(55);

    sl.find(98);

    sl.find(46);

    return 0;
}

