#include "math/binomial_coefficients.hpp"

#include <gtest/gtest.h>

#include <random>
#include <vector>

using namespace std;

#ifndef CONST_INT_MOD
#define CONST_INT_MOD
constexpr int MOD = 1000000009;
#endif

TEST(BinomialCoefficientsTest, Zero) {
    int n = 1000;

    BinomialCoefficients<MOD> binom(n);

    ASSERT_EQ(binom.get(-1, 0), 0);
    ASSERT_EQ(binom.get(n / 2, -1), 0);
    ASSERT_EQ(binom.get(n / 2, n / 2 + 1), 0);
}

TEST(BinomialCoefficientsTest, Small) {
    int n = 1000;

    BinomialCoefficients<MOD> binom(n);

    vector b(n + 1, vector<long long>(n + 1, 0ll));

    for (int i = 0; i <= n; i++) {
        b[i][0] = 1;

        for (int j = 1; j <= i; j++) {
            b[i][j] = b[i - 1][j - 1] + b[i - 1][j];
            if (b[i][j] >= MOD) b[i][j] -= MOD;
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            ASSERT_EQ(binom.get(i, j), b[i][j]);
        }
    }
}

#include "math/inverse.hpp"

TEST(BinomialCoefficientsTest, LargeRandom) {
    random_device seed_gen;
    mt19937 engine(seed_gen());

    int n = 1000000;
    int q = 100000;

    BinomialCoefficients<MOD> binom(n);

    uniform_int_distribution<> distrib(0, n);

    long long fact[n + 1];
    fact[0] = 1;

    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;

    for (int t = 0; t < q; t++) {
        int i = distrib(engine);
        int j = distrib(engine);

        if (i < j) swap(i, j);

        ASSERT_EQ(binom.get(i, j), fact[i] * inverse(fact[j]) % MOD * inverse(fact[i - j]) % MOD);
    }
}
