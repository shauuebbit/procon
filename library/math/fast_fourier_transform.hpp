#pragma once

#include <complex>
#include <vector>

template <typename T = double>
void fast_fourier_transform(std::vector<std::complex<T>>& signal) {
    size_t length = signal.size();

    for (size_t i = 0, j = 0; i < (length >> 1); i += 2) {
        if (i < j) {
            std::swap(signal[i], signal[j]);
            std::swap(signal[i + (length >> 1) + 1], signal[j + (length >> 1) + 1]);
        }
        std::swap(signal[i + (length >> 1)], signal[j + 1]);

        for (size_t k = length >> 2; k > (j ^= k); k >>= 1)
            ;
    }

    for (size_t k = 1; k < length; k <<= 1) {
        std::complex<T> rot = std::polar((T)1.0, -(T)M_PI / (T)k);
        std::complex<T> w = 1.0;
        for (size_t i = 0; i < k; i++) {
            for (size_t j = 0; j < length; j += k << 1) {
                std::complex<T> z = signal[i + j + k] * w;
                signal[i + j + k] = signal[i + j] - z;
                signal[i + j] += z;
            }
            w *= rot;
        }
    }
}

template <typename T = double>
void inverse_fast_fourier_transform(std::vector<std::complex<T>>& signal) {
    size_t length = signal.size();
    T length_inv = 1.0 / (T)length;
    for (size_t k = 0; k < length; k++) {
        signal[k] = std::conj(signal[k]) * length_inv;
    }

    fast_fourier_transform(signal);

    for (size_t n = 0; n < length; n++) {
        signal[n] = std::conj(signal[n]);
    }
}

template <typename T = double>
std::vector<std::complex<T>> convolute(std::vector<std::complex<T>> signal1, std::vector<std::complex<T>> signal2) {
    size_t length = signal1.size() + signal2.size() + 1;
    size_t l = 1;
    for (; l < length; l <<= 1)
        ;

    signal1.resize(l);
    signal2.resize(l);

    fast_fourier_transform(signal1);
    fast_fourier_transform(signal2);

    for (size_t i = 0; i < l; i++) {
        signal1[i] *= signal2[i];
    }

    inverse_fast_fourier_transform(signal1);
    signal1.resize(length);

    return signal1;
}
