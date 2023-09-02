#pragma once

#include <cassert>
#include <vector>

class UnionFind {
   private:
    size_t sz;
    std::vector<int> data;

   public:
    UnionFind(size_t n = 0) : data(n, -1), sz(n) {}

    size_t find(size_t x) {
        assert(x < data.size());
        return static_cast<size_t>(data[x] < 0 ? x : data[x] = find(data[x]));
    }

    bool unite(size_t x, size_t y) {
        x = find(x);
        y = find(y);

        if (x == y) {
            return false;
        } else {
            if (data[x] > data[y]) std::swap(x, y);
            data[x] += data[y];
            data[y] = x;
            --sz;
            return true;
        }
    }

    bool is_same(size_t x, size_t y) { return find(x) == find(y); }

    size_t size(size_t x) { return static_cast<size_t>(-data[find(x)]); }

    size_t size() const { return sz; }
};
