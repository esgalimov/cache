#include <iostream>

#include "ideal_cache.hpp"
#include "get.hpp"

int slow_get_page(int key)
{
    return key;
}

int main()
{
    cache_props_t ch_pr = get_props();

    if (!ch_pr.is_ok) exit(1);

    ideal_caches::ideal_cache_t<int> myIdealCache{ch_pr.cache_size, ch_pr.req_num, ch_pr.requests};
    int hits = 0;

    for (int i = 0; i < ch_pr.req_num; i++)
        hits += myIdealCache.lookup_update(i, slow_get_page);

    std::cout << "Ideal cache hits = " << hits << std::endl;

    return 0;
}
