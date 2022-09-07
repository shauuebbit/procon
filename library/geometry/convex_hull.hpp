#pragma once

#include <algorithm>
#include <complex>
#include <vector>

#include "point.hpp"

template <typename T>
std::vector<Point<T>> convex_hull(std::vector<Point<T>> points) {
    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());

    int n = points.size(), k = 0;
    if (n < 3)
        return points;
    else {
        std::vector<Point<T>> ret(n << 1);
        for (int i = 0; i < n; ret[k++] = points[i++]) {
            while (k >= 2 && cross(ret[k - 1] - ret[k - 2], points[i] - ret[k - 1]) <= 0) --k;
        }
        for (int i = n - 2, t = k + 1; i >= 0; ret[k++] = points[i--]) {
            while (k >= t && cross(ret[k - 1] - ret[k - 2], points[i] - ret[k - 1]) <= 0) --k;
        }
        ret.resize(k - 1);
        return ret;
    }
}

template <typename T>
std::vector<std::complex<T>> convex_hull(std::vector<std::complex<T>> points) {
    std::sort(points.begin(), points.end(), [](const std::complex<T>& a, const std::complex<T>& b) {
        return (std::real(a) < std::real(b)) || ((std::real(a) == std::real(b)) && std::imag(a) < std::imag(b));
    });
    points.erase(std::unique(points.begin(), points.end()), points.end());

    int n = points.size(), k = 0;
    if (n < 3)
        return points;
    else {
        auto cross = [](const std::complex<T>& a, const std::complex<T>& b) {
            return std::real(a) * std::imag(b) - std::imag(a) * std::real(b);
        };

        std::vector<std::complex<T>> ret(n << 1);
        for (int i = 0; i < n; ret[k++] = points[i++]) {
            while (k >= 2 && cross(ret[k - 1] - ret[k - 2], points[i] - ret[k - 1]) <= 0) --k;
        }
        for (int i = n - 2, t = k + 1; i >= 0; ret[k++] = points[i--]) {
            while (k >= t && cross(ret[k - 1] - ret[k - 2], points[i] - ret[k - 1]) <= 0) --k;
        }
        ret.resize(k - 1);
        return ret;
    }
}
