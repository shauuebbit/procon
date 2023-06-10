#pragma once

#include <chrono>
#include <stack>
#include <vector>

class Timer {
   private:
    std::stack<std::chrono::system_clock::time_point, std::vector<std::chrono::system_clock::time_point>> time_stack;

   public:
    Timer() = default;

    void start() {
        auto t = std::chrono::system_clock::now();

        time_stack.push(t);
    }

    std::chrono::system_clock::duration elapse() {
        auto e = std::chrono::system_clock::now() - time_stack.top();
        return e;
    }

    std::chrono::system_clock::duration stop() {
        auto e = this->elapse();
        time_stack.pop();
        return e;
    }

    long double elapse_as_nanoseconds() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(this->elapse()).count();
    }

    long double elapse_as_microseconds() {
        return std::chrono::duration_cast<std::chrono::microseconds>(this->elapse()).count();
    }

    long double elapse_as_milliseconds() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(this->elapse()).count();
    }

    long double elapse_as_seconds() {
        return std::chrono::duration_cast<std::chrono::seconds>(this->elapse()).count();
    }

    long double stop_as_nanoseconds() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(stop()).count();
    }

    long double stop_as_microseconds() {
        return std::chrono::duration_cast<std::chrono::microseconds>(stop()).count();
    }

    long double stop_as_milliseconds() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(stop()).count();
    }

    long double stop_as_seconds() {
        return std::chrono::duration_cast<std::chrono::seconds>(stop()).count();
    }
};
