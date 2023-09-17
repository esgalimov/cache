#include <iostream>

#include "ideal_cache.hpp"

int slow_get_page(int key)
{
    return key;
}

int main()
{
    // FILE* stream = freopen( "011.dat", "r", stdin);
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

    if (cache_size <= 0 || req_num <= 0)
    {
        std::cout << "Bad cache_size = " << cache_size << " or req_num = " << req_num << std::endl;
        return 1;
    }

    std::cout << "Enter " << req_num << " requests:" << std::endl;

    ideal_caches::ideal_cache_t<int> myIdealCache{cache_size};

    int* requests = new int [req_num];
    int req = 0;

    for (size_t i = 0; i < req_num; i++)
    {
        if (!(std::cin >> req))
        {
            std::cout << "Invalid input" << std::endl;
            return 1;
        }
        requests[i] = req;
    }
    int hits = 0;

    for (size_t i = 0; i < req_num; i++)
    {
        hits += myIdealCache.lookup_update(requests[i], slow_get_page, requests, req_num, i);
    }
    std::cout << "Ideal cache hits = " << hits << std::endl;

    delete[] requests;

    return 0;
}
