#include "math/fast_fourier_transform.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <random>

using namespace std;

TEST(FastFourierTransform, RandomConvolution) {
    int n = 10000, m = 8000;

    const int MAX = 100000;

    using T = long double;

    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist(-MAX, MAX);

    vector<complex<T>> f(n + 1);
    vector<complex<T>> g(m + 1);

    for (int i = 0; i <= n; i++) {
        f[i] = static_cast<T>(dist(engine));
    }

    for (int j = 0; j <= m; j++) {
        g[j] = static_cast<T>(dist(engine));
    }

    auto h = convolute(f, g);

    for (int k = 0; k <= n + m; k++) {
        T c = 0;
        for (int i = max(k - m, 0); i <= k && i <= n; i++) {
            c += f[i].real() * g[k - i].real();
        }

        ASSERT_EQ(static_cast<long long>(h[k].real() + 0.5), static_cast<long long>(c + 0.5));
    }
}
