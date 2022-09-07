#pragma once

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

long long hilbert_order(int x, int y, int k) {
    if (k == 0) return 0;
 
    --k;
    int m = 1 << k;
 
    int fx = (x & m) >> k, fy = (y & m) >> k;
 
    x = ~m & x;
    y = ~m & y;
 
    if (!fx) {
        x ^= y;
        y ^= x;
        x ^= y;
 
        if (fy) {
            x = ~x & (m - 1);
            y = ~y & (m - 1);
        }
    }
 
    return (static_cast<long long>(m) << k) * ((fy << 1) | (fx ^ fy)) + hilbert_order(x, y, k);
}
 
class Mo {
    std::vector<std::pair<int, int>> queries;
 
   public:
    void add_query(int left, int right) {
        queries.emplace_back(left, right);
    }
 
    template <typename EL, typename ER, typename SL, typename SR, typename A>
    void run(int n, const EL& expand_left, const ER& expand_right, const SL& shrink_left, const SR& shrink_right, const A& answer) {
        std::vector<int> indices(queries.size());
        std::iota(indices.begin(), indices.end(), 0);
 
        int k = 0;
        while ((1 << k) < n) ++k;
 
        std::vector<long long> ord(queries.size());
 
        for (int q = 0; q < queries.size(); q++) {
            ord[q] = hilbert_order(queries[q].second, queries[q].first, k);
        }
 
        std::sort(indices.begin(), indices.end(), [&ord = std::as_const(ord)](int i, int j) {
            return ord[i] < ord[j];
        });
 
        int left = 0;
        int right = 0;
 
        for (int idx : indices) {
            auto [l, r] = queries[idx];
 
            while (l < left) expand_left(--left);
            while (right < r) expand_right(right++);
            while (left < l) shrink_left(left++);
            while (r < right) shrink_right(--right);
 
            answer(idx);
        }
    }
};
