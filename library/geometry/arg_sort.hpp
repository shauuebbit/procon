#pragma once

#include <algorithm>
#include <vector>
#include <utility>

#include "point.hpp"

template <typename T>
constexpr void arg_sort(std::vector<Point<T>>& points) {
    constexpr auto ord = [](const Point<T>& p) {
        if (p.y() > 0)
            return 1;
        else if (p.y() < 0)
            return 3;
        else if (p.x() < 0)
            return 2;
        else
            return 0;
    };

    std::ranges::sort(points, [&ord = std::as_const(ord)](const Point<T>& p0, const Point<T>& p1) {
        auto o0 = ord(p0);
        auto o1 = ord(p1);
        if (o0 != o1)
            return o0 < o1;
        else if (o0 == 1)
            return p0.x() > p1.x();
        else
            return p0.x() < p1.x();
    });
}
