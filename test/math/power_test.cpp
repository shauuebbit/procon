#include "math/power.hpp"

#include <gtest/gtest.h>

TEST(PowerTest, Small1) {
    long long b = 123;
    int n = 100000;

    long long x = 1;

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(power(b, i), x);
        x *= b;
        x %= MOD;
    }
    ASSERT_EQ(power(b, n), x);
}

TEST(PowerTest, Small2) {
    long long b = 1037015;
    int n = 100000;

    long long x = 1;

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(power(b, i), x);
        x *= b;
        x %= MOD;
    }
    ASSERT_EQ(power(b, n), x);
}
