#include "data_structure/sliding_window_aggregation.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <vector>

using namespace std;

TEST(SlidingWindowAggregationTest, SWAGEmpty) {
    int n = 10000;

    const int INF = 1 << 30;
    auto f = [](int x, int y) { return min(x, y); };

    SlidingWindowAggregation<int, decltype(f)> swag(f, INF);

    for (int i = 0; i < n; i++) {
        swag.push(i);
        swag.pop();

        ASSERT_TRUE(swag.empty());
        ASSERT_EQ(swag.fold(), INF);
    }

    for (int i = 0; i < n; i++) {
        swag.push(i);

        ASSERT_FALSE(swag.empty());
    }

    for (int i = 0; i < n; i++) {
        ASSERT_FALSE(swag.empty());

        swag.pop();
    }

    ASSERT_TRUE(swag.empty());
    ASSERT_EQ(swag.fold(), INF);
}

TEST(SlidingWindowAggregationTest, SWAGClear) {
    int n = 10000;

    const int INF = 1 << 30;
    auto f = [](int x, int y) { return min(x, y); };

    SlidingWindowAggregation<int, decltype(f)> swag(f, INF);

    for (int i = 0; i < n; i++) {
        swag.push(i);

        ASSERT_FALSE(swag.empty());
    }

    for (int i = 0; i < (n >> 1); i++) {
        ASSERT_FALSE(swag.empty());

        swag.pop();
    }

    ASSERT_FALSE(swag.empty());
    
    swag.clear();

    ASSERT_TRUE(swag.empty());
    ASSERT_EQ(swag.fold(), INF);
}

TEST(SlidingWindowAggregationTest, SWAGSlideMin) {
    int n = 10000;

    const int INF = 1 << 30;
    auto f = [](int x, int y) { return min(x, y); };

    SlidingWindowAggregation<int, decltype(f)> swag(f, INF);

    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist_val(-INF + 1, INF - 1);

    vector<int> a(n, INF);

    for (int i = 0; i < n; i++) {
        a[i] = dist_val(engine);
    }

    for (int d = 1; d <= 5; d++) {
        for (int l = 0, r = 0; l < n; l++) {
            while (r < n && r - l < d) {
                swag.push(a[r++]);
            }

            int v = INF;

            for (int i = l; i < r; i++) v = min(v, a[i]);

            ASSERT_EQ(swag.size(), r - l);
            ASSERT_EQ(swag.fold(), v);

            swag.pop();
        }
    }
}

TEST(SlidingWindowAggregationTest, SWAGSlideLinearComposition) {
    int n = 10000;

    const int MAX = 10;

    struct S {
        long long a;
        long long b;

        bool operator==(const S& rhs) const {
            return a == rhs.a && b == rhs.b;
        }
    };

    auto c = [](const S& f, const S& g) -> S {
        return {g.a * f.a, g.a * f.b + g.b};
    };

    const S ID = {1ll, 0ll};

    SlidingWindowAggregation<S, decltype(c)> swag(c, ID);

    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist_val(-MAX, MAX);

    vector<S> a(n, ID);

    for (int i = 0; i < n; i++) {
        a[i] = {dist_val(engine), dist_val(engine)};
    }

    for (int d = 1; d <= 5; d++) {
        for (int l = 0, r = 0; l < n; l++) {
            while (r < n && r - l < d) {
                swag.push(a[r++]);
            }

            S v = ID;

            for (int i = l; i < r; i++) v = c(v, a[i]);

            ASSERT_EQ(swag.fold(), v);

            swag.pop();
        }
    }
}

TEST(SlidingWindowAggregationTest, DoubleEndedSWAGEmpty) {
    int n = 10000;

    const int INF = 1 << 30;
    auto f = [](int x, int y) { return min(x, y); };

    DoubleEndedSlidingWindowAggregation<int, decltype(f)> swag(f, INF);

    for (int i = 0; i < n; i++) {
        swag.push_back(i);
        swag.pop_front();

        ASSERT_TRUE(swag.empty());
        ASSERT_EQ(swag.fold(), INF);
    }

    for (int i = 0; i < n; i++) {
        swag.push_back(i);

        ASSERT_FALSE(swag.empty());
    }

    for (int i = 0; i < n; i++) {
        ASSERT_FALSE(swag.empty());

        swag.pop_front();
    }

    ASSERT_TRUE(swag.empty());
    ASSERT_EQ(swag.fold(), INF);

    for (int i = 0; i < n; i++) {
        swag.push_front(i);
        swag.pop_back();

        ASSERT_TRUE(swag.empty());
        ASSERT_EQ(swag.fold(), INF);
    }

    for (int i = 0; i < n; i++) {
        swag.push_front(i);

        ASSERT_FALSE(swag.empty());
    }

    for (int i = 0; i < n; i++) {
        ASSERT_FALSE(swag.empty());

        swag.pop_back();
    }

    ASSERT_TRUE(swag.empty());
    ASSERT_EQ(swag.fold(), INF);
}

TEST(SlidingWindowAggregationTest, DoubleEndedSWAGClear) {
    int n = 10000;

    const int INF = 1 << 30;
    auto f = [](int x, int y) { return min(x, y); };

    DoubleEndedSlidingWindowAggregation<int, decltype(f)> swag(f, INF);

    for (int i = 0; i < n; i++) {
        swag.push_front(i);

        ASSERT_FALSE(swag.empty());
    }

    for (int i = 0; i < (n >> 1); i++) {
        ASSERT_FALSE(swag.empty());

        swag.pop_back();
    }

    ASSERT_FALSE(swag.empty());
    
    swag.clear();

    ASSERT_TRUE(swag.empty());
    ASSERT_EQ(swag.fold(), INF);

    for (int i = 0; i < n; i++) {
        swag.push_back(i);

        ASSERT_FALSE(swag.empty());
    }

    for (int i = 0; i < (n >> 1); i++) {
        ASSERT_FALSE(swag.empty());

        swag.pop_front();
    }

    ASSERT_FALSE(swag.empty());
    
    swag.clear();

    ASSERT_TRUE(swag.empty());
    ASSERT_EQ(swag.fold(), INF);
}

TEST(SlidingWindowAggregationTest, DoubleEndedSWAGSlideMin) {
    int n = 10000;

    const int INF = 1 << 30;
    auto f = [](int x, int y) { return min(x, y); };

    DoubleEndedSlidingWindowAggregation<int, decltype(f)> swag(f, INF);

    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist_val(-INF + 1, INF - 1);

    vector<int> a(n, INF);

    for (int i = 0; i < n; i++) {
        a[i] = dist_val(engine);
    }

    for (int d = 1; d <= 5; d++) {
        for (int l = 0, r = 0; l < n; l++) {
            while (r < n && r - l < d) {
                swag.push_back(a[r++]);
            }

            int v = INF;

            for (int i = l; i < r; i++) v = min(v, a[i]);

            ASSERT_EQ(swag.size(), r - l);
            ASSERT_EQ(swag.fold(), v);

            swag.pop_front();
        }
    }

    swag.clear();
    ASSERT_TRUE(swag.empty());

    for (int d = 1; d <= 5; d++) {
        for (int l = n, r = n; r > 0; r--) {
            while (l > 0 && r - l < d) {
                swag.push_front(a[--l]);
            }

            int v = INF;

            for (int i = l; i < r; i++) v = min(a[i], v);

            ASSERT_EQ(swag.size(), r - l);
            ASSERT_EQ(swag.fold(), v);

            swag.pop_back();
        }
    }
}

TEST(SlidingWindowAggregationTest, DoubleEndedSWAGSlideLinearComposition) {
    int n = 10000;

    const int MAX = 10;

    struct S {
        long long a;
        long long b;

        bool operator==(const S& rhs) const {
            return a == rhs.a && b == rhs.b;
        }
    };

    auto c = [](const S& f, const S& g) -> S {
        return {g.a * f.a, g.a * f.b + g.b};
    };

    const S ID = {1ll, 0ll};

    DoubleEndedSlidingWindowAggregation<S, decltype(c)> swag(c, ID);

    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist_val(-MAX, MAX);

    vector<S> a(n, ID);

    for (int i = 0; i < n; i++) {
        a[i] = {dist_val(engine), dist_val(engine)};
    }

    for (int d = 1; d <= 5; d++) {
        for (int l = 0, r = 0; l < n; l++) {
            while (r < n && r - l < d) {
                swag.push_back(a[r++]);
            }

            S v = ID;

            for (int i = l; i < r; i++) v = c(v, a[i]);

            ASSERT_EQ(swag.fold(), v);

            swag.pop_front();
        }
    }

    swag.clear();
    ASSERT_TRUE(swag.empty());

    for (int d = 1; d <= 5; d++) {
        for (int l = n, r = n; r > 0; r--) {
            while (l > 0 && r - l < d) {
                swag.push_front(a[--l]);
            }

            S v = ID;

            for (int i = l; i < r; i++) v = c(v, a[i]);

            ASSERT_EQ(swag.size(), r - l);
            ASSERT_EQ(swag.fold(), v);

            swag.pop_back();
        }
    }
}
