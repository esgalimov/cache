#include <iostream>
#include <cassert>

#include "cache.hpp"


int slow_get_page(int key)
{
    return key;
}

int main()
{
    caches::cache_t<int> myCache{3};

    myCache.lookup_update(2, slow_get_page);
    myCache.lookup_update(1, slow_get_page);
    myCache.lookup_update(3, slow_get_page);
    myCache.lookup_update(3, slow_get_page);
    myCache.lookup_update(3, slow_get_page);
    myCache.lookup_update(3, slow_get_page);
    myCache.lookup_update(3, slow_get_page);
    myCache.lookup_update(2, slow_get_page);
    myCache.lookup_update(3, slow_get_page);
    //myCache.lookup_update(77, slow_get_page);
    myCache.print_cache_list();
    return 0;
}


