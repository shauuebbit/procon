#include "util/timer.hpp"

#include <gtest/gtest.h>

TEST(TimerTest, Construct) {
    Timer timer;

    int sum = 0;

    timer.start();
    for (int i = 0; i < 2; i++) {
        timer.start();
        for (int j = 0; j < 3; j++) {
            timer.start();
            for (int k = 0; k < 4; k++) {
                timer.start();
                for (int l = 0; l < 2; l++) {
                    sum += (i + 1) * (j + 1) + k * l;
                }
                auto elapsed = timer.elapse_as_nanoseconds();
                ASSERT_GE(elapsed, 0);
                auto stopped = timer.stop_as_nanoseconds();
                ASSERT_GE(stopped, elapsed);
            }
            auto elapsed = timer.elapse_as_microseconds();
            ASSERT_GE(elapsed, 0);
            auto stopped = timer.stop_as_microseconds();
            ASSERT_GE(stopped, elapsed);
        }
        auto elapsed = timer.elapse_as_milliseconds();
        ASSERT_GE(elapsed, 0);
        auto stopped = timer.stop_as_milliseconds();
        ASSERT_GE(stopped, elapsed);
    }
    auto elapsed = timer.elapse_as_seconds();
    ASSERT_GE(elapsed, 0);
    auto stopped = timer.stop_as_seconds();
    ASSERT_GE(stopped, elapsed);
}
