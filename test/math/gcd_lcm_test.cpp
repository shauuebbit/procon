#include "math/gcd_lcm.hpp"

#include <gtest/gtest.h>

TEST(GCDLCMTest, GCD) {
    ASSERT_EQ(gcd(12, 18), 6);
    ASSERT_EQ(gcd(2, 0), 2);
    ASSERT_EQ(gcd(4, 1), 1);
}

TEST(GCDLCMTest, LCM) {
    ASSERT_EQ(lcm(12, 18), 36);
    ASSERT_EQ(lcm(2, 0), 0);
    ASSERT_EQ(lcm(4, 1), 4);
}

TEST(GCDLCMTest, ExtGCD) {
    constexpr auto test = [](int a, int b) {
        auto [x, y, g] = extgcd(a, b);
        ASSERT_EQ(a * x + b * y, g);
        ASSERT_EQ(g, gcd(a, b));
    };

    test(12, 18);
    test(2, 0);
    test(4, 1);
}
