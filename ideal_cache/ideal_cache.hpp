#pragma once

#include <iterator>
#include <list>
#include <unordered_map>
#include <tuple>
#include <utility>


namespace ideal_caches {

    template <typename T, typename KeyT = int, typename CntT = unsigned int>
    struct ideal_cache_t
    {
        size_t sz_;

        struct page_t
        {
            KeyT   key;
            T      content;
            size_t next_find;
        };

        std::list<page_t> cache_;

        using ListIt = typename std::list<page_t>::iterator;

        std::unordered_map<KeyT, ListIt> hash_;

        ListIt later_used_iter;

        ideal_cache_t(size_t sz) : sz_(sz) {};

        bool full() const
        {
            return cache_.size() == sz_;
        }

        template <typename F>
        bool lookup_update(KeyT key, F slow_get_page, T* requests, size_t len, size_t pos)
        {
            auto hit = hash_.find(key);

            if (hit == hash_.end())
            {
                if (full())
                {
                    if (find_later_used(key, requests, len, pos))
                    {
                        hash_.erase((*later_used_iter).key);
                        cache_.erase(later_used_iter);

                        page_t emplace_struct = {slow_get_page(key), key, 0};

                        cache_.emplace_front(emplace_struct);
                        hash_.emplace(key, cache_.begin());
                    }
                }
                else
                {
                    page_t emplace_struct = {slow_get_page(key), key, 0};

                    cache_.emplace_front(emplace_struct);
                    hash_.emplace(key, cache_.begin());
                }

                return false;
            }

            return true;
        }

        void change_size(size_t new_sz)
        {
            hash_.clear();
            cache_.clear();
            sz_ = new_sz;
        }

        size_t find_later_used(KeyT key, T* requests, size_t len, size_t pos)
        {
            ListIt iter = cache_.begin();

            size_t curr_find = len;

            for (size_t i = pos + 1; i < len; i++)
            {
                if (requests[i] == key)
                {
                    curr_find = i;
                    break;
                }
            }

            while (iter != cache_.end())
            {
                (*iter).next_find = len;

                for (size_t i = pos + 1; i < len; i++)
                {
                    if (requests[i] == (*iter).key)
                    {
                        (*iter).next_find = i;
                        break;
                    }
                }
                iter++;
            }
            iter = cache_.begin();
            later_used_iter = iter;

            while (iter != cache_.end())
            {
                if ((*iter).next_find >= (*later_used_iter).next_find)
                {
                    later_used_iter = iter;
                }
                iter++;
            }

            if (curr_find > (*later_used_iter).next_find)
                return 0;

            return curr_find;
        }

        void print_cache_list()
        {
            ListIt iter = cache_.end();

            std::cout << "key" << std::endl;

            while (iter-- != cache_.begin())
            {
                std::cout << (*iter).content << " ";
            }
            std::cout << std::endl;
        }
    };

}
