#pragma once

#include "math/modint.hpp"

template <long long mod>
class BinomialCoefficients {
    using mint = ModInt<mod>;

    int max;
    mint *factorial;
    mint *factorial_inverse;
    mint *inverse;

   public:
   mint get(int n, int k) {
        if (n < 0 || k < 0 || k > n)
            return 0;
        else
            return factorial[n] * (factorial_inverse[k] * factorial_inverse[n - k]);
    }

    BinomialCoefficients(int max) : max(max) {
        factorial = new mint[max + 1];
        factorial_inverse = new mint[max + 1];
        inverse = new mint[max + 1];

        factorial[0] = factorial[1] = 1;
        factorial_inverse[0] = factorial_inverse[1] = 1;
        inverse[1] = 1;

        for (int k = 2; k <= max; k++) {
            factorial[k] = factorial[k - 1] * k;
            inverse[k] = mint(mod) - inverse[mod % k] * (mod / k);
            factorial_inverse[k] = factorial_inverse[k - 1] * inverse[k];
        }
    }

    ~BinomialCoefficients() {
        delete[] factorial;
        delete[] factorial_inverse;
        delete[] inverse;
    }
};
