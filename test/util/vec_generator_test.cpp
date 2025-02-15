#include "util/vec_generator.hpp"

#include <gtest/gtest.h>

#include "math/power.hpp"

TEST(VecGeneratorTest, OneLenOneVal) {
    using T = int;
    constexpr size_t MIN_LEN = 2;
    constexpr size_t MAX_LEN = 2;
    constexpr T MIN_VAL = 3;
    constexpr T MAX_VAL = 3;

    std::set<std::vector<int>> s;

    for (auto v : VecGenerator(MIN_LEN, MAX_LEN, MIN_VAL, MAX_VAL)) {
        // len range check
        EXPECT_GE(v.size(), MIN_LEN);
        EXPECT_LE(v.size(), MAX_LEN);

        // value range check
        for (auto x : v) {
            EXPECT_GE(x, MIN_VAL);
            EXPECT_LE(x, MAX_VAL);
        }

        s.insert(v);
    }

    // completeness check
    EXPECT_EQ(s.size(), 1);
}

TEST(VecGeneratorTest, OneLenMultipleVal) {
    using T = int;
    constexpr size_t MIN_LEN = 2;
    constexpr size_t MAX_LEN = 2;
    constexpr T MIN_VAL = 1;
    constexpr T MAX_VAL = 5;

    std::set<std::vector<int>> s;

    for (auto v : VecGenerator(MIN_LEN, MAX_LEN, MIN_VAL, MAX_VAL)) {
        // len range check
        EXPECT_GE(v.size(), MIN_LEN);
        EXPECT_LE(v.size(), MAX_LEN);

        // value range check
        for (auto x : v) {
            EXPECT_GE(x, MIN_VAL);
            EXPECT_LE(x, MAX_VAL);
        }

        s.insert(v);
    }

    // completeness check
    size_t num = 0;
    for (size_t len = MIN_LEN; len <= MAX_LEN; len++) {
        num += power(MAX_VAL - MIN_VAL + 1, len);
    }
    EXPECT_EQ(s.size(), num);
}

TEST(VecGeneratorTest, MultipleLenOneValue) {
    using T = int;
    constexpr size_t MIN_LEN = 2;
    constexpr size_t MAX_LEN = 4;
    constexpr T MIN_VAL = 3;
    constexpr T MAX_VAL = 3;

    std::set<std::vector<int>> s;

    for (auto v : VecGenerator(MIN_LEN, MAX_LEN, MIN_VAL, MAX_VAL)) {
        // len range check
        EXPECT_GE(v.size(), MIN_LEN);
        EXPECT_LE(v.size(), MAX_LEN);

        // value range check
        for (auto x : v) {
            EXPECT_GE(x, MIN_VAL);
            EXPECT_LE(x, MAX_VAL);
        }

        s.insert(v);
    }

    // completeness check
    size_t num = 0;
    for (size_t len = MIN_LEN; len <= MAX_LEN; len++) {
        num += power(MAX_VAL - MIN_VAL + 1, len);
    }
    EXPECT_EQ(s.size(), num);
}

TEST(VecGeneratorTest, MultipleLenMultipleValue) {
    using T = int;
    constexpr size_t MIN_LEN = 2;
    constexpr size_t MAX_LEN = 4;
    constexpr T MIN_VAL = 1;
    constexpr T MAX_VAL = 5;

    std::set<std::vector<int>> s;

    for (auto v : VecGenerator(MIN_LEN, MAX_LEN, MIN_VAL, MAX_VAL)) {
        // len range check
        EXPECT_GE(v.size(), MIN_LEN);
        EXPECT_LE(v.size(), MAX_LEN);

        // value range check
        for (auto x : v) {
            EXPECT_GE(x, MIN_VAL);
            EXPECT_LE(x, MAX_VAL);
        }

        s.insert(v);
    }

    // completeness check
    size_t num = 0;
    for (size_t len = MIN_LEN; len <= MAX_LEN; len++) {
        num += power(MAX_VAL - MIN_VAL + 1, len);
    }
    EXPECT_EQ(s.size(), num);
}
