#pragma once

#include <cassert>
#include <limits>
#include <set>

template <typename T, typename Compare = std::less<T>>
class ConvexHullTrick {
   private:
    static constexpr Compare cmp = Compare();

    static bool cmp1(const std::optional<std::pair<T, T>>& l1, const std::optional<std::pair<T, T>>& l2) {
        assert(l1 && l2);
        return l1.value() < l2.value();
    }

    static bool cmp2(const std::optional<std::pair<T, T>>& e1, const std::optional<std::pair<T, T>>& e2) {
        if (!e1)
            return false;
        else if (!e2)
            return true;
        auto [p1, q1] = e1.value();
        auto [p2, q2] = e2.value();
        return cmp(p2 * q1, p1 * q2);
    }

    struct Line {
        std::optional<std::pair<T, T>> line;
        mutable std::optional<std::pair<T, T>> endpoint;

        bool operator<(const Line& rhs) const {
            if (this->line && rhs.line)
                return cmp1(this->line, rhs.line);
            else
                return cmp2(this->endpoint, rhs.endpoint);
        }
    };

    static std::pair<T, T> intersection(const std::optional<std::pair<T, T>>& l1, const std::optional<std::pair<T, T>>& l2) {
        assert(l1 && l2);
        auto [a1, b1] = l1.value();
        auto [a2, b2] = l2.value();
        assert(a1 < a2);
        return {b1 - b2, a2 - a1};
    }

    std::set<Line> line_set;

   public:
    bool add_line(const std::pair<T, T>& line) {
        auto [a, b] = line;

        if (auto itr = line_set.lower_bound({std::pair<T, T>({a, std::numeric_limits<T>::lowest()}), std::nullopt}); itr != line_set.end()) {
            auto [ta, tb] = itr->line.value();
            if (ta == a) {
                if (!cmp(b, tb)) return false;
                line_set.erase(itr);
            }
        }

        auto [itr, is_inserted] = line_set.insert({line, std::nullopt});
        assert(is_inserted);

        for (auto next = std::next(itr, 1);; next = line_set.erase(next)) {
            if (next == line_set.end()) {
                itr->endpoint = std::nullopt;
                break;
            }
            itr->endpoint = intersection(itr->line, next->line);
            if (cmp2(itr->endpoint, next->endpoint)) break;
        }

        for (auto prev = std::prev(itr, 1), prev2 = std::prev(prev, 1); itr != line_set.begin(); line_set.erase(prev), prev = prev2, --prev2) {
            prev->endpoint = intersection(prev->line, itr->line);
            if (prev == line_set.begin() || cmp2(prev2->endpoint, prev->endpoint)) break;
        }

        if (auto prev = std::prev(itr, 1); itr != line_set.begin() && !cmp2(prev->endpoint, itr->endpoint)) {
            itr = line_set.erase(itr);
            if (itr != line_set.end()) prev->endpoint = intersection(prev->line, itr->line);
            else prev->endpoint = std::nullopt;

            return false;
        }

        return true;
    }

    T get(const T& x) const {
        assert(!line_set.empty());

        auto itr = line_set.lower_bound({std::nullopt, std::pair<T, T>({x, 1})});

        auto [a, b] = itr->line.value();

        return a * x + b;
    }
};
