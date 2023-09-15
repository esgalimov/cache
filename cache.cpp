#include <iostream>

#include "cache.hpp"
#include "ideal_cache.hpp"

//#define TESTS

int slow_get_page(int key)
{
    return key;
}

int main()
{
    #ifdef TESTS
        LFU_test();
        ideal_cache_test();
    #endif
    #ifndef TESTS

    // FILE* stream = freopen( "015.dat", "r", stdin);
    // if (!stream)
    // {
    //     std::cout << "Something wrog with file opening" << std::endl;
    //     return 1;
    // }

    std::cout << "Enter cache size and number of requests:" << std::endl;

    size_t cache_size = 0,
           req_num = 0;

    if (!(std::cin >> cache_size && std::cin >> req_num))
    {
        std::cout << "Invalid input" << std::endl;
        return 1;
    }

    std::cout << "Enter " << req_num << " requests:" << std::endl;

    caches::cache_t<int> myCache{cache_size};

    int* requests = new int [req_num];
    int req = 0, hits = 0;

    for (size_t i = 0; i < req_num; i++)
    {
        if (!(std::cin >> req))
        {
            std::cout << "Invalid input" << std::endl;
            return 1;
        }
        requests[i] = req;

        hits += (int) myCache.lookup_update(req, slow_get_page);
    }
    std::cout << "LFU hits = " << hits << std::endl;
//     hits = 0;
//
//     ideal_caches::ideal_cache_t<int> myIdealCache{cache_size};
//
//     for (size_t i = 0; i < req_num; i++)
//     {
//         hits += myIdealCache.lookup_update(requests[i], slow_get_page, requests, req_num, i);
//     }
//     std::cout << "Ideal cache hits = " << hits << std::endl;

    delete[] requests;

    #endif

    return 0;
}


