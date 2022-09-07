#pragma once

template <typename T, typename U>
constexpr T gcd(T a, U b) {
    while (b) {
        a %= b;
        b ^= a;
        a ^= b;
        b ^= a;
    }
    return a;
}

template <typename T, typename U>
constexpr T lcm(T a, U b) {
    return a / gcd(a, b) * b;
}
