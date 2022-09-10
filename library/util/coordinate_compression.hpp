#pragma once

#include <algorithm>
#include <map>
#include <vector>

template <typename T>
class Compressor {
   private:
    bool compressed;
    std::map<T, int> zip;
    std::vector<T> unzip;

   public:
    Compressor() : compressed(false) {}

    Compressor(const std::vector<T>& org) : unzip(org), compressed(false) {
        compressed = build();
    }

    bool add(T x) {
        if (compressed) return false;
        unzip.push_back(x);
        return true;
    }

    bool build() {
        if (compressed) return false;

        std::sort(unzip.begin(), unzip.end());
        unzip.erase(std::unique(unzip.begin(), unzip.end()), unzip.end());

        for (int i = 0; i < (int)unzip.size(); i++) {
            zip[unzip[i]] = i;
        }

        compressed = true;

        return true;
    }

    int compress(const T& x) {
        if (!compressed) build();

        return zip[x];
    }

    T uncompress(int ord) {
        if (!compressed) build();

        return unzip[ord];
    }

    size_t size() {
        if (!compressed) build();

        return unzip.size();
    }
};
