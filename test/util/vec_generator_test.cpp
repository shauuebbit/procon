#include "util/vec_generator.hpp"

#include <gtest/gtest.h>

#include "math/power.hpp"

struct IntValTestParam {
   private:
    using T = int;

    std::string test_name;
    size_t min_size;
    size_t max_size;
    T min_val;
    T max_val;

   public:
    constexpr IntValTestParam(const std::string& test_name, size_t min_size, size_t max_size, T min_val, T max_val) : test_name(test_name), min_size(min_size), max_size(max_size), min_val(min_val), max_val(max_val) {}

    auto get_test_name() const noexcept { return test_name; }
    auto get_min_size() const noexcept { return min_size; }
    auto get_max_size() const noexcept { return max_size; }
    auto get_min_val() const noexcept { return min_val; }
    auto get_max_val() const noexcept { return max_val; }
};

constexpr std::ostream& operator<<(std::ostream& os, const IntValTestParam& param) {
    return os << param.get_test_name();
}

class IntValTest : public ::testing::TestWithParam<IntValTestParam> {};

TEST_P(IntValTest, test) {
    using T = int;

    const auto param = GetParam();
    const size_t MIN_LEN = param.get_min_size();
    const size_t MAX_LEN = param.get_max_size();
    const T MIN_VAL = param.get_min_val();
    const T MAX_VAL = param.get_max_val();

    std::set<std::vector<T>> s;

    for (auto v : VecGenerator(MIN_LEN, MAX_LEN, MIN_VAL, MAX_VAL)) {
        // len range check
        EXPECT_GE(v.size(), MIN_LEN);
        EXPECT_LE(v.size(), MAX_LEN);

        // value range check
        for (auto x : v) {
            EXPECT_GE(x, MIN_VAL);
            EXPECT_LE(x, MAX_VAL);
        }

        s.insert(v);
    }

    // completeness check
    // the number of generated vectors must be (val_range)^MIN_LEN + ... + (val_range)^MAX_LEN
    // where val_range := MAX_VAL - MIN_VAL + 1
    size_t num = MIN_VAL == MAX_VAL ? (MAX_LEN - MIN_LEN + 1) : (power(MAX_VAL - MIN_VAL + 1, MAX_LEN + 1) - power(MAX_VAL - MIN_VAL + 1, MIN_LEN)) / (MAX_VAL - MIN_VAL);
    EXPECT_EQ(s.size(), num);
}

INSTANTIATE_TEST_SUITE_P(VecGeneratorTest, IntValTest,
                         testing::Values(
                             IntValTestParam("OneLenOneValue", 2, 2, 3, 3),
                             IntValTestParam("OneLenMultipleValue", 2, 2, 1, 5),
                             IntValTestParam("MultipleLenOneValue", 2, 4, 3, 3),
                             IntValTestParam("MultipleLenMultipleValue", 2, 4, 1, 5)),
                         ::testing::PrintToStringParamName());
