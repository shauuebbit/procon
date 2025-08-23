#include "string/manacher.hpp"

#include <gtest/gtest.h>

using namespace std;

TEST(ManacherTest, Small1) {
    for (const string s : {"aabacabbaaababbabaabbbbaba", "d", "abababababab", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"}) {
        auto res = manacher(s);

        for (int i = 0; i < (int)s.size(); i++) {
            int r = 0;

            while (i - r >= 0 && i + r < (int)s.size() && s[i - r] == s[i + r]) ++r;
            ASSERT_EQ(res[i], r);
        }
    }
}

TEST(KMPTest, Small2) {
    const vector<int> s = {1, 0, 1, 0, 1, 1, 0, 0, 1, 2, 0, 1, 2, 0, 1, 1, 0, 0, 1, 0, 1, 0};

    auto res = manacher(s);

    for (int i = 0; i < (int)s.size(); i++) {
        int r = 0;

        while (i - r >= 0 && i + r < (int)s.size() && s[i - r] == s[i + r]) ++r;
        ASSERT_EQ(res[i], r);
    }
}
