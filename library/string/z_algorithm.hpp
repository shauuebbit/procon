#pragma once

#include <string>
#include <vector>

std::vector<int> z_algorithm(const std::string& s) {
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

template <typename T>
std::vector<int> z_algorithm(const std::vector<T>& s) {
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
