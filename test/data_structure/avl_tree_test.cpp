#include "data_structure/avl_tree.hpp"

#include <gtest/gtest.h>

#include <set>

using namespace std;

TEST(AVLTreeTest, LinearInsert1) {
    AVLTree<int> tree;

    int n = 300000;

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(tree.size(), i);
        tree.insert(i);
        ASSERT_FALSE(tree.empty());
    }
    ASSERT_EQ(tree.size(), n);
}

TEST(AVLTreeTest, LinearInsert2) {
    AVLTree<int> tree;

    int n = 300000;

    for (int i = n - 1; i >= 0; i--) {
        ASSERT_EQ(tree.size(), n - i - 1);
        tree.insert(i);
        ASSERT_FALSE(tree.empty());
    }
    ASSERT_EQ(tree.size(), n);
}

TEST(AVLTreeTest, LinearErase1) {
    AVLTree<int> tree;

    int n = 300000;

    for (int i = 0; i < n; i++) {
        tree.insert(i);
    }

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(tree.size(), n - i);
        ASSERT_FALSE(tree.empty());
        tree.erase(i);
    }
    ASSERT_EQ(tree.size(), 0);
    ASSERT_TRUE(tree.empty());
}

TEST(AVLTreeTest, LinearErase2) {
    AVLTree<int> tree;

    int n = 300000;

    for (int i = 0; i < n; i++) {
        tree.insert(i);
    }

    for (int i = n - 1; i >= 0; i--) {
        ASSERT_EQ(tree.size(), i + 1);
        ASSERT_FALSE(tree.empty());
        tree.erase(i);
    }
    ASSERT_EQ(tree.size(), 0);
    ASSERT_TRUE(tree.empty());
}

TEST(AVLTreeTest, LinearErase3) {
    AVLTree<int> tree;

    int n = 300000;

    for (int i = n - 1; i >= 0; i--) {
        tree.insert(i);
    }

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(tree.size(), n - i);
        ASSERT_FALSE(tree.empty());
        tree.erase(i);
    }
    ASSERT_EQ(tree.size(), 0);
    ASSERT_TRUE(tree.empty());
}

TEST(AVLTreeTest, LinearErase4) {
    AVLTree<int> tree;

    int n = 300000;

    for (int i = n - 1; i >= 0; i--) {
        tree.insert(i);
    }

    for (int i = n - 1; i >= 0; i--) {
        ASSERT_EQ(tree.size(), i + 1);
        ASSERT_FALSE(tree.empty());
        tree.erase(i);
    }
    ASSERT_EQ(tree.size(), 0);
    ASSERT_TRUE(tree.empty());
}

TEST(AVLTreeTest, InsertAndErase) {
    AVLTree<int> tree;

    multiset<int> s;

    int n = 3000;

    for (int i = 0; i < n; i++) {
        int r = i % 3;
        if (r == 0) {
            tree.insert(i);
            s.insert(i);
        } else if (r == 1) {
            tree.insert(i + 1);
            s.insert(i + 1);
        } else {
            tree.insert(i - 1);
            s.insert(i - 1);
        }

        ASSERT_EQ(tree.size(), s.size());

        if (i % 6 == 5) {
            tree.erase(i - 3);
            tree.erase(i - 1);

            s.erase(s.find(i - 3));
            s.erase(s.find(i - 1));
        }

        ASSERT_EQ(tree.size(), s.size());

        for (auto e : s) {
            ASSERT_TRUE(tree.contains(e));
        }
    }

    while (!s.empty()) {
        tree.erase(*s.begin());
        s.erase(s.begin());
    }

    ASSERT_TRUE(tree.empty());
}

TEST(AVLTreeTest, GetKthKey) {
    AVLTree<int> tree;

    multiset<int> s;

    int n = 3000;

    for (int i = 0; i < n; i++) {
        int r = i % 3;
        if (r == 0) {
            tree.insert(i);
            s.insert(i);
        } else if (r == 1) {
            tree.insert(i + 1);
            s.insert(i + 1);
        } else {
            tree.insert(i - 1);
            s.insert(i - 1);
        }

        if (i % 6 == 5) {
            tree.erase(i - 3);
            tree.erase(i - 1);

            s.erase(s.find(i - 3));
            s.erase(s.find(i - 1));
        }

        size_t ord = 0;
        for (auto e : s) {
            ASSERT_EQ(tree.get_kth_element(ord++), e);
        }
    }

    while (!s.empty()) {
        tree.erase(*s.begin());
        s.erase(s.begin());

        size_t ord = 0;
        for (auto e : s) {
            ASSERT_EQ(tree.get_kth_element(ord++), e);
        }
    }
}

TEST(AVLTreeTest, Clear) {
    AVLTree<int> tree;

    int n = 300000;

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(tree.size(), i);
        tree.insert(i);
    }

    tree.clear();

    ASSERT_TRUE(tree.empty());

    tree.insert(1);

    ASSERT_EQ(tree.size(), 1);
}
