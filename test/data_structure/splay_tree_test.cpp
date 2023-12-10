#include "data_structure/splay_tree.hpp"

#include <gtest/gtest.h>

#include <random>
#include <set>

#include "data_structure/lazy_segment_tree.hpp"

using namespace std;

TEST(SplayTreeTest, LinearInsert1) {
    auto op = [](int, int) { return 0; };
    auto act = [](int, int) { return 0; };
    auto cp = [](int, int) { return 0; };

    SplayTree<int, int, int, decltype(op), decltype(act), decltype(cp)> tree(op, act, cp, 0, 0);

    int n = 300000;

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(tree.size(), i);
        tree.insert(i, 0);
        ASSERT_FALSE(tree.empty());
    }
    ASSERT_EQ(tree.size(), n);
}

TEST(SplayTreeTest, LinearInsert2) {
    auto op = [](int, int) { return 0; };
    auto act = [](int, int) { return 0; };
    auto cp = [](int, int) { return 0; };

    SplayTree<int, int, int, decltype(op), decltype(act), decltype(cp)> tree(op, act, cp, 0, 0);

    int n = 300000;

    for (int i = n - 1; i >= 0; i--) {
        ASSERT_EQ(tree.size(), n - i - 1);
        tree.insert(i, 0);
        ASSERT_FALSE(tree.empty());
    }
    ASSERT_EQ(tree.size(), n);
}

TEST(SplayTreeTest, LinearErase1) {
    auto op = [](int, int) { return 0; };
    auto act = [](int, int) { return 0; };
    auto cp = [](int, int) { return 0; };

    SplayTree<int, int, int, decltype(op), decltype(act), decltype(cp)> tree(op, act, cp, 0, 0);

    int n = 300000;

    for (int i = 0; i < n; i++) {
        tree.insert(i, 0);
    }

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(tree.size(), n - i);
        ASSERT_FALSE(tree.empty());
        tree.erase(i);
    }
    ASSERT_EQ(tree.size(), 0);
    ASSERT_TRUE(tree.empty());
}

TEST(SplayTreeTest, LinearErase2) {
    auto op = [](int, int) { return 0; };
    auto act = [](int, int) { return 0; };
    auto cp = [](int, int) { return 0; };

    SplayTree<int, int, int, decltype(op), decltype(act), decltype(cp)> tree(op, act, cp, 0, 0);

    int n = 300000;

    for (int i = 0; i < n; i++) {
        tree.insert(i, 0);
    }

    for (int i = n - 1; i >= 0; i--) {
        ASSERT_EQ(tree.size(), i + 1);
        ASSERT_FALSE(tree.empty());
        tree.erase(i);
    }
    ASSERT_EQ(tree.size(), 0);
    ASSERT_TRUE(tree.empty());
}

TEST(SplayTreeTest, LinearErase3) {
    auto op = [](int, int) { return 0; };
    auto act = [](int, int) { return 0; };
    auto cp = [](int, int) { return 0; };

    SplayTree<int, int, int, decltype(op), decltype(act), decltype(cp)> tree(op, act, cp, 0, 0);

    int n = 300000;

    for (int i = n - 1; i >= 0; i--) {
        tree.insert(i, 0);
    }

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(tree.size(), n - i);
        ASSERT_FALSE(tree.empty());
        tree.erase(i);
    }
    ASSERT_EQ(tree.size(), 0);
    ASSERT_TRUE(tree.empty());
}

TEST(SplayTreeTest, LinearErase4) {
    auto op = [](int, int) { return 0; };
    auto act = [](int, int) { return 0; };
    auto cp = [](int, int) { return 0; };

    SplayTree<int, int, int, decltype(op), decltype(act), decltype(cp)> tree(op, act, cp, 0, 0);

    int n = 300000;

    for (int i = n - 1; i >= 0; i--) {
        tree.insert(i, 0);
    }

    for (int i = n - 1; i >= 0; i--) {
        ASSERT_EQ(tree.size(), i + 1);
        ASSERT_FALSE(tree.empty());
        tree.erase(i);
    }
    ASSERT_EQ(tree.size(), 0);
    ASSERT_TRUE(tree.empty());
}

TEST(SplayTreeTest, InsertAndErase) {
    auto op = [](int, int) { return 0; };
    auto act = [](int, int) { return 0; };
    auto cp = [](int, int) { return 0; };

    SplayTree<int, int, int, decltype(op), decltype(act), decltype(cp)> tree(op, act, cp, 0, 0);

    multiset<int> s;

    int n = 3000;

    for (int i = 0; i < n; i++) {
        int r = i % 3;
        if (r == 0) {
            tree.insert(i, 0);
            s.insert(i);
        } else if (r == 1) {
            tree.insert(i + 1, 0);
            s.insert(i + 1);
        } else {
            tree.insert(i - 1, 0);
            s.insert(i - 1);
        }

        ASSERT_EQ(tree.size(), s.size());

        if (i % 6 == 5) {
            tree.erase(i - 3);
            tree.erase(i - 1);

            s.erase(s.find(i - 3));
            s.erase(s.find(i - 1));
        }

        ASSERT_EQ(tree.size(), s.size());

        for (auto e : s) {
            ASSERT_TRUE(tree.contains(e));
        }
    }

    while (!s.empty()) {
        tree.erase(*s.begin());
        s.erase(s.begin());
    }

    ASSERT_TRUE(tree.empty());
}

TEST(SplayTreeTest, GetKthKey) {
    auto op = [](int, int) { return 0; };
    auto act = [](int, int) { return 0; };
    auto cp = [](int, int) { return 0; };

    SplayTree<int, int, int, decltype(op), decltype(act), decltype(cp)> tree(op, act, cp, 0, 0);

    multiset<int> s;

    int n = 3000;

    for (int i = 0; i < n; i++) {
        int r = i % 3;
        if (r == 0) {
            tree.insert(i, 0);
            s.insert(i);
        } else if (r == 1) {
            tree.insert(i + 1, 0);
            s.insert(i + 1);
        } else {
            tree.insert(i - 1, 0);
            s.insert(i - 1);
        }

        if (i % 6 == 5) {
            tree.erase(i - 3);
            tree.erase(i - 1);

            s.erase(s.find(i - 3));
            s.erase(s.find(i - 1));
        }

        size_t ord = 0;
        for (auto e : s) {
            ASSERT_EQ(tree.get_kth_key(ord++), e);
        }
    }

    while (!s.empty()) {
        tree.erase(*s.begin());
        s.erase(s.begin());

        size_t ord = 0;
        for (auto e : s) {
            ASSERT_EQ(tree.get_index(e), ord++);
        }
    }
}

TEST(SplayTreeTest, Clear) {
    auto op = [](int, int) { return 0; };
    auto act = [](int, int) { return 0; };
    auto cp = [](int, int) { return 0; };

    SplayTree<int, int, int, decltype(op), decltype(act), decltype(cp)> tree(op, act, cp, 0, 0);

    int n = 300000;

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(tree.size(), i);
        tree.insert(i, 0);
    }

    tree.clear();

    ASSERT_TRUE(tree.empty());

    tree.insert(1, 0);

    ASSERT_EQ(tree.size(), 1);
}

TEST(SplayTreeTest, InsertRangeUpdateRangeMinimumQuery) {
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

    const M e = INF;
    const E id = nullopt;

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

    auto act2 = [](const M& x, const E& f) {
        if (x == e)
            return x;
        else if (f)
            return f.value();
        else
            return x;
    };

    SplayTree<int, M, E, decltype(op), decltype(act), decltype(cp)> tree(op, act, cp, e, id);

    LazySegmentTree<M, E, decltype(op), decltype(act2), decltype(cp)> segtree(n, op, act2, cp, e, id);

    vector<int> contains(n, 0);

    for (int t = 0; t < q; t++) {
        int i = dist_idx(engine);

        M x = dist_val(engine);

        if (contains[i]) {
            tree.update(i, x);
            segtree.update(i, x);
        } else {
            tree.insert(i, x);
            segtree.update(i, x);
            contains[i] |= 1;
        }

        int l = dist_idx(engine);
        int r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        x = dist_val(engine);

        tree.update(l, r - 1, x);

        segtree.update(l, r, x);

        l = dist_idx(engine);
        r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        ASSERT_EQ(tree.fold(l, r - 1), segtree.fold(l, r));
        ASSERT_EQ(tree.fold(), segtree.fold());
    }
}

TEST(SplayTreeTest, InsertEraseRangeUpdateRangeMinimumQuery) {
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

    const M e = INF;
    const E id = nullopt;

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

    auto act2 = [](const M& x, const E& f) {
        if (x == e)
            return x;
        else if (f)
            return f.value();
        else
            return x;
    };

    SplayTree<int, M, E, decltype(op), decltype(act), decltype(cp)> tree(op, act, cp, e, id);

    LazySegmentTree<M, E, decltype(op), decltype(act2), decltype(cp)> segtree(n, op, act2, cp, e, id);

    vector<int> contains(n, 0);

    for (int t = 0; t < q; t++) {
        int i = dist_idx(engine);

        M x = dist_val(engine);

        if (contains[i]) {
            tree.erase(i);
            segtree.update(i, e);
            contains[i] ^= 1;
        } else {
            tree.insert(i, x);
            segtree.update(i, x);
            contains[i] ^= 1;
        }

        int l = dist_idx(engine);
        int r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        x = dist_val(engine);

        tree.update(l, r - 1, x);

        segtree.update(l, r, x);

        l = dist_idx(engine);
        r = dist_idx(engine);

        if (l > r) swap(l, r);
        ++r;

        ASSERT_EQ(tree.fold(l, r - 1), segtree.fold(l, r));
        ASSERT_EQ(tree.fold(), segtree.fold());
    }
}
