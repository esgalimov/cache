#include <iostream>

#include "ideal_cache.hpp"

int slow_get_page(int key)
{
    return key;
}

int main()
{
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

    int* requests = new int[req_num];
    int curr_key = 0;

    for (size_t i = 0; i < req_num; i++)
    {
        if (!(std::cin >> curr_key))
        {
            std::cout << "Bad request on pos " << i << std::endl;
            return 1;
        }
        requests[i] = curr_key;
    }

    ideal_caches::ideal_cache_t<int> myIdealCache{cache_size, req_num, requests};
    size_t hits = 0;

    for (size_t i = 0; i < req_num; i++)
        hits += (size_t) myIdealCache.lookup_update(i, slow_get_page);

    std::cout << "Ideal cache hits = " << hits << std::endl;

    delete[] requests;

    return 0;
}
