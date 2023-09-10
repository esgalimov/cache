#include <iostream>
#include <fstream>

#include "cache.hpp"

int test() {
    std::fstream ftests("test.txt");

    if (!ftests.is_open()) {
        std::cout << "Can't open file with tests" << std::endl;
        return 1;
    }

    int cur_value = 0,
        next_value = 0,
        hits = 0;

    ftests >> cur_value;
    caches::cache_t<int> myCache{(size_t) cur_value};

    while (ftests >> next_value)
    {
        if (next_value == STOP_LINE_VALUE)
        {
            if (hits == cur_value)
            {
                std::cout << "Test passed, hits = " << hits << std::endl;
            }
            else
            {
                std::cout << "Test failed, hits = " << hits << ", correct = " << cur_value << std::endl;
            }
            ftests >> cur_value;
            myCache.change_size((size_t) cur_value);
            ftests >> cur_value;
            hits = 0;
            continue;
        }
        hits += (int) myCache.lookup_update(cur_value, slow_get_page);
        cur_value = next_value;
    }

    return 0;
}
