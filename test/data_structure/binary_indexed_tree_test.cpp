#include "data_structure/binary_indexed_tree.hpp"

#include <gtest/gtest.h>

TEST(BinaryIndexedTreeTest, AddIndexZero) {
    int n = 10;
    BinaryIndexedTree<int> bit(n);

    ASSERT_EQ(bit.sum(0), 0);
    ASSERT_EQ(bit.sum(1), 0);
    ASSERT_EQ(bit.sum(n - 2), 0);
    ASSERT_EQ(bit.sum(n - 1), 0);
    ASSERT_EQ(bit.sum(n), 0);

    ASSERT_TRUE(bit.add(0, 10));

    ASSERT_EQ(bit.sum(0), 10);
    ASSERT_EQ(bit.sum(1), 10);
    ASSERT_EQ(bit.sum(n - 2), 10);
    ASSERT_EQ(bit.sum(n - 1), 10);
    ASSERT_EQ(bit.sum(n), 10);
}

TEST(BinaryIndexedTreeTest, AddIndexLast) {
    int n = 10;
    BinaryIndexedTree<int> bit(n);

    ASSERT_EQ(bit.sum(0), 0);
    ASSERT_EQ(bit.sum(1), 0);
    ASSERT_EQ(bit.sum(n - 2), 0);
    ASSERT_EQ(bit.sum(n - 1), 0);
    ASSERT_EQ(bit.sum(n), 0);

    ASSERT_TRUE(bit.add(n - 1, 10));

    ASSERT_EQ(bit.sum(0), 0);
    ASSERT_EQ(bit.sum(1), 0);
    ASSERT_EQ(bit.sum(n - 2), 0);
    ASSERT_EQ(bit.sum(n - 1), 10);
    ASSERT_EQ(bit.sum(n), 10);
}

TEST(BinaryIndexedTreeTest, AddIndexOutOfRange) {
    int n = 10;
    BinaryIndexedTree<int> bit(n);

    ASSERT_EQ(bit.sum(0), 0);
    ASSERT_EQ(bit.sum(1), 0);
    ASSERT_EQ(bit.sum(n - 2), 0);
    ASSERT_EQ(bit.sum(n - 1), 0);
    ASSERT_EQ(bit.sum(n), 0);

    ASSERT_FALSE(bit.add(-2, 1));
    ASSERT_FALSE(bit.add(-1, 10));
    ASSERT_FALSE(bit.add(n, 100));
    ASSERT_FALSE(bit.add(n + 1, 10));

    ASSERT_EQ(bit.sum(0), 0);
    ASSERT_EQ(bit.sum(1), 0);
    ASSERT_EQ(bit.sum(n - 2), 0);
    ASSERT_EQ(bit.sum(n - 1), 0);
    ASSERT_EQ(bit.sum(n), 0);
}

TEST(BinaryIndexedTreeTest, LargeSizeSmallQuery) {
    int n = 1000000;
    BinaryIndexedTree<int> bit(n);

    ASSERT_EQ(bit.sum(n), 0);

    bit.add(0);

    ASSERT_EQ(bit.sum(0), 1);
    ASSERT_EQ(bit.sum(2), 1);

    bit.add(0, -2);

    ASSERT_EQ(bit.sum(0), -1);
    ASSERT_EQ(bit.sum(2), -1);

    ASSERT_FALSE(bit.add(n + 1));
    ASSERT_FALSE(bit.add(n));
    ASSERT_FALSE(bit.add(-1));
    ASSERT_FALSE(bit.add(-2));

    ASSERT_TRUE(bit.add(n - 1, 10));

    ASSERT_EQ(bit.sum(0), -1);
    ASSERT_EQ(bit.sum(n - 2), -1);
    ASSERT_EQ(bit.sum(n - 1), 9);

    bit.add(5, 2);

    ASSERT_EQ(bit.sum(4), -1);
    ASSERT_EQ(bit.sum(5), 1);
    ASSERT_EQ(bit.sum(n - 1), 11);
}

TEST(BinaryIndexedTreeTest, LowerBound) {
    int n = 1000000;
    BinaryIndexedTree<int> bit(n);

    ASSERT_EQ(bit.lower_bound(-1), 0);
    ASSERT_EQ(bit.lower_bound(0), 0);
    ASSERT_EQ(bit.lower_bound(1), n);

    bit.add(0, 1);

    ASSERT_EQ(bit.lower_bound(-1), 0);
    ASSERT_EQ(bit.lower_bound(0), 0);
    ASSERT_EQ(bit.lower_bound(1), 0);
    ASSERT_EQ(bit.lower_bound(2), n);

    bit.add(10, 100);

    ASSERT_EQ(bit.lower_bound(-1), 0);
    ASSERT_EQ(bit.lower_bound(0), 0);
    ASSERT_EQ(bit.lower_bound(100), 10);
    ASSERT_EQ(bit.lower_bound(101), 10);
    ASSERT_EQ(bit.lower_bound(102), n);
    ASSERT_EQ(bit.lower_bound(200), n);

    int i = n / 3 * 2;
    bit.add(i, 1000);

    ASSERT_EQ(bit.lower_bound(-1), 0);
    ASSERT_EQ(bit.lower_bound(0), 0);
    ASSERT_EQ(bit.lower_bound(100), 10);
    ASSERT_EQ(bit.lower_bound(101), 10);
    ASSERT_EQ(bit.lower_bound(102), i);

    ASSERT_EQ(bit.lower_bound(1000), i);
    ASSERT_EQ(bit.lower_bound(1101), i);
    ASSERT_EQ(bit.lower_bound(1102), n);
    ASSERT_EQ(bit.lower_bound(2000), n);
}
