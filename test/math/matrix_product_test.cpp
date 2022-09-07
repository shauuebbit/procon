#include "math/matrix_product.hpp"

#include <gtest/gtest.h>

#include <vector>

using namespace std;

TEST(MatrixProductTest, Small) {
    vector a(4, vector<int>(2, 0));
    vector b(2, vector<int>(3, 0));

    a = {{1, -2,}, {-3, 4,}, {5, 6,}, {-7, 8,},};
    b = {{1, -2, 3,}, {4, 5, -6,},};

    auto c = matrix_product(a, b);

    ASSERT_EQ(c.size(), 4);
    ASSERT_EQ(c[0].size(), 3);

    vector d = vector<vector<int>>(4, vector<int>(3));
    
    d = {{-7, -12, 15,}, {13, 26, -33,}, {29, 20, -21,}, {25, 54, -69},};

    ASSERT_EQ(c, d);
}
