#include "string/kmp.hpp"

#include <gtest/gtest.h>

#include <string>

using namespace std;

TEST(KMPTest, SmallSearch) {
    const string target = "aabacabbaaababbabaabbbbaba";

    for (int l = 0; l < target.size(); l++) {
        for (int r = l + 1; r <= target.size(); r++) {
            const string pattern = target.substr(l, r - l);

            int pos = search(target, pattern);
            ASSERT_GE(pos, 0);
            ASSERT_LE(pos, l);
            ASSERT_EQ(search(target, pattern + "d"), -1);
        }
    }

    for (const string& pattern : {"d", "abababababab", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"}) {
        ASSERT_EQ(search(target, pattern), -1);
    }
}
