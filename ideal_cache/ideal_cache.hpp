#pragma once

#include <iterator>
#include <list>
#include <map>
#include <unordered_map>
#include <utility>


namespace ideal_caches {

    template <typename T, typename KeyT = int, typename CntT = unsigned int>
    struct ideal_cache_t
    {
        private:

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

        KeyT* requests;

        bool full() const
        {
            return cache_.size() == sz_;
        }

        void get_requests()
        {
            for (size_t i = 0; i < req_num_; i++)
                hash_.emplace(requests[i], page_t{requests[i], 0, i});
        }

        void replace_latest_page(KeyT key, T content)
        {
            hash_.erase(hash_.find(key));

            MapIt later_used = cache_.begin();
            auto next_curr = hash_.find(key);

            if (next_curr != hash_.end() && later_used->second.pos > next_curr->second.pos)
            {
                cache_.erase(later_used);
                cache_.emplace(next_curr->second.pos, page_t{key, content, next_curr->second.pos});
            }
        }

        void add_new_page(KeyT key, T content)
        {
            hash_.erase(hash_.find(key));
            auto next_curr = hash_.find(key);

            if (next_curr != hash_.end())
                cache_.emplace(next_curr->second.pos, page_t{key, content, next_curr->second.pos});
        }

        void hit_update(KeyT key, T content)
        {
            hash_.erase(hash_.find(key));

            auto next_curr = hash_.find(key);

            if (next_curr == hash_.end())
                cache_.emplace(req_num_, page_t{key, content, req_num_});
            else
                cache_.emplace(next_curr->second.pos, page_t{key, content, next_curr->second.pos});
        }

        public:

        ideal_cache_t(size_t sz, size_t req_num, KeyT* reqs) :
        sz_(sz), req_num_(req_num), requests(reqs)
        { get_requests();};

        template <typename F>
        bool lookup_update(size_t pos, F slow_get_page)
        {
            auto hit = cache_.find(pos);

            if (hit == cache_.end())
            {
                if (full())
                {
                    replace_latest_page(requests[pos], slow_get_page(requests[pos]));
                    return false;
                }
                add_new_page(requests[pos], slow_get_page(requests[pos]));
                return false;
            }
            cache_.erase(hit);
            hit_update(requests[pos], slow_get_page(requests[pos]));

            return true;
        }
    };

}
