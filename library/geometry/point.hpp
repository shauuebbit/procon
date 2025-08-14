#pragma once

template <typename T>
struct Point {
   private:
    T x_;
    T y_;

   public:
    constexpr Point(const Point<T>& p) : x_(p.x()), y_(p.y()) {}
    constexpr Point(T x, T y) : x_(x), y_(y) {}
    constexpr Point() : x_(0), y_(0) {}

    constexpr T x() const { return x_; }
    constexpr T y() const { return y_; }

    constexpr Point<T>& operator=(const Point<T>& p) & {
        x_ = p.x();
        y_ = p.y();
        return *this;
    }

    constexpr Point<T>& operator+=(const Point<T>& p) {
        x_ += p.x();
        y_ += p.y();
        return *this;
    }

    constexpr Point<T>& operator-=(const Point<T>& p) {
        x_ -= p.x();
        y_ -= p.y();
        return *this;
    }
};

template <typename T>
constexpr Point<T> operator+(const Point<T>& p1, const Point<T>& p2) { return Point<T>(p1) += p2; }

template <typename T>
constexpr Point<T> operator-(const Point<T>& p1, const Point<T>& p2) { return Point<T>(p1) -= p2; }

// lexicographical order
template <typename T>
constexpr bool operator<(const Point<T>& p1, const Point<T>& p2) { return (p1.x() < p2.x()) || ((p1.x() == p2.x()) && (p1.y() < p2.y())); }

// lexicographical order
template <typename T>
constexpr bool operator>(const Point<T>& p1, const Point<T>& p2) { return (p1.x() > p2.x()) || ((p1.x() == p2.x()) && (p1.y() > p2.y())); }

template <typename T>
constexpr bool operator==(const Point<T>& p1, const Point<T>& p2) { return !(p1 < p2) && !(p1 > p2); }

template <typename T>
constexpr T cross(const Point<T>& p1, const Point<T>& p2) { return p1.x() * p2.y() - p2.x() * p1.y(); }
