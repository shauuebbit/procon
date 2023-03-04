#pragma once

#include <string>
#include <vector>

std::vector<int> manacher(const std::string& s) {
    std::vector<int> ret(s.size());

    for (int i = 0, j = 0; i < (int)s.size();) {
        while (i - j >= 0 && i + j < s.size() && s[i - j] == s[i + j]) {
            ++j;
        }
        ret[i] = j;

        int k = 1;
        while (i - k >= 0 && k + ret[i - k] < j) {
            ret[i + k] = ret[i - k];
            ++k;
        }
        i += k;
        j -= k;
    }

    return ret;
}

template <typename T>
std::vector<int> manacher(const std::vector<T>& s) {
    std::vector<int> ret(s.size());

    for (int i = 0, j = 0; i < (int)s.size();) {
        while (i - j >= 0 && i + j < s.size() && s[i - j] == s[i + j]) {
            ++j;
        }
        ret[i] = j;

        int k = 1;
        while (i - k >= 0 && k + ret[i - k] < j) {
            ret[i + k] = ret[i - k];
            ++k;
        }
        i += k;
        j -= k;
    }

    return ret;
}
