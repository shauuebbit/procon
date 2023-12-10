#include "data_structure/convex_hull_trick.hpp"

#include <gtest/gtest.h>

#include <functional>
#include <random>
#include <vector>

using namespace std;

TEST(ConvexHullTrickTest, OneLine) {
    ConvexHullTrick<int> cht;

    ASSERT_TRUE(cht.add_line({2, -3}));
    ASSERT_EQ(cht.get(-100), 2 * (-100) - 3);
    ASSERT_EQ(cht.get(0), 2 * 0 - 3);
    ASSERT_EQ(cht.get(10), 2 * 10 - 3);
}

TEST(ConvexHullTrickTest, MonotonicAddMin) {
    constexpr long long INF = 1ll << 60;

    ConvexHullTrick<long long> cht;

    std::vector<std::pair<long long, long long>> lines;

    ASSERT_TRUE(cht.add_line({-100, 10000}));
    lines.emplace_back(-100, 10000);

    ASSERT_TRUE(cht.add_line({0, 6000}));
    lines.emplace_back(0, 6000);

    ASSERT_FALSE(cht.add_line({0, 10000}));
    lines.emplace_back(0, 10000);

    ASSERT_TRUE(cht.add_line({0, 5000}));
    lines.emplace_back(0, 5000);

    ASSERT_TRUE(cht.add_line({2, 10}));
    lines.emplace_back(2, 10);

    ASSERT_TRUE(cht.add_line({100, 0}));
    lines.emplace_back(100, 0);

    for (long long x = -100; x < 200; x++) {
        long long min_y = INF;

        for (auto line : lines) {
            auto [a, b] = line;

            min_y = std::min(a * x + b, min_y);
        }

        ASSERT_EQ(cht.get(x), min_y);
    }
}

TEST(ConvexHullTrickTest, MonotonicAddMax) {
    constexpr long long INF = 1ll << 60;

    ConvexHullTrick<long long, greater<long long>> cht;

    std::vector<std::pair<long long, long long>> lines;

    ASSERT_TRUE(cht.add_line({-100, -10000}));
    lines.emplace_back(-100, -10000);

    ASSERT_TRUE(cht.add_line({0, -6000}));
    lines.emplace_back(0, -6000);

    ASSERT_FALSE(cht.add_line({0, -10000}));
    lines.emplace_back(0, -10000);

    ASSERT_TRUE(cht.add_line({0, -5000}));
    lines.emplace_back(0, -5000);

    ASSERT_TRUE(cht.add_line({2, -10}));
    lines.emplace_back(2, -10);

    ASSERT_TRUE(cht.add_line({100, 0}));
    lines.emplace_back(100, 0);

    for (long long x = -100; x < 200; x++) {
        long long max_y = -INF;

        for (auto line : lines) {
            auto [a, b] = line;

            max_y = std::max(a * x + b, max_y);
        }

        ASSERT_EQ(cht.get(x), max_y);
    }
}

TEST(ConvexHullTrickTest, Min) {
    constexpr long long INF = 1ll << 60;

    ConvexHullTrick<long long> cht;

    std::vector<std::pair<long long, long long>> lines;

    ASSERT_TRUE(cht.add_line({-100, 10000}));
    lines.emplace_back(-100, 10000);

    ASSERT_TRUE(cht.add_line({100, 0}));
    lines.emplace_back(100, 0);

    ASSERT_FALSE(cht.add_line({0, 6000}));
    lines.emplace_back(0, 6000);

    ASSERT_TRUE(cht.add_line({0, 4000}));
    lines.emplace_back(0, 4000);

    ASSERT_FALSE(cht.add_line({0, 10000}));
    lines.emplace_back(0, 10000);

    ASSERT_TRUE(cht.add_line({2, 10}));
    lines.emplace_back(2, 10);

    for (long long x = -100; x < 200; x++) {
        long long min_y = INF;

        for (auto line : lines) {
            auto [a, b] = line;

            min_y = std::min(a * x + b, min_y);
        }

        ASSERT_EQ(cht.get(x), min_y);
    }
}

TEST(ConvexHullTrickTest, Max) {
    constexpr long long INF = 1ll << 60;

    ConvexHullTrick<long long, greater<long long>> cht;

    std::vector<std::pair<long long, long long>> lines;

    ASSERT_TRUE(cht.add_line({-100, -10000}));
    lines.emplace_back(-100, -10000);

    ASSERT_TRUE(cht.add_line({100, 0}));
    lines.emplace_back(100, 0);

    ASSERT_FALSE(cht.add_line({0, -6000}));
    lines.emplace_back(0, -6000);

    ASSERT_TRUE(cht.add_line({0, -4000}));
    lines.emplace_back(0, -4000);

    ASSERT_FALSE(cht.add_line({0, -10000}));
    lines.emplace_back(0, -10000);

    ASSERT_TRUE(cht.add_line({2, -10}));
    lines.emplace_back(2, -10);

    for (long long x = -100; x < 200; x++) {
        long long max_y = -INF;

        for (auto line : lines) {
            auto [a, b] = line;

            max_y = std::max(a * x + b, max_y);
        }

        ASSERT_EQ(cht.get(x), max_y);
    }
}

TEST(ConvexHullTrick, RandomMin) {
    int q = 2000;

    ConvexHullTrick<long long> cht;

    std::vector<std::pair<long long, long long>> lines;

    constexpr int LINE_PARAM_MAX = 50;
    constexpr int QUERY_MAX = LINE_PARAM_MAX * 2 + 1;
    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist_line(-LINE_PARAM_MAX, LINE_PARAM_MAX);

    constexpr long long INF = 1ll << 60;

    for (int t = 0; t < q; t++) {
        long long a = dist_line(engine);
        long long b = dist_line(engine);

        cht.add_line({a, b});
        lines.emplace_back(a, b);

        for (int x = -QUERY_MAX; x <= QUERY_MAX; x++) {
            long long min_y = INF;

            for (auto [a, b] : lines) {
                min_y = min(a * x + b, min_y);
            }

            ASSERT_EQ(cht.get(x), min_y);
        }
    }
}

TEST(ConvexHullTrick, RandomMax) {
    int q = 200;

    ConvexHullTrick<long long, greater<long long>> cht;

    std::vector<std::pair<long long, long long>> lines;

    constexpr int LINE_PARAM_MAX = 4000;
    constexpr int QUERY_MAX = LINE_PARAM_MAX * 2 + 1;
    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist_line(-LINE_PARAM_MAX, LINE_PARAM_MAX);

    constexpr long long INF = 1ll << 60;

    for (int t = 0; t < q; t++) {
        long long a = dist_line(engine);
        long long b = dist_line(engine);

        cht.add_line({a, b});
        lines.emplace_back(a, b);

        for (int x = -QUERY_MAX; x <= QUERY_MAX; x++) {
            long long max_y = -INF;

            for (auto [a, b] : lines) {
                max_y = max(a * x + b, max_y);
            }

            ASSERT_EQ(cht.get(x), max_y);
        }
    }
}
