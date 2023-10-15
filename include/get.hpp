#pragma once
#include <vector>

struct cache_props_t {
    size_t cache_size = 0;
    size_t req_num = 0;
    std::vector<int> requests;
    bool is_ok = false;
};

cache_props_t get_props();
