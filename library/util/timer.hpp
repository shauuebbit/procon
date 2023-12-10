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

    long double elapse_in_nanoseconds() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(this->elapse()).count();
    }

    long double elapse_in_microseconds() {
        return std::chrono::duration_cast<std::chrono::microseconds>(this->elapse()).count();
    }

    long double elapse_in_milliseconds() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(this->elapse()).count();
    }

    long double elapse_in_seconds() {
        return std::chrono::duration_cast<std::chrono::seconds>(this->elapse()).count();
    }

    long double stop_in_nanoseconds() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(this->stop()).count();
    }

    long double stop_in_microseconds() {
        return std::chrono::duration_cast<std::chrono::microseconds>(this->stop()).count();
    }

    long double stop_in_milliseconds() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(this->stop()).count();
    }

    long double stop_in_seconds() {
        return std::chrono::duration_cast<std::chrono::seconds>(this->stop()).count();
    }
};
