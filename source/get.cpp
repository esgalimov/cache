#include "get.hpp"

cache_props_t get_props() {
    cache_props_t ch_pr{};

    if (!(std::cin >> ch_pr.cache_size && std::cin >> ch_pr.req_num))
    {
        std::cout << "Invalid input" << std::endl;
        return ch_pr;
    }

    if (ch_pr.cache_size <= 0 || ch_pr.req_num <= 0)
    {
        std::cout << "Bad cache_size = " << ch_pr.cache_size << " or req_num = " << ch_pr.req_num << std::endl;
        return ch_pr;
    }
    ch_pr.requests.reserve(ch_pr.req_num);
    int curr_key = 0;

    for (size_t i = 0; i < ch_pr.req_num; i++)
    {
        if (!(std::cin >> curr_key))
        {
            std::cout << "Bad request on pos " << i << std::endl;
            return ch_pr;
        }
        ch_pr.requests[i] = curr_key;
    }
    ch_pr.is_ok = true;
    return ch_pr;
};
