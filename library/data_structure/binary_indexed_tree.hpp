#pragma once

#include <cassert>
#include <vector>

template <typename T>
class BinaryIndexedTree {
   private:
    std::vector<T> data;

   public:
    BinaryIndexedTree(size_t sz = 0) : data(sz + 1, 0) {}

    bool add(size_t index, T x = 1) {
        if (data.size() <= index + 1) return false;
        for (++index; index < data.size(); index += index & -index) {
            data[index] += x;
        }
        return true;
    }

    T sum(size_t index) const {
        // [0..index]

        T x = 0;
        for (index = std::min(index + 1, data.size() - 1); index; index -= index & -index) {
            x += data[index];
        }
        return x;
    }

    size_t lower_bound(T x) const {
        if (x <= 0) return 0;

        size_t index = 0, b = 1;
        while ((b << 1) < data.size()) b <<= 1;

        while (b) {
            if (index + b < data.size() && data[index + b] < x) {
                x -= data[index + b];
                index += b;
            }
            b >>= 1;
        }
        return index;
    }

    size_t size() { return data.size() - 1; }
};
