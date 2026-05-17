#include "geometry/arg_sort.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

TEST(ArgSortTest, Small1) {
    vector<Point<int>> points(8), points_sorted(8);

    int x[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    int y[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    for (int i = 0; i < 8; i++) {
        points_sorted[i] = {x[i], y[i]};
    }

    vector<int> p(8);
    iota(p.begin(), p.end(), 0);

    do {
        for (int i = 0; i < 8; i++) {
            points[i] = points_sorted[p[i]];
        }

        arg_sort(points);

        for (int i = 0; i < 8; i++) {
            ASSERT_EQ(points[i], points_sorted[i]);
        }
    } while (next_permutation(p.begin(), p.end()));
}

TEST(ArgSortTest, Small2) {
    vector<Point<int>> points(16), points_sorted(16);

    int x[16] = {1, 2, 1, 1, 0, -1, -1, -2, -1, -2, -1, -1, 0, 1, 1, 2};
    int y[16] = {0, 1, 1, 2, 1, 2, 1, 1, 0, -1, -1, -2, -1, -2, -1, -1};

    for (int i = 0; i < 16; i++) {
        points_sorted[i] = {x[i], y[i]};
    }

    random_device seed_gen;
    mt19937 engine(seed_gen());

    vector<int> p(16);
    iota(p.begin(), p.end(), 0);

    for (int k = 0; k < 1000; k++) {
        ranges::shuffle(p, engine);

        for (int i = 0; i < 16; i++) {
            points[i] = points_sorted[p[i]];
        }

        arg_sort(points);

        for (int i = 0; i < 16; i++) {
            ASSERT_EQ(points[i], points_sorted[i]);
        }
    }
}
