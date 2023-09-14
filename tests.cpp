#include <iostream>
#include <fstream>
#include <cstdlib>

#include "cache.hpp"
#include "ideal_cache.hpp"

int LFU_test() {
    std::fstream ftests("test.txt");

    if (!ftests.is_open()) {
        std::cout << "Can't open file with tests" << std::endl;
        return 1;
    }

    int cache_sz = 0, req_num = 0, cur_req = 0, hits = 0;

    std::cout << "LFU cache tests:" << std::endl;

    ftests >> cache_sz;
    caches::cache_t<int> myCache{(size_t) cache_sz};
    ftests >> req_num;

    while (ftests >> cur_req)
    {
        if (req_num-- == 0)
        {
            if (hits == cur_req)
            {
                std::cout << "Test passed, hits = " << hits << std::endl;
            }
            else
            {
                std::cout << "Test failed, hits = " << hits << ", correct = " << cur_req << std::endl;
            }
            ftests >> cache_sz;
            myCache.change_size((size_t) cache_sz);
            ftests >> req_num;
            hits = 0;
            continue;
        }
        hits += (int) myCache.lookup_update(cur_req, slow_get_page);
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

    std::cout << "\nIdeal cache tests:" << std::endl;

    int cur_req = 0, cache_sz = 0, req_num = 0;

    ftests >> cache_sz;
    ideal_caches::ideal_cache_t<int> myCache{(size_t) cache_sz};

    ftests >> req_num;
    int* requests = (int*) calloc(req_num, sizeof(int));

    int hits = 0;
    size_t i = 0;

    while (ftests >> cur_req)
    {
        if (req_num-- == 0)
        {
            for (size_t j = 0; j < i; j++)
                hits += (int) myCache.lookup_update(requests[j], slow_get_page, requests, i, j);

            std::cout << "Ideal, hits = " << hits << ", LFU = " << cur_req << std::endl;

            ftests >> cache_sz;
            myCache.change_size((size_t) cache_sz);

            ftests >> req_num;
            requests = (int*) realloc(requests, req_num * sizeof(int));

            hits = 0;
            i = 0;
            continue;
        }
        requests[i++] = cur_req;
    }
    delete[] requests;

    return 0;
}
