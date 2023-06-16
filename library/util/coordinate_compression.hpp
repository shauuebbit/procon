#pragma once

#include <algorithm>
#include <vector>

template <typename T>
class Compressor {
   private:
    bool compressed;
    std::vector<T> data;

   public:
    Compressor() : compressed(false) {}

    Compressor(const std::vector<T>& data) : data(data), compressed(false) {
        compressed = build();
    }

    bool add(T x) {
        if (compressed) return false;
        data.push_back(x);
        return true;
    }

    bool build() {
        if (compressed) return false;
        std::sort(data.begin(), data.end());
        data.erase(std::unique(data.begin(), data.end()), data.end());
        return compressed = true;
    }

    int compress(const T& x) {
        if (!compressed) build();
        return static_cast<int>(std::upper_bound(data.begin(), data.end(), x) - data.begin()) - 1;
    }

    T uncompress(int index) {
        if (!compressed) build();
        return data[index];
    }

    size_t size() {
        if (!compressed) build();
        return data.size();
    }
};
