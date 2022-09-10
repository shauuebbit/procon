#include "geometry/arg_sort.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

TEST(ArgSortTest, Small) {
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
