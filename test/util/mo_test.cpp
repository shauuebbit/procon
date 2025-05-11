#include "util/mo.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

TEST(MoTest, HilbertOrder1) {
    ASSERT_EQ(hilbert_order(0, 0, 3), 0);
    ASSERT_EQ(hilbert_order(1, 0, 3), 1);
    ASSERT_EQ(hilbert_order(1, 1, 3), 2);
    ASSERT_EQ(hilbert_order(0, 1, 3), 3);
    ASSERT_EQ(hilbert_order(0, 2, 3), 4);
    ASSERT_EQ(hilbert_order(0, 3, 3), 5);
    ASSERT_EQ(hilbert_order(1, 3, 3), 6);
    ASSERT_EQ(hilbert_order(1, 2, 3), 7);
    ASSERT_EQ(hilbert_order(2, 2, 3), 8);
    ASSERT_EQ(hilbert_order(2, 3, 3), 9);
    ASSERT_EQ(hilbert_order(3, 3, 3), 10);
    ASSERT_EQ(hilbert_order(3, 2, 3), 11);
    ASSERT_EQ(hilbert_order(3, 1, 3), 12);
    ASSERT_EQ(hilbert_order(2, 1, 3), 13);
    ASSERT_EQ(hilbert_order(2, 0, 3), 14);
    ASSERT_EQ(hilbert_order(3, 0, 3), 15);

    ASSERT_EQ(hilbert_order(4, 0, 3), 16);
    ASSERT_EQ(hilbert_order(4, 1, 3), 17);
    ASSERT_EQ(hilbert_order(5, 1, 3), 18);
    ASSERT_EQ(hilbert_order(5, 0, 3), 19);
    ASSERT_EQ(hilbert_order(6, 0, 3), 20);
    ASSERT_EQ(hilbert_order(7, 0, 3), 21);
    ASSERT_EQ(hilbert_order(7, 1, 3), 22);
    ASSERT_EQ(hilbert_order(6, 1, 3), 23);
    ASSERT_EQ(hilbert_order(6, 2, 3), 24);
    ASSERT_EQ(hilbert_order(7, 2, 3), 25);
    ASSERT_EQ(hilbert_order(7, 3, 3), 26);
    ASSERT_EQ(hilbert_order(6, 3, 3), 27);
    ASSERT_EQ(hilbert_order(5, 3, 3), 28);
    ASSERT_EQ(hilbert_order(5, 2, 3), 29);
    ASSERT_EQ(hilbert_order(4, 2, 3), 30);
    ASSERT_EQ(hilbert_order(4, 3, 3), 31);

    ASSERT_EQ(hilbert_order(4, 4, 3), 32);
    // :
    ASSERT_EQ(hilbert_order(4, 7, 3), 47);

    ASSERT_EQ(hilbert_order(3, 7, 3), 48);
    // :
    ASSERT_EQ(hilbert_order(0, 7, 3), 63);
}

TEST(MoTest, HilbertOrder2) {
    int l = 5;
    vector<array<int, 2>> p(1 << l << l);

    for (int x = 0; x < (1 << l); x++) {
        for (int y = 0; y < (1 << l); y++) {
            p[x | (y << l)] = {x, y};
        }
    }

    vector<int> idx(1 << l << l);
    iota(idx.begin(), idx.end(), 0);

    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return hilbert_order(p[i][0], p[i][1], l) < hilbert_order(p[j][0], p[j][1], l);
    });

    for (int i = 0; i + 1 < (1 << l << l); i++) {
        ASSERT_EQ(abs(p[idx[i]][0] - p[idx[i + 1]][0]) + abs(p[idx[i]][1] - p[idx[i + 1]][1]), 1);
    }
}

TEST(MoTest, RandomNumberOfKinds) {
    const int n = 10000;
    const int m = 100;
    const int q = 10000;

    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist_idx(0, n);
    uniform_int_distribution<> dist_val(0, m - 1);

    vector<int> a(n);

    vector<pair<int, int>> queries(q);

    vector<int> ans(q, 0);

    bitset<m> b;

    for (int i = 0; i < n; i++) {
        a[i] = dist_val(engine);
    }

    for (int t = 0; t < q; t++) {
        int l = dist_idx(engine);
        int r = dist_idx(engine);

        if (l > r) swap(l, r);

        queries[t] = {l, r};

        for (int i = l; i < r; i++) {
            b.set(a[i]);
        }

        ans[t] = b.count();
        b.reset();
    }

    Mo mo;

    for (int t = 0; t < q; t++) {
        auto [l, r] = queries[t];

        mo.add_query(l, r);
    }

    int num_kinds = 0;

    vector<int> sum(m, 0);

    auto expand = [&](int idx) {
        if (sum[a[idx]]++ == 0) ++num_kinds;
    };

    auto shrink = [&](int idx) {
        if (--sum[a[idx]] == 0) --num_kinds;
    };

    vector<int> mo_ans(q);

    auto answer = [&](int query_idx) {
        mo_ans[query_idx] = num_kinds;
    };

    mo.run(n, expand, expand, shrink, shrink, answer);

    for (int t = 0; t < q; t++) {
        ASSERT_EQ(mo_ans[t], ans[t]);
    }
}
