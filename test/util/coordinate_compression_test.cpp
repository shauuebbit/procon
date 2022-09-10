#include "util/coordinate_compression.hpp"

#include <gtest/gtest.h>

#include <vector>

using namespace std;

TEST(CoordinateCompressionTest, Add) {
    vector<long long> v = {1, 5, 3, 2, 3, 80000000000ll};
    Compressor<long long> cmp;

    for (auto x : v) {
        ASSERT_TRUE(cmp.add(x));
    }

    ASSERT_EQ(cmp.size(), 5);

    ASSERT_FALSE(cmp.add(4));

    ASSERT_EQ(cmp.size(), 5);

    ASSERT_EQ(cmp.compress(1), 0);
    ASSERT_EQ(cmp.compress(2), 1);
    ASSERT_EQ(cmp.compress(3), 2);
    ASSERT_EQ(cmp.compress(5), 3);
    ASSERT_EQ(cmp.compress(80000000000ll), 4);

    for (int i = 0; i < cmp.size(); i++) {
        ASSERT_EQ(cmp.compress(cmp.uncompress(i)), i);
    }
}

TEST(CoordinateCompressionTest, ConstructWithVector) {
    vector<int> v = {1, 5, 3, 2, 3, 8};
    Compressor<int> cmp(v);

    ASSERT_FALSE(cmp.add(4));

    ASSERT_EQ(cmp.size(), 5);

    ASSERT_FALSE(cmp.add(4));

    ASSERT_EQ(cmp.size(), 5);

    ASSERT_EQ(cmp.compress(1), 0);
    ASSERT_EQ(cmp.compress(2), 1);
    ASSERT_EQ(cmp.compress(3), 2);
    ASSERT_EQ(cmp.compress(5), 3);
    ASSERT_EQ(cmp.compress(8), 4);

    for (int i = 0; i < cmp.size(); i++) {
        ASSERT_EQ(cmp.compress(cmp.uncompress(i)), i);
    }
}
