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
                sum += (i + 1) * (j + 1) + k;
            }
            auto elapsed = timer.stop_as_nanoseconds();
            ASSERT_GE(elapsed, 0);
        }
        auto elapsed = timer.stop_as_microseconds();
        ASSERT_GE(elapsed, 0);
    }
    auto elapsed = timer.stop_as_milliseconds();
    ASSERT_GE(elapsed, 0);
}
