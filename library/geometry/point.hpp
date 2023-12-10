#pragma once

template <typename T>
struct Point {
    T x;
    T y;

    Point(const Point<T>& p) : x(p.x), y(p.y) {}
    Point(T x, T y) : x(x), y(y) {}
    Point() : x(0), y(0) {}

    constexpr Point<T>& operator=(const Point<T>& p) & {
        x = p.x;
        y = p.y;
        return *this;
    }

    constexpr Point<T>& operator+=(const Point<T>& p) {
        x += p.x;
        y += p.y;
        return *this;
    }

    constexpr Point<T>& operator-=(const Point<T>& p) {
        x -= p.x;
        y -= p.y;
        return *this;
    }
};

template <typename T>
Point<T> operator+(const Point<T>& p1, const Point<T>& p2) { return Point<T>(p1) += p2; }

template <typename T>
Point<T> operator-(const Point<T>& p1, const Point<T>& p2) { return Point<T>(p1) -= p2; }

// lexicographical order
template <typename T>
bool operator<(const Point<T>& p1, const Point<T>& p2) { return (p1.x < p2.x) || ((p1.x == p2.x) && (p1.y < p2.y)); }

// lexicographical order
template <typename T>
bool operator>(const Point<T>& p1, const Point<T>& p2) { return (p1.x > p2.x) || ((p1.x == p2.x) && (p1.y > p2.y)); }

template <typename T>
bool operator==(const Point<T>& p1, const Point<T>& p2) { return !(p1 < p2) && !(p1 > p2); }

template <typename T>
T cross(const Point<T>& p1, const Point<T>& p2) { return p1.x * p2.y - p2.x * p1.y; }
