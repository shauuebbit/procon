#pragma once

template <typename T, typename U>
bool chmin(T& a, const U& b) {
    if (a <= b) return false;
    a = b;
    return true;
}
template <typename T, typename U>
bool chmax(T& a, const U& b) {
    if (a >= b) return false;
    a = b;
    return true;
}
