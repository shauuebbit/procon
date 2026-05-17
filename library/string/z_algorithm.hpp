#pragma once

#include <vector>

template <std::ranges::random_access_range R>
std::vector<int> z_algorithm(const R& s) {
    std::vector<int> ret(s.size());
    ret[0] = s.size();

    for (int i = 1, j = 0; i < (int)s.size();) {
        while (i + j < (int)s.size() && s[j] == s[i + j]) ++j;
        ret[i] = j;
        if (j == 0) {
            ++i;
            continue;
        }

        int k = 1;
        while (i + k < (int)s.size() && k + ret[k] < j) {
            ret[i + k] = ret[k];
            ++k;
        }
        i += k;
        j -= k;
    }

    return ret;
}
