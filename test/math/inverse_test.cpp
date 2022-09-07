#include "math/inverse.hpp"

#include <gtest/gtest.h>

TEST(InverseTest, Small1) {
    constexpr long long a = inverse(5ll);
    ASSERT_EQ(a * 5 % MOD, 1);

    for (int x = 1; x <= 1000; x++) {
        long long y = inverse(static_cast<long long>(x));
        ASSERT_EQ(y * x % MOD, 1);
    }
}

TEST(InverseTest, Small2) {
    constexpr long long a = inverse(5ll, MOD);
    ASSERT_EQ(a * 5 % MOD, 1);

    for (int x = 1; x <= 1000; x++) {
        long long y = inverse(static_cast<long long>(x), MOD);
        ASSERT_EQ(y * x % MOD, 1);
    }
}
