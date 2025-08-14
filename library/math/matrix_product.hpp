#pragma once

#include <cassert>
#include <vector>

template <typename T>
std::vector<std::vector<T>> matrix_product(const std::vector<std::vector<T>>& a, const std::vector<std::vector<T>>& b) {
    assert(a.size() && b.size() && a[0].size() && b[0].size() && a[0].size() == b.size());

    size_t n = a.size(), m = b[0].size(), r = a[0].size();

    std::vector ret(n, std::vector<T>(m, 0));

    for (size_t k = 0; k < r; k++) {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) {
                ret[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return ret;
}
