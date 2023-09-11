#include <iostream>
#include <fstream>

#include "cache.hpp"
#include "ideal_cache.hpp"

int LFU_test() {
    std::fstream ftests("test.txt");

    if (!ftests.is_open()) {
        std::cout << "Can't open file with tests" << std::endl;
        return 1;
    }

    int cur_value = 0,
        next_value = 0,
        hits = 0;

    std::cout << "LFU cache tests:" << std::endl;

    ftests >> cur_value;
    caches::cache_t<int> myCache{(size_t) cur_value};
    ftests >> cur_value;

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

int ideal_cache_test()
{
    std::fstream ftests("test.txt");

    if (!ftests.is_open()) {
        std::cout << "Can't open file with tests" << std::endl;
        return 1;
    }

    int* requests = (int*) calloc(MAX_TESTS_ARR_SIZE, sizeof(int));

    std::cout << "\nIdeal cache tests:" << std::endl;

    int val = 0;

    ftests >> val;
    ideal_caches::ideal_cache_t<int> myCache{(size_t) val};

    int hits = 0;
    size_t i = 0;

    while (ftests >> val)
    {
        if (val == STOP_LINE_VALUE)
        {
            for (size_t j = 0; j < i - 1; j++)
                hits += (int) myCache.lookup_update(requests[j], slow_get_page, requests, i, j);

            std::cout << "Ideal, hits = " << hits << ", LFU = " << requests[i - 1] << std::endl;

            ftests >> val;
            myCache.change_size((size_t) val);
            hits = 0;
            i = 0;
            continue;
        }
        requests[i++] = val;
    }

    free(requests);

    return 0;
}
