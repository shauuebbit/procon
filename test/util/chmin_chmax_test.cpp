#include "util/chmin_chmax.hpp"

#include <gtest/gtest.h>

TEST(ChminChmaxTest, Chmin) {
    int n = 1000;
    ASSERT_FALSE(chmin(n, 1001));
    ASSERT_EQ(n, 1000);
    ASSERT_FALSE(chmin(n, 1000));
    ASSERT_EQ(n, 1000);
    ASSERT_TRUE(chmin(n, 999));
    ASSERT_EQ(n, 999);
}

TEST(ChminChmaxTest, Chmax) {
    int n = 1000;
    ASSERT_FALSE(chmax(n, 999));
    ASSERT_EQ(n, 1000);
    ASSERT_FALSE(chmax(n, 1000));
    ASSERT_EQ(n, 1000);
    ASSERT_TRUE(chmax(n, 1001));
    ASSERT_EQ(n, 1001);
}
