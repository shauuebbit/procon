#include "geometry/convex_hull.hpp"

#include <gtest/gtest.h>

#include <random>
#include <vector>

using namespace std;

TEST(ConvexHullTest, PointSmall) {
    vector<Point<int>> points(5);
    points[0] = Point<int>(0, 0), points[1] = Point<int>(1, 1), points[2] = Point<int>(1, 0), points[3] = Point<int>(-2, 2), points[4] = Point<int>(0, 1);

    vector<Point<int>> ch = convex_hull(points);

    ASSERT_EQ(ch.size(), 4);
}

TEST(ConvexHullTest, ComplexSmall) {
    vector<complex<double>> points(5);
    points[0] = complex<double>(0, 0), points[1] = complex<double>(1, 1), points[2] = complex<double>(1, 0), points[3] = complex<double>(-2, 2), points[4] = complex<double>(0, 1);

    vector<complex<double>> ch = convex_hull(points);

    ASSERT_EQ(ch.size(), 4);
}

TEST(ConvexHullTest, Line) {
    vector<Point<int>> points(5);
    points[0] = Point<int>(0, 0), points[1] = Point<int>(2, 1), points[2] = Point<int>(-4, -2), points[3] = Point<int>(-100, -50), points[4] = Point<int>(20, 10);

    auto ch = convex_hull(points);

    ASSERT_EQ(ch.size(), 2);

    ASSERT_EQ(ch[0], Point<int>(-100, -50));
    ASSERT_EQ(ch[1], Point<int>(20, 10));
}

TEST(ConvexHullTest, HorizontalLine) {
    vector<Point<int>> points(3);
    points[0] = Point<int>(-1, 2), points[1] = Point<int>(1, 2), points[2] = Point<int>(3, 2);

    auto ch = convex_hull(points);

    ASSERT_EQ(ch.size(), 2);

    ASSERT_EQ(ch[0], Point<int>(-1, 2));
    ASSERT_EQ(ch[1], Point<int>(3, 2));
}

TEST(ConvexHullTest, VerticalLine) {
    vector<Point<int>> points(3);
    points[0] = Point<int>(-1, 2), points[1] = Point<int>(-1, 3), points[2] = Point<int>(-1, -10);

    auto ch = convex_hull(points);

    ASSERT_EQ(ch.size(), 2);

    ASSERT_EQ(ch[0], Point<int>(-1, -10));
    ASSERT_EQ(ch[1], Point<int>(-1, 3));
}

TEST(ConvexHullTest, RandomLarge) {
    int t = 100;

    while (t--) {
        int n = 10000;

        const int MAX = 1000;

        random_device seed_gen;
        mt19937 engine(seed_gen());

        uniform_int_distribution<> dist(-MAX, MAX);

        vector<Point<int>> points(n);

        for (int i = 0; i < n; i++) {
            points[i] = {dist(engine), dist(engine)};
        }

        auto ch = convex_hull(points);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < ch.size(); j++) {
                ASSERT_GE(cross(ch[(j + 1) % ch.size()] - ch[j], points[i] - ch[j]), 0);
            }
        }
    }
}
