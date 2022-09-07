#pragma once

#include <cassert>
#include <functional>
#include <stack>
#include <vector>

template <typename T, typename F = std::function<T(T, T)>>
class SlidingWindowAggregation {
   private:
    T prod_right;
    F op;
    T e;
    std::stack<T, std::vector<T>> stack_prod_left;
    std::stack<T, std::vector<T>> stack_prod_right;

   public:
    SlidingWindowAggregation(const F& op, const T& e) : op(op), prod_right(e), e(e) {}

    void push(const T& x) {
        stack_prod_right.push(x);
        prod_right = op(prod_right, x);
    }

    bool pop() {
        if (stack_prod_left.empty()) {
            if (stack_prod_right.empty()) return false;

            prod_right = e;

            while (stack_prod_right.size() > 1) {
                prod_right = op(stack_prod_right.top(), prod_right);
                stack_prod_left.push(prod_right);
                stack_prod_right.pop();
            }

            stack_prod_right.pop();

            prod_right = e;
        } else {
            stack_prod_left.pop();
        }

        return true;
    }

    T fold() {
        if (stack_prod_left.empty())
            return prod_right;
        else
            return op(stack_prod_left.top(), prod_right);
    }

    inline size_t size() { return stack_prod_left.size() + stack_prod_right.size(); }

    inline bool empty() { return size() == 0; }

    void clear() {
        while (!stack_prod_left.empty()) stack_prod_left.pop();
        while (!stack_prod_right.empty()) stack_prod_right.pop();
        prod_right = e;
    }
};

template <typename T, typename F = std::function<T(T, T)>>
class DoubleEndedSlidingWindowAggregation {
   private:
    F op;
    T e;
    std::stack<T, std::vector<T>> stack_left;
    std::stack<T, std::vector<T>> stack_prod_left;
    std::stack<T, std::vector<T>> stack_right;
    std::stack<T, std::vector<T>> stack_prod_right;

    void balance(const std::vector<T>& v) {
        int n = v.size();

        for (int i = (n >> 1) - 1; i >= 0; i--) {
            push_front(v[i]);
        }

        for (int i = n >> 1; i < n; i++) {
            push_back(v[i]);
        }
    }

   public:
    DoubleEndedSlidingWindowAggregation(const F& op, const T& e) : op(op), e(e) {}

    void push_front(const T& x) {
        stack_left.push(x);

        if (stack_prod_left.empty()) {
            stack_prod_left.push(x);
        } else {
            stack_prod_left.push(op(x, stack_prod_left.top()));
        }
    }

    void push_back(const T& x) {
        stack_right.push(x);

        if (stack_prod_right.empty()) {
            stack_prod_right.push(x);
        } else {
            stack_prod_right.push(op(stack_prod_right.top(), x));
        }
    }

    bool pop_front() {
        if (stack_left.empty()) {
            if (stack_right.empty()) return false;

            size_t sz = size();

            std::vector<T> v(sz - 1, e);

            for (size_t i = 0; i + 1 < sz; i++) {
                v[sz - i - 2] = stack_right.top();
                stack_right.pop();
                stack_prod_right.pop();
            }

            stack_right.pop();
            stack_prod_right.pop();

            balance(v);
        } else {
            stack_left.pop();
            stack_prod_left.pop();
        }

        return true;
    }

    bool pop_back() {
        if (stack_right.empty()) {
            if (stack_left.empty()) return false;

            size_t sz = size();

            std::vector<T> v(sz - 1, e);

            for (size_t i = 0; i + 1 < sz; i++) {
                v[i] = stack_left.top();
                stack_left.pop();
                stack_prod_left.pop();
            }

            stack_left.pop();
            stack_prod_left.pop();

            balance(v);
        } else {
            stack_right.pop();
            stack_prod_right.pop();
        }

        return true;
    }

    T fold() {
        if (stack_prod_left.empty() && stack_prod_right.empty())
            return e;
        else if (stack_prod_left.empty())
            return stack_prod_right.top();
        else if (stack_prod_right.empty())
            return stack_prod_left.top();
        else
            return op(stack_prod_left.top(), stack_prod_right.top());
    }

    inline size_t size() { return stack_left.size() + stack_right.size(); }

    inline bool empty() { return size() == 0; }

    void clear() {
        while (!stack_left.empty()) stack_left.pop();
        while (!stack_prod_left.empty()) stack_prod_left.pop();
        while (!stack_right.empty()) stack_right.pop();
        while (!stack_prod_right.empty()) stack_prod_right.pop();
    }
};
