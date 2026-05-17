#include "string/trie.hpp"

#include <gtest/gtest.h>

using namespace std;

TEST(TrieTest, Construct) {
    Trie<int> trie;
}

TEST(TrieTest, Contains1) {
    Trie<char> trie;

    std::string s1 = "abaaba";
    std::string s2 = "abbaab";

    trie.add(s1);
    trie.add(s2);

    ASSERT_TRUE(trie.contains(s1));
    ASSERT_TRUE(trie.contains(s2));

    std::string p1 = "abac";
    std::string p2 = "aba";

    ASSERT_FALSE(trie.contains(p1));
    ASSERT_TRUE(trie.contains(p2));
}

TEST(TrieTest, Contains2) {
    Trie<int> trie;

    std::vector<int> s1 = {2, 1, 1, 2, 3};
    std::vector<int> s2 = {2, 2, 1, 2, 3};
    std::vector<int> s3 = {1};
    std::vector<int> s4 = {2, 2, 1, 3};
    std::vector<int> s5 = {2, 1, 3};

    trie.add(s1);
    trie.add(s2);
    trie.add(s3);
    trie.add(s4);
    trie.add(s5);

    ASSERT_TRUE(trie.contains(s1));
    ASSERT_TRUE(trie.contains(s2));
    ASSERT_TRUE(trie.contains(s3));
    ASSERT_TRUE(trie.contains(s4));
    ASSERT_TRUE(trie.contains(s5));

    std::string p1 = {2};
    std::string p2 = {3};
    std::string p3 = {2, 1, 2};
    std::string p4 = {2, 1, 3};

    ASSERT_TRUE(trie.contains(p1));
    ASSERT_FALSE(trie.contains(p2));
    ASSERT_FALSE(trie.contains(p3));
    ASSERT_TRUE(trie.contains(p4));
}
