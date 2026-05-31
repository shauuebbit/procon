#pragma once

template <typename T, typename U>
T div_floor(T x, U y) {
    if (y < 0) {
        x = -x;
        y = -y;
    }

    return (x >= 0 ? x / y : -((-x + y - 1) / y));
}

template <typename T, typename U>
T div_ceil(T x, U y) { return -div_floor(-x, y); }
