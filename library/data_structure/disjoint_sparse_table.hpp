#pragma once

#include <bit>
#include <cassert>
#include <functional>
#include <vector>

template <typename T, typename F = std::function<T(T, T)>>
class DisjointSparseTable {
   private:
    std::vector<std::vector<T>> table;
    F op;

   public:
    DisjointSparseTable(const std::vector<T>& v, const F& op) : op(op) {
        unsigned int k = std::bit_width(v.size());
        table = std::vector<std::vector<T>>(k, std::vector<T>(v.size()));

        for (unsigned int d = 0; d < k; d++) {
            for (unsigned int l = 0; l < v.size(); l += (2 << d)) {
                unsigned int m = std::min(l + (1 << d), (unsigned int)v.size());

                table[d][m - 1] = v[m - 1];
                for (unsigned int i = m - 1; i > l; i--) {
                    table[d][i - 1] = op(v[i - 1], table[d][i]);
                }

                if (m >= v.size()) continue;

                table[d][m] = v[m];
                unsigned int r = std::min(l + (2 << d), (unsigned int)v.size());
                for (unsigned int i = m; i + 1 < r; i++) {
                    table[d][i + 1] = op(table[d][i], v[i + 1]);
                }
            }
        }
    }

    T fold(unsigned int l, unsigned int r) {
        // [l, r)
        assert(l < r);
        assert(r <= table[0].size());
        --r;

        if (l == r) {
            return table[0][l];
        }

        unsigned int d = sizeof(unsigned int) * 8 - std::countl_zero(l ^ r) - 1;

        return op(table[d][l], table[d][r]);
    }
};
