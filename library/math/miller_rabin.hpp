#pragma once

#include <random>
#include <vector>

#include "power.hpp"

template <typename T, typename U>
bool is_prime(T n, const std::vector<U>& b) {
    if (n < 2) return false;

    U d = n - 1;
    int s = 0;
    for (; d % 2 == 0; d /= 2, ++s);

    auto test = [&](U a) {
        if (a % n == 0) return true;

        U t = power(a, d, n);
        if (t == 1) return true;

        for (int k = 0; k < s; k++) {
            if (t == n - 1) return true;
            t = t * t % n;
        }

        return false;
    };

    for (auto a : b) {
        if (!test(a)) {
            return false;
        }
    }

    return true;
}

template <typename T, typename U, typename S = decltype(std::random_device()())>
bool is_prime(T n, size_t num_repeat, S seed = std::random_device()()) {
    std::mt19937 engine(seed);

    std::uniform_int_distribution<T> dist(1, std::numeric_limits<T>::max());

    std::vector<U> b(num_repeat);

    for (size_t i = 0; i < num_repeat; i++) {
        b[i] = dist(engine);
    }

    return is_prime(n, b);
}

inline bool is_prime(unsigned long long n) {
    const std::vector<__int128_t> b{2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    return is_prime(n, b);
}
