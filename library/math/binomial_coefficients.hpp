#pragma once

template <typename T = long long, typename U = int>
class BinomialCoefficients {
    int max;
    U mod;
    T *factorial;
    T *factorial_inverse;
    T *inverse;

   public:
    T get(int n, int k) {
        if (n < 0 || k < 0 || k > n)
            return 0;
        else
            return factorial[n] * (factorial_inverse[k] * factorial_inverse[n - k] % mod) % mod;
    }

    BinomialCoefficients(int max, U mod) : max(max), mod(mod) {
        factorial = new T[max + 1];
        factorial_inverse = new T[max + 1];
        inverse = new T[max + 1];

        factorial[0] = factorial[1] = 1;
        factorial_inverse[0] = factorial_inverse[1] = 1;
        inverse[1] = 1;

        for (int k = 2; k <= max; k++) {
            factorial[k] = factorial[k - 1] * k % mod;
            inverse[k] = mod - inverse[mod % k] * (mod / k) % mod;
            factorial_inverse[k] = factorial_inverse[k - 1] * inverse[k] % mod;
        }
    }

    ~BinomialCoefficients() {
        delete[] factorial;
        delete[] factorial_inverse;
        delete[] inverse;
    }
};
