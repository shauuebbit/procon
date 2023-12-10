#include "string/kmp.hpp"

#include <gtest/gtest.h>

#include <string>

using namespace std;

TEST(KMPTest, SmallSearch1) {
    const string target = "aabacabbaaababbabaabbbbaba";

    for (int l = 0; l < (int)target.size(); l++) {
        for (int r = l + 1; r <= (int)target.size(); r++) {
            const string pattern = target.substr(l, r - l);

            int pos = search(target, pattern);
            ASSERT_GE(pos, 0);
            ASSERT_LE(pos, l);
            ASSERT_EQ(search(target, pattern + "d"), -1);
        }
    }

    for (const string pattern : {"d", "abababababab", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"}) {
        ASSERT_EQ(search(target, pattern), -1);
    }
}

TEST(KMPTest, SmallSearch2) {
    const vector<int> target = {1, 0, 1, 0, 1, 1, 0, 0, 1, 2, 0, 1, 2, 0, 1, 1, 0, 0, 1, 0, 1, 0};

    for (int l = 0; l < (int)target.size(); l++) {
        for (int r = l + 1; r <= (int)target.size(); r++) {
            vector<int> pattern(r - l);
            for (int i = l; i < r; i++) pattern[i - l] = target[i];

            int pos = search(target, pattern);
            ASSERT_GE(pos, 0);
            ASSERT_LE(pos, l);

            pattern.push_back(10);
            ASSERT_EQ(search(target, pattern), -1);
        }
    }
}
