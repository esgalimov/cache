#pragma once

#include <iterator>
#include <list>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>


namespace ideal_caches {

    template <typename T, typename KeyT = int, typename CntT = unsigned int>
    struct ideal_cache_t
    {
        size_t sz_;
        size_t req_num_;

        struct page_t
        {
            KeyT   key;
            T      content;
            size_t pos;
        };

        std::map<size_t, page_t, std::greater<size_t>> cache_;
        using MapIt = typename std::map<size_t, page_t, std::greater<size_t>>::iterator;

        std::unordered_multimap<KeyT, page_t> hash_;

        std::vector<KeyT> requests;


        ideal_cache_t(size_t sz, size_t req_num) : sz_(sz), req_num_(req_num) {};

        bool full() const
        {
            return cache_.size() == sz_;
        }

        bool get_requests()
        {
            requests.reserve(req_num_);
            KeyT curr_key = 0;

            for (size_t i = 0; i < req_num_; i++)
            {
                if (!(std::cin >> curr_key))
                {
                    std::cout << "Bad request on pos " << i << std::endl;
                    return false;
                }
                requests.push_back(curr_key);
            }
            for (size_t i = 0; i < req_num_; i++)
            {
                hash_.emplace(requests[i], page_t{requests[i], 0, i});
            }
            return true;
        }

        template <typename F>
        bool lookup_update(size_t pos, F slow_get_page)
        {
            auto hit = cache_.find(pos);

            if (hit == cache_.end())
            {
                if (full())
                {
                    hash_.erase(hash_.find(requests[pos]));

                    MapIt later_used = cache_.begin();
                    auto next_curr = hash_.find(requests[pos]);

                    if (next_curr != hash_.end() && later_used->second.pos > next_curr->second.pos)
                    {
                        cache_.erase(later_used);
                        cache_.emplace(next_curr->second.pos, page_t{requests[pos],
                                       slow_get_page(requests[pos]), next_curr->second.pos});
                    }

                    return false;
                }

                hash_.erase(hash_.find(requests[pos]));
                auto next_curr = hash_.find(requests[pos]);

                if (next_curr != hash_.end())
                    cache_.emplace(next_curr->second.pos, page_t{requests[pos],
                                   slow_get_page(requests[pos]), next_curr->second.pos});

                return false;
            }

            cache_.erase(hit);
            hash_.erase(hash_.find(requests[pos]));

            auto next_curr = hash_.find(requests[pos]);

            if (next_curr == hash_.end())
                cache_.emplace(req_num_, page_t{requests[pos], slow_get_page(requests[pos]), req_num_});
            else
                cache_.emplace(next_curr->second.pos, page_t{requests[pos],
                               slow_get_page(requests[pos]), next_curr->second.pos});

            return true;
        }

        void print_cache()
        {
            std::cout << "cache, size = " << cache_.size() << std::endl;
            for (auto it = cache_.begin(); it != cache_.end(); it++)
                std::cout << it->second.key << "-" << it->second.pos << std::endl;

            std::cout << "\n\n";
        }

        void print_hash()
        {
            std::cout << "hash" << std::endl;
            for (unsigned i = 0; i < hash_.bucket_count(); ++i)
            {
                std::cout << i << " contains:";
                for (auto local_it = hash_.begin(i); local_it != hash_.end(i); ++local_it)
                    std::cout << " " << local_it->first << ":" << local_it->second.pos;
                std::cout << std::endl;
            }
            std::cout << "\n\n";
        }
    };

}
