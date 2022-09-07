#include "data_structure/segment_tree.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <vector>

using namespace std;

const int INF = 1e9 + 9;
const int MAX = 1e8;

TEST(SegmentTreeTest, RandomRangeMinimumQuery) {
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

    SegmentTree<int> segtree(
        v, [](int a, int b) { return min(a, b); }, INF);

    for (int t = 0; t < q; t++) {
        int i = dist_idx(engine);
        int x = dist_val(engine);

        segtree.update(i, x);
        v[i] = x;

        int l = 0, r = n;

        x = INF;

        for (int j = l; j < r; j++) {
            x = min(x, v[j]);
        }

        ASSERT_EQ(segtree.fold(l, r), x);

        l = dist_idx(engine);
        r = dist_idx(engine);

        if (l > r) swap(l, r);

        x = INF;

        for (int j = l; j < r; j++) {
            x = min(x, v[j]);
        }

        ASSERT_EQ(segtree.fold(l, r), x);
    }
}

TEST(SegmentTreeTest, RandomRangeMaximumQuery) {
    random_device seed_gen;
    mt19937 engine(seed_gen());

    int n = 5000;
    int q = 50000;

    uniform_int_distribution<> dist_idx(0, n - 1);
    uniform_int_distribution<> dist_val(-MAX, MAX);

    SegmentTree<int, std::function<int(int, int)>> segtree(
        n, [](int a, int b) { return max(a, b); }, -INF);

    vector<int> v(n, -INF);

    for (int t = 0; t < q; t++) {
        int i = dist_idx(engine);
        int x = dist_val(engine);

        segtree.update(i, x);
        v[i] = x;

        int l = 0, r = n;

        x = -INF;

        for (int j = l; j < r; j++) {
            x = max(x, v[j]);
        }

        ASSERT_EQ(segtree.fold(l, r), x);

        l = dist_idx(engine);
        r = dist_idx(engine);

        if (l > r) swap(l, r);

        x = -INF;

        for (int j = l; j < r; j++) {
            x = max(x, v[j]);
        }

        ASSERT_EQ(segtree.fold(l, r), x);
    }
}

TEST(SegmentTreeTest, RandomRangeSumQuery) {
    int n = 5000;
    int q = 50000;

    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist_idx(0, n - 1);
    uniform_int_distribution<> dist_val(-MAX, MAX);

    auto f = [](long long a, long long b) {
        return a + b;
    };

    SegmentTree<long long, decltype(f)> segtree(n, f, 0ll);

    vector<long long> v(n, 0ll);

    for (int t = 0; t < q; t++) {
        int i = dist_idx(engine);
        long long x = static_cast<long long>(dist_val(engine));

        segtree.update(i, x);
        v[i] = x;

        int l = 0, r = n;

        x = 0ll;

        for (int j = l; j < r; j++) {
            x = x + v[j];
        }

        ASSERT_EQ(segtree.fold(l, r), x);

        l = dist_idx(engine);
        r = dist_idx(engine);

        if (l > r) swap(l, r);

        x = 0ll;

        for (int j = l; j < r; j++) {
            x = x + v[j];
        }

        ASSERT_EQ(segtree.fold(l, r), x);
    }
}

TEST(SegmentTreeTest, RandomLinearComposition) {
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

    SegmentTree<S, decltype(c)> segtree(v, c, ID);

    for (int t = 0; t < q; t++) {
        int i = dist_idx(engine);
        S x = {dist_val(engine), dist_val(engine)};

        segtree.update(i, x);
        v[i] = x;

        int l = 0, r = n;

        x = ID;

        for (int j = l; j < r; j++) {
            x = c(x, v[j]);
        }

        ASSERT_EQ(segtree.fold(l, r), x);

        l = dist_idx(engine);
        r = dist_idx(engine);

        if (l > r) swap(l, r);

        x = ID;

        for (int j = l; j < r; j++) {
            x = c(x, v[j]);
        }

        ASSERT_EQ(segtree.fold(l, r), x);
    }
}
