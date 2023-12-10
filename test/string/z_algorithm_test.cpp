#include "string/z_algorithm.hpp"

#include <gtest/gtest.h>

using namespace std;

TEST(ManacherTest, Small1) {
    for (const string& s : {"aabacabbaaababbabaabbbbaba", "d", "abababababab", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"}) {
        auto res = z_algorithm(s);

        for (int i = 0; i < (int)s.size(); i++) {
            int l = 0;
            while (i + l < (int)s.size() && s[l] == s[i + l]) ++l;

            ASSERT_EQ(res[i], l);
        }
    }
}

TEST(KMPTest, Small2) {
    const vector<int> s = {1, 0, 1, 0, 1, 1, 0, 0, 1, 2, 0, 1, 2, 0, 1, 1, 0, 0, 1, 0, 1, 0};

    auto res = z_algorithm(s);

    for (int i = 0; i < (int)s.size(); i++) {
        int l = 0;
        while (i + l < (int)s.size() && s[l] == s[i + l]) ++l;

        ASSERT_EQ(res[i], l);
    }
}
