#include "geometry/point.hpp"

#include <gtest/gtest.h>

TEST(PointTest, Add) {
    Point<int> p1(2, 3);
    Point<int> p2(-10, 50);

    Point<int> p3(-8, 53);

    ASSERT_EQ(p1 + p2, p3);

    p1 += p2;

    ASSERT_EQ(p1, p3);
}

TEST(PointTest, Sub) {
    Point<long long> p1(10000000000ll, 0ll);
    Point<long long> p2(1000ll, -1000ll);

    Point<long long> p3(9999999000ll, 1000ll);

    ASSERT_EQ(p1 - p2, p3);

    p1 -= p2;

    ASSERT_EQ(p1, p3);
}

TEST(PointTest, Comparation) {
    Point<int> p1(2, 3);
    Point<int> p2(1, 2);

    ASSERT_GT(p1, p2);

    p1 = Point<int>(1, 0);

    ASSERT_LT(p1, p2);
}

TEST(PointTest, Zero) {
    Point<int> p;

    ASSERT_EQ(p.x, 0);
    ASSERT_EQ(p.y, 0);
}

TEST(PointTest, Cross) {
    Point<int> p1(1, 2);
    Point<int> p2(-1, 3);

    ASSERT_EQ(cross(p1, p2), 5);
}
