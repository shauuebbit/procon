#pragma once

#ifndef CONST_INT_MOD
#define CONST_INT_MOD
constexpr int MOD = 998244353;
#endif

template <typename T, typename U, typename V>
constexpr T power(T b, U e, V mod) {
    if (b >= mod) b %= mod;
    T ret = 1;
    while (e) {
        if (e & 1) {
            ret *= b;
            ret %= mod;
        }

        b *= b;
        b %= mod;
        e >>= 1;
    }

    return ret;
}

template <typename T, typename U>
constexpr T power(T b, U e) {
    return power(b, e, MOD);
}
