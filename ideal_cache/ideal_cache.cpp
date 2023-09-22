#include <iostream>

#include "ideal_cache.hpp"

int slow_get_page(int key)
{
    return key;
}

int main()
{
    //std::cout << "Enter cache size and number of requests:" << std::endl;

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

    //std::cout << "Enter " << req_num << " requests:" << std::endl;

    ideal_caches::ideal_cache_t<int> myIdealCache{cache_size, req_num};
    size_t hits = 0;

    if (myIdealCache.get_requests())
        for (size_t i = 0; i < req_num; i++)
            hits += (size_t) myIdealCache.lookup_update(i, slow_get_page);

    std::cout << "Ideal cache hits = " << hits << std::endl;

    return 0;
}
