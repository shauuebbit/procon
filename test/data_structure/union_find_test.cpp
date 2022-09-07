#include "data_structure/union_find.hpp"

#include <gtest/gtest.h>

TEST(UnionFindTest, SameSmall) {
    int n = 10;
    UnionFind uf(n);

    uf.unite(0, 2);

    ASSERT_TRUE(uf.is_same(0, 2));
    ASSERT_FALSE(uf.is_same(0, 1));
}

TEST(UnionFindTest, SizeSmall) {
    int n = 10;
    UnionFind uf(n);

    ASSERT_EQ(uf.size(0), 1);

    ASSERT_EQ(uf.size(), n);

    uf.unite(0, 2);

    ASSERT_EQ(uf.size(), n - 1);

    ASSERT_EQ(uf.size(0), 2);

    ASSERT_EQ(uf.size(1), 1);

    ASSERT_EQ(uf.size(4), 1);

    ASSERT_EQ(uf.size(), n - 1);
}
