#pragma once

#include <iterator>
#include <list>
#include <unordered_map>
#include <map>
#include <tuple>
#include <utility>


int slow_get_page(int key);

namespace caches {

    template <typename T, typename KeyT = int, typename CntT = unsigned int>
    struct cache_t
    {
        private:
        size_t sz_;

        struct page_t
        {
            KeyT key;
            T    content;
            CntT cnt;
        };

        using ListIt = typename std::list<page_t>::iterator;

        std::unordered_map<KeyT, ListIt> hash_;
        std::map<CntT, std::list<page_t>> cnt_;

        bool full() const
        {
            return hash_.size() == sz_;
        }

        void delete_less_used_page()
        {
            ListIt less_used_iter = (cnt_.begin()->second).begin();

            CntT less_used_cnt = less_used_iter->cnt;

            hash_.erase(less_used_iter->key);
            (cnt_.begin()->second).erase(less_used_iter);

            if (cnt_.begin()->second.size() == 0)
                cnt_.erase(less_used_cnt);
        }

        void add_new_page(KeyT key, T content)
        {
            page_t emplace_struct = {content, key, 1};

            auto cnt_one_find = cnt_.find(1);

            if (cnt_one_find == cnt_.end())
                cnt_.emplace(1, std::list<page_t>{emplace_struct});
            else
                (cnt_.begin()->second).emplace_back(emplace_struct);

            hash_.emplace(key, --(cnt_.begin()->second.end()));
        }

        void hit_update(ListIt cur_iter, KeyT key)
        {
            cur_iter->cnt++;

            auto cnt_hit_find = cnt_.find(cur_iter->cnt);

            if (cnt_hit_find == cnt_.end())
                cnt_.emplace(cur_iter->cnt, std::list<page_t>{*cur_iter});

            else
                cnt_hit_find->second.emplace_back(*cur_iter);

            hash_.at(key) = --(cnt_.find(cur_iter->cnt)->second.end());

            CntT cnt_before = cur_iter->cnt - 1;
            auto cnt_before_find = cnt_.find(cnt_before);
            (*cnt_before_find).second.erase(cur_iter);

            if (cnt_before_find->second.size() == 0)
                cnt_.erase(cnt_before);
        }

        public:

        cache_t(size_t sz) : sz_(sz) {};

        template <typename F>
        bool lookup_update(KeyT key, F slow_get_page)
        {
            auto hit = hash_.find(key);

            if (hit == hash_.end())
            {
                if (full()) delete_less_used_page();

                add_new_page(key, slow_get_page(key));

                return false;
            }

            hit_update(hit->second, key);

            return true;
        }
    };

}
