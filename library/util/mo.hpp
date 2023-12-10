#pragma once

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

long long hilbert_order(size_t x, size_t y, size_t k) {
    if (k == 0) return 0;

    --k;
    size_t m = (size_t)1 << k;

    size_t fx = (x & m) >> k, fy = (y & m) >> k;

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

    return (static_cast<size_t>(m) << k) * ((fy << 1) | (fx ^ fy)) + hilbert_order(x, y, k);
}

class Mo {
    std::vector<std::pair<size_t, size_t>> queries;

   public:
    void add_query(size_t left, size_t right) {
        queries.emplace_back(left, right);
    }

    template <typename EL, typename ER, typename SL, typename SR, typename A>
    void run(size_t n, const EL& expand_left, const ER& expand_right, const SL& shrink_left, const SR& shrink_right, const A& answer) {
        std::vector<size_t> indices(queries.size());
        std::iota(indices.begin(), indices.end(), 0);

        size_t k = 0;
        while (((size_t)1 << k) < n) ++k;

        std::vector<long long> ord(queries.size());

        for (size_t q = 0; q < queries.size(); q++) {
            ord[q] = hilbert_order(queries[q].second, queries[q].first, k);
        }

        std::sort(indices.begin(), indices.end(), [&ord = std::as_const(ord)](int i, int j) {
            return ord[i] < ord[j];
        });

        size_t left = 0;
        size_t right = 0;

        for (size_t idx : indices) {
            auto [l, r] = queries[idx];

            while (l < left) expand_left(--left);
            while (right < r) expand_right(right++);
            while (left < l) shrink_left(left++);
            while (r < right) shrink_right(--right);

            answer(idx);
        }
    }
};
