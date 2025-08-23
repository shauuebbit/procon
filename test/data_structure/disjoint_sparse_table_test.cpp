#include "data_structure/disjoint_sparse_table.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <vector>

using namespace std;

const int INF = 1e9 + 9;
const int MAX = 1e8;

TEST(DisjointSparseTableTest, RandomRangeMinimumQuery) {
    random_device seed_gen;
    mt19937 engine(seed_gen());

    int n = 5000;
    int q = 50000;

    uniform_int_distribution<> dist_idx(0, n - 1);
    uniform_int_distribution<> dist_val(-MAX, MAX);

    vector<int> v(n, INF);

    for (int i = 0; i < n; i++) {
        v[i] = dist_val(engine);
    }

    auto op = [](int a, int b) {
        return min(a, b);
    };

    DisjointSparseTable<int, decltype(op)> table(v, op);

    for (int t = 0; t < q; t++) {
        int l = dist_idx(engine);
        int r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        int x = INF;

        for (int j = l; j < r; j++) {
            x = min(x, v[j]);
        }

        ASSERT_EQ(table.fold(l, r), x);
    }
}

TEST(DisjointSparseTableTest, RandomLinearComposition) {
    int n = 5000;
    int q = 50000;

    const int MAX = 10;

    struct S {
        long long a;
        long long b;

        bool operator==(const S& rhs) const {
            return a == rhs.a && b == rhs.b;
        }
    };

    auto c = [](const S& f, const S& g) -> S {
        return {g.a * f.a, g.a * f.b + g.b};
    };

    const S ID = {1ll, 0ll};

    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist_idx(0, n - 1);
    uniform_int_distribution<> dist_val(-MAX, MAX);

    vector<S> v(n, ID);

    for (int i = 0; i < n; i++) {
        v[i] = {dist_val(engine), dist_val(engine)};
    }

    DisjointSparseTable<S, decltype(c)> segtree(v, c);

    for (int t = 0; t < q; t++) {
        int l = dist_idx(engine);
        int r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        S x = ID;

        for (int j = l; j < r; j++) {
            x = c(x, v[j]);
        }

        ASSERT_EQ(segtree.fold(l, r), x);
    }
}
