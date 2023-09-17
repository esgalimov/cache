#include <iostream>

#include "lfu_cache.hpp"

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

    caches::cache_t<int> myCache{cache_size};

    int req = 0, hits = 0;

    for (size_t i = 0; i < req_num; i++)
    {
        if (!(std::cin >> req))
        {
            std::cout << "Invalid input" << std::endl;
            return 1;
        }

        hits += (int) myCache.lookup_update(req, slow_get_page);
    }
    std::cout << "LFU hits = " << hits << std::endl;

    return 0;
}


