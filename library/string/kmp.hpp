#pragma once

#include <string>
#include <vector>

std::vector<int> kmp(const std::string& s) {
    std::vector<int> ret(s.size() + 1, -1);
    for (int i = 0, j = -1; i < (int)s.size(); i++) {
        while (j >= 0 && s[i] != s[j]) j = ret[j];
        if (s[i + 1] == s[++j])
            ret[i + 1] = ret[j];
        else
            ret[i + 1] = j;
    }
    return ret;
}

template <typename T>
std::vector<int> kmp(const std::vector<T>& s) {
    std::vector<int> ret(s.size() + 1, -1);
    for (int i = 0, j = -1; i < (int)s.size(); i++) {
        while (j >= 0 && s[i] != s[j]) j = ret[j];
        if (s[i + 1] == s[++j])
            ret[i + 1] = ret[j];
        else
            ret[i + 1] = j;
    }
    return ret;
}

int search(const std::string& target, const std::string& pattern) {
    auto r = kmp(pattern);

    for (int i = 0, j = 0; i < (int)target.size(); i++) {
        if (target[i] == pattern[j]) {
            if (j + 1 == (int)pattern.size()) return i - j;

            ++j;
        } else {
            if (r[j] == r[0])
                j = 0;
            else
                --i, j = r[j];
        }
    }

    return -1;
}

template <typename T>
int search(const std::vector<T>& target, const std::vector<T>& pattern) {
    auto r = kmp(pattern);

    for (int i = 0, j = 0; i < (int)target.size(); i++) {
        if (target[i] == pattern[j]) {
            if (j + 1 == (int)pattern.size()) return i - j;

            ++j;
        } else {
            if (r[j] == r[0])
                j = 0;
            else
                --i, j = r[j];
        }
    }

    return -1;
}
