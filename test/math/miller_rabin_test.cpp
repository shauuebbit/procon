#include "math/miller_rabin.hpp"

#include <gtest/gtest.h>

#include <vector>

using namespace std;

TEST(MillerRabinTest, DeterministicVersion) {
    constexpr int MAX = 1e7;

    vector<char> sieve(MAX + 1, 1);

    sieve[0] = sieve[1] = 0;

    for (int p = 2; p <= MAX; p++) {
        if (sieve[p]) {
            for (int q = p * 2; q <= MAX; q += p) {
                sieve[q] = 0;
            }
        }
    }

    for (int x = 0; x <= MAX; x++) {
        int res = is_prime(x);
        ASSERT_EQ(res, sieve[x]);
    }
}

TEST(MillerRabinTest, StochasticVersion) {
    constexpr int MAX = 1e6;

    constexpr size_t NUM_REPEAT = 7;

    std::random_device seed_gen;
    const auto seed = seed_gen();

    vector<char> sieve(MAX + 1, 1);

    sieve[0] = sieve[1] = 0;

    for (int p = 2; p <= MAX; p++) {
        if (sieve[p]) {
            for (int q = p * 2; q <= MAX; q += p) {
                sieve[q] = 0;
            }
        }
    }

    for (int x = 0; x <= MAX; x++) {
        int res = is_prime<int, long long>(x, NUM_REPEAT, seed);
        ASSERT_EQ(res, sieve[x]);
    }
}
