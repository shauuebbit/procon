#include "math/division.hpp"

#include <gtest/gtest.h>

TEST(DivisionTest, Floor1) {
    constexpr int denominator = 7;

    constexpr int q_min = -100;
    constexpr int q_max = 100;

    int count_tests = 0;

    for (int q = q_min; q <= q_max; q++) {
        for (int numerator = denominator * q; numerator < denominator * (q + 1); numerator++) {
            ASSERT_EQ(div_floor(numerator, denominator), q);

            ++count_tests;
        }
    }

    ASSERT_EQ(count_tests, abs(denominator) * (q_max - q_min + 1));
}

TEST(DivisionTest, Floor2) {
    constexpr int denominator = -7;

    constexpr int q_min = -100;
    constexpr int q_max = 100;

    int count_tests = 0;

    for (int q = q_min; q <= q_max; q++) {
        for (int numerator = denominator * q; numerator > denominator * (q + 1); numerator--) {
            ASSERT_EQ(div_floor(numerator, denominator), q);

            ++count_tests;
        }
    }

    ASSERT_EQ(count_tests, abs(denominator) * (q_max - q_min + 1));
}

TEST(DivisionTest, Ceil1) {
    constexpr int denominator = 7;

    constexpr int q_min = -100;
    constexpr int q_max = 100;

    int count_tests = 0;

    for (int q = q_min; q <= q_max; q++) {
        for (int numerator = denominator * q; numerator > denominator * (q - 1); numerator--) {
            ASSERT_EQ(div_ceil(numerator, denominator), q);

            ++count_tests;
        }
    }

    ASSERT_EQ(count_tests, abs(denominator) * (q_max - q_min + 1));
}

TEST(DivisionTest, Ceil2) {
    constexpr int denominator = -7;

    constexpr int q_min = -100;
    constexpr int q_max = 100;

    int count_tests = 0;

    for (int q = q_min; q <= q_max; q++) {
        for (int numerator = denominator * q; numerator < denominator * (q - 1); numerator++) {
            ASSERT_EQ(div_ceil(numerator, denominator), q);

            ++count_tests;
        }
    }

    ASSERT_EQ(count_tests, abs(denominator) * (q_max - q_min + 1));
}
