#pragma once

#include <tuple>

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

template <typename T, typename U>
constexpr std::tuple<T, T, T> extgcd(T a, U b) {
    if (a == 0) return {0, 1, b};
    else if (b == 0) return {1, 0, a};

    std::tuple<T, T, T> aa = {1, 0, a};
    std::tuple<T, T, T> bb = {0, 1, b};
    std::tuple<T, T, T> tt;

    constexpr auto add = [](const std::tuple<T, T, T>& lhs, const std::tuple<T, T, T>& rhs) -> std::tuple<T, T, T> {
        auto [lhs0, lhs1, lhs2] = lhs;
        auto [rhs0, rhs1, rhs2] = rhs;
        return {lhs0 + rhs0, lhs1 + rhs1, lhs2 + rhs2};
    };

    constexpr auto mul = [](const std::tuple<T, T, T>& lhs, const T& rhs) -> std::tuple<T, T, T> {
        auto [lhs0, lhs1, lhs2] = lhs;
        return {lhs0 * rhs, lhs1 * rhs, lhs2 * rhs};
    };

    while (std::get<2>(bb) != 0) {
        T w = std::get<2>(aa) / std::get<2>(bb);
        tt = add(aa, mul(bb, -w));
        aa = bb;
        bb = tt;
    }

    return aa;
}
