#include "geometry/arg_sort.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using namespace std;

TEST(ArgSortTest, Small) {
    vector<Point<int>> points(8), points_sorted(8);

    int x[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    int y[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    for (int i = 0; i < 8; i++) {
        points[i] = {x[i], y[i]};
        points_sorted[i] = {x[i], y[i]};
    }

    do {
        auto p = points;

        arg_sort(p);

        for (int i = 0; i < 8; i++) {
            ASSERT_EQ(p[i], points_sorted[i]);
        }
    } while (next_permutation(points.begin(), points.end()));
}
