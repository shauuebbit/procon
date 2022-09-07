#include "math/gcd.hpp"

#include <gtest/gtest.h>

TEST(GCDTest, GCD) {
    ASSERT_EQ(gcd(12, 18), 6);
    ASSERT_EQ(gcd(2, 0), 2);
    ASSERT_EQ(gcd(4, 1), 1);
}

TEST(GCDTest, LCM) {
    ASSERT_EQ(lcm(12, 18), 36);
    ASSERT_EQ(lcm(2, 0), 0);
    ASSERT_EQ(lcm(4, 1), 4);
}
