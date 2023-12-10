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
