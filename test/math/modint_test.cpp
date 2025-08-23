#include "math/modint.hpp"

#include <gtest/gtest.h>

using namespace std;

#define CONST_INT_MOD
constexpr int MOD = 998244353;
using mint = ModInt<MOD>;

TEST(ModIntTest, Init) {
    mint a;

    ASSERT_EQ(a.get(), 0);

    a = mint(MOD - 1);
    ASSERT_EQ(a.get(), MOD - 1);

    a = mint(MOD);
    ASSERT_EQ(a.get(), 0);

    a = mint(static_cast<long long>(MOD) * 3);
    ASSERT_EQ(a.get(), 0);

    a = mint(static_cast<long long>(MOD) * 3 + 1);
    ASSERT_EQ(a.get(), 1);

    a = mint(-1);

    ASSERT_EQ(a.get(), MOD - 1);

    a = mint(-MOD * 2 - 1);

    ASSERT_EQ(a.get(), MOD - 1);
}

TEST(ModIntTest, Add) {
    mint a(6);
    mint b(5);
    ASSERT_EQ((a + b).get(), 11);
    ASSERT_EQ((a + 10).get(), 16);

    a += b;
    ASSERT_EQ(a.get(), 11);
    ASSERT_EQ(b.get(), 5);
    a += 2;
    ASSERT_EQ(a.get(), 13);

    ASSERT_EQ((mint(MOD - 1) + mint(MOD - 1)).get(), MOD - 2);
}

TEST(ModIntTest, Sub) {
    mint a(6);
    mint b(5);
    ASSERT_EQ((a - b).get(), 1);
    ASSERT_EQ((-b + a).get(), 1);
    ASSERT_EQ((a - 10).get(), MOD - 4);

    b -= 3;
    ASSERT_EQ(b.get(), 2);
    a -= b;
    ASSERT_EQ(a.get(), 4);
    ASSERT_EQ(b.get(), 2);
}

TEST(ModIntTest, Mul) {
    mint a(6);
    mint b(5);
    ASSERT_EQ((a * b).get(), 30);
    ASSERT_EQ((a * 2).get(), 12);

    ASSERT_EQ((mint(100000) * mint(100000)).get(), 10000000000ll % MOD);

    a *= 4;
    ASSERT_EQ(a.get(), 24);

    a *= b;
    ASSERT_EQ(a.get(), 120);
    ASSERT_EQ(b.get(), 5);
}

#include "math/inverse.hpp"

TEST(ModIntTest, Div) {
    ASSERT_EQ((mint(6) / 3).get(), 2);

    ASSERT_EQ((mint(5) / mint(120)).get(), 5ll * inverse(120ll) % MOD);

    mint a(6);

    a /= 3;

    ASSERT_EQ(a.get(), 2);

    mint b(12);

    b /= a;

    ASSERT_EQ(a.get(), 2);
    ASSERT_EQ(b.get(), 6);
}

TEST(ModIntTest, Inc) {
    mint a(6);

    ASSERT_EQ((a++).get(), 6);
    ASSERT_EQ(a.get(), 7);

    ASSERT_EQ((++a).get(), 8);
    ASSERT_EQ(a.get(), 8);

    mint b(MOD - 1);

    ++b;
    ASSERT_EQ(b.get(), 0);

    ++b;
    ASSERT_EQ(b.get(), 1);
}

TEST(ModIntTest, Dec) {
    mint a(6);

    ASSERT_EQ((a--).get(), 6);
    ASSERT_EQ(a.get(), 5);

    ASSERT_EQ((--a).get(), 4);
    ASSERT_EQ(a.get(), 4);

    mint b(1);

    --b;
    ASSERT_EQ(b.get(), 0);

    --b;
    ASSERT_EQ(b.get(), MOD - 1);

    --b;
    ASSERT_EQ(b.get(), MOD - 2);
}

TEST(ModIntTest, Pow) {
    mint a(2);

    ASSERT_EQ((a ^ 10).get(), 1024);

    mint b(15);

    long long z = 1;

    for (int i = 0; i < 100; i++) {
        ASSERT_EQ((b ^ i).get(), z);
        z *= 15;
        z %= MOD;
    }
}

TEST(ModIntTest, Equal) {
    mint a(10);
    mint b(10);
    mint c(1000);

    ASSERT_EQ(a, b);
    ASSERT_EQ(a, 10);
    ASSERT_NE(b, c);
    ASSERT_NE(c, a);
}

TEST(ModIntTest, Assign) {
    mint a(10);
    mint b(1000);

    a = b;
    ASSERT_EQ(a.get(), 1000);
    ASSERT_EQ(b.get(), 1000);

    a = 876567;
    ASSERT_EQ(a.get(), 876567);

    b = 10000000000ll;
    ASSERT_EQ(b.get(), 10000000000ll % MOD);
}

#include <sstream>

TEST(ModIntTest, Stream) {
    int x = 987;

    mint a;

    istringstream sin(to_string(x));

    sin >> a;

    ASSERT_EQ(a.get(), x);

    ++a;

    ostringstream sout;

    sout << a;

    ASSERT_EQ(stoll(sout.str()), x + 1);
}
