#include "data_structure/lazy_segment_tree.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <optional>
#include <random>

using namespace std;

TEST(LazySegmentTreeTest, RangeUpdateRangeMinimumQuery) {
    int n = 5000;
    int q = 50000;

    const int MAX = 1e5;
    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist_idx(0, n - 1);
    uniform_int_distribution<> dist_val(-MAX, MAX);

    const long long INF = 1ll << 60;

    using M = long long;
    using E = optional<long long>;

    auto op = [](const M& x, const M& y) {
        return min(x, y);
    };

    auto cp = [](const E& f, const E& g) {
        if (g)
            return g;
        else
            return f;
    };

    auto act = [](const M& x, const E& f) {
        if (f) return f.value();
        return x;
    };

    const M e = INF;
    const E id = nullopt;

    LazySegmentTree<M, E, decltype(op), decltype(act), decltype(cp)> segtree(n, op, act, cp, e, id);

    vector<M> a(n, e);

    for (int t = 0; t < q; t++) {
        int l = dist_idx(engine);
        int r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        M x = dist_val(engine);

        for (int i = l; i < r; i++) {
            a[i] = x;
        }

        segtree.update(l, r, x);

        l = dist_idx(engine);
        r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        x = e;

        for (int i = l; i < r; i++) {
            x = op(x, a[i]);
        }

        ASSERT_EQ(segtree.fold(l, r), x);

        if (t == q / 1000) {
            int j = dist_idx(engine);
            ASSERT_EQ(segtree.get(j), a[j]);
        }
    }
}

TEST(LazySegmentTreeTest, RangeAddRangeMinimumQuery) {
    int n = (1 << 12);
    int q = 50000;

    const int MAX = 1e5;
    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist_idx(0, n - 1);
    uniform_int_distribution<> dist_val(-MAX, MAX);

    const long long INF = 1ll << 60;

    using M = long long;
    using E = long long;

    auto op = [](const M& x, const M& y) {
        return min(x, y);
    };

    auto cp = [](const E& f, const E& g) {
        return f + g;
    };

    auto act = [](const M& x, const E& f) -> M {
        return x + f;
    };

    const M e = INF;
    const E id = 0ll;

    vector<M> a(n, 0ll);

    LazySegmentTree<M, E, decltype(op), decltype(act), decltype(cp)> segtree(a, op, act, cp, e, id);

    for (int t = 0; t < q; t++) {
        int l = dist_idx(engine);
        int r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        M x = dist_val(engine);

        for (int i = l; i < r; i++) {
            a[i] += x;
        }

        segtree.update(l, r, x);

        l = dist_idx(engine);
        r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        x = e;

        for (int i = l; i < r; i++) {
            x = op(x, a[i]);
        }

        ASSERT_EQ(segtree.fold(l, r), x);

        if (t == q / 1000) {
            int j = dist_idx(engine);
            ASSERT_EQ(segtree.get(j), a[j]);
        }
    }
}

TEST(LazySegmentTreeTest, PointUpdateRangeAddRangeMinimumQuery) {
    int n = 4000;
    int q = 50000;

    const int MAX = 1e5;
    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist_idx(0, n - 1);
    uniform_int_distribution<> dist_val(-MAX, MAX);

    const long long INF = 1ll << 60;

    using M = long long;
    using E = long long;

    auto op = [](const M& x, const M& y) {
        return min(x, y);
    };

    auto cp = [](const E& f, const E& g) {
        return f + g;
    };

    auto act = [](const M& x, const E& f) -> M {
        return x + f;
    };

    const M e = INF;
    const E id = 0ll;

    vector<M> a(n, 0ll);

    LazySegmentTree<M, E, decltype(op), decltype(act), decltype(cp)> segtree(a, op, act, cp, e, id);

    for (int t = 0; t < q; t++) {
        int l = dist_idx(engine);
        int r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        M x = dist_val(engine);

        for (int i = l; i < r; i++) {
            a[i] += x;
        }

        segtree.update(l, r, x);

        if ((t >> 2) & 1) {
            int i = dist_idx(engine);

            M x = dist_val(engine);
            a[i] = x;
            segtree.set(i, x);
        }

        l = dist_idx(engine);
        r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        x = e;

        for (int i = l; i < r; i++) {
            x = op(x, a[i]);
        }

        ASSERT_EQ(segtree.fold(l, r), x);

        if (t == q / 1000) {
            int j = dist_idx(engine);
            ASSERT_EQ(segtree.get(j), a[j]);
        }
    }
}

TEST(LazySegmentTreeTest, RangeUpdateRangeSumQuery) {
    int n = (1 << 12) - 1;
    int q = 50000;

    const int MAX = 1e5;
    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist_idx(0, n - 1);
    uniform_int_distribution<> dist_val(-MAX, MAX);

    struct M {
        long long sum;
        int len;
    };

    using E = optional<long long>;

    auto op = [](const M& x, const M& y) -> M {
        return {x.sum + y.sum, x.len + y.len};
    };

    auto cp = [](const E& f, const E& g) {
        if (g)
            return g;
        else
            return f;
    };

    auto act = [](const M& x, const E& f) -> M {
        if (f) {
            auto fval = f.value();
            return {fval * x.len, x.len};
        }
        return x;
    };

    const M e = {0ll, 0};
    const E id = nullopt;

    vector<M> init_data(n, {0ll, 1});

    LazySegmentTree<M, E, decltype(op), decltype(act), decltype(cp)> segtree(init_data, op, act, cp, e, id);

    vector<long long> a(n, 0ll);

    for (int t = 0; t < q; t++) {
        int l = dist_idx(engine);
        int r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        long long val = dist_val(engine);

        for (int i = l; i < r; i++) {
            a[i] = val;
        }

        segtree.update(l, r, val);

        l = dist_idx(engine);
        r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        M x = e;

        for (int i = l; i < r; i++) {
            x = op(x, {a[i], 1});
        }

        ASSERT_EQ(segtree.fold(l, r).sum, x.sum);
        ASSERT_EQ(segtree.fold(l, r).len, x.len);
    }
}

TEST(LazySegmentTreeTest, RangeAddRangeSumQuery) {
    int n = (1 << 12) + 1;
    int q = 50000;

    const int MAX = 1e5;
    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist_idx(0, n - 1);
    uniform_int_distribution<> dist_val(-MAX, MAX);

    struct M {
        long long sum;
        int len;
    };

    using E = long long;

    auto op = [](const M& x, const M& y) -> M {
        return {x.sum + y.sum, x.len + y.len};
    };

    auto cp = [](const E& f, const E& g) {
        return f + g;
    };

    auto act = [](const M& x, const E& f) -> M {
        return {x.sum + f * x.len, x.len};
    };

    const M e = {0ll, 0};
    const E id = 0ll;

    vector<M> init_data(n, {0ll, 1});

    LazySegmentTree<M, E, decltype(op), decltype(act), decltype(cp)> segtree(init_data, op, act, cp, e, id);

    vector<long long> a(n, 0ll);

    for (int t = 0; t < q; t++) {
        int l = dist_idx(engine);
        int r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        long long val = dist_val(engine);

        for (int i = l; i < r; i++) {
            a[i] += val;
        }

        segtree.update(l, r, val);

        l = dist_idx(engine);
        r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        M x = e;

        for (int i = l; i < r; i++) {
            x = op(x, {a[i], 1});
        }

        ASSERT_EQ(segtree.fold(l, r).sum, x.sum);
        ASSERT_EQ(segtree.fold(l, r).len, x.len);
    }
}
