#pragma once

#include <vector>

class UnionFind {
   private:
    size_t sz;
    std::vector<int> data;

   public:
    UnionFind(size_t n = 0) : sz(n), data(n, -1) {}

    int find(int x) { return data[x] < 0 ? x : data[x] = find(data[x]); }

    bool unite(int x, int y) {
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

    bool is_same(int x, int y) { return find(x) == find(y); }

    size_t size(int x) {
        return static_cast<size_t>(-data[find(x)]);
    }

    size_t size() { return sz; }
};
