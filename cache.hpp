#pragma once

#include <iterator>
#include <list>
#include <unordered_map>
#include <tuple>
#include <utility>

const int MAX_TESTS_ARR_SIZE = 1024;
const int STOP_LINE_VALUE = -1;

int LFU_test();

int slow_get_page(int key);

int slow_get_page(int key);

namespace caches {

    template <typename T, typename KeyT = int, typename CntT = unsigned int>
    struct cache_t
    {
        size_t sz_;

        struct page_t
        {
            KeyT key;
            T    content;
            CntT cnt;
        };

        std::list<page_t> cache_;

        using ListIt = typename std::list<page_t>::iterator;

        std::unordered_map<KeyT, ListIt> hash_;

        ListIt less_used_iter;

        cache_t(size_t sz) : sz_(sz) {};

        bool full() const
        {
            return cache_.size() == sz_;
        }

        template <typename F>
        bool lookup_update(KeyT key, F slow_get_page)
        {
            auto hit = hash_.find(key);

            if (hit == hash_.end())
            {
                if (full())
                {
                    find_less_used();
                    hash_.erase((*less_used_iter).key);
                    cache_.erase(less_used_iter);
                }
                page_t emplace_struct = {slow_get_page(key), key, 1};
                cache_.emplace_front(emplace_struct);
                hash_.emplace(key, cache_.begin());

                return false;
            }

            (*(hit->second)).cnt++;

            return true;
        }

        void change_size(size_t new_sz)
        {
            hash_.clear();
            cache_.clear();
            sz_ = new_sz;
        }

        void find_less_used()
        {
            ListIt iter = cache_.begin();
            less_used_iter = iter;

            while (iter != cache_.end())
            {
                if ((*iter).cnt <= (*less_used_iter).cnt)
                {
                    less_used_iter = iter;
                }
                iter++;
            }
        }

        void print_cache_list()
        {
            ListIt iter = cache_.end();

            std::cout << "key-cnt" << std::endl;

            while (iter-- != cache_.begin())
            {
                std::cout << (*iter).content << "-" << (*iter).cnt << std::endl;
            }
        }
    };

}
