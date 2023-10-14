#include <iostream>

#include "lfu_cache.hpp"
#include "get.hpp"

int slow_get_page(int key)
{
    return key;
}

int main()
{
    cache_props_t ch_pr = get_props();

    if (!ch_pr.is_ok) exit(1);

    caches::cache_t<int> myCache{ch_pr.cache_size};
    int hits = 0;

    for (int i = 0; i < ch_pr.req_num; i++)
        hits += myCache.lookup_update(ch_pr.requests[i], slow_get_page);

    std::cout << "LFU hits = " << hits << std::endl;

    return 0;
}


