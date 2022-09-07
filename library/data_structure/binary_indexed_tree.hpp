#pragma once

template <typename T>
class BinaryIndexedTree {
   private:
    int sz;
    T *data;

   public:
    BinaryIndexedTree(int sz = 0) : sz(sz) {
        data = new T[sz + 1];
        for (int i = 0; i <= sz; i++) data[i] = 0;
    }

    bool add(int index, T x = 1) {
        if (index < 0 || sz <= index) return false;
        for (++index; index <= sz; index += index & -index) {
            data[index] += x;
        }
        return true;
    }

    T sum(int index) const {
        // [0..index]
        if (index < 0)
            index = 0;
        else if (index >= sz)
            index = sz - 1;

        T x = 0;
        for (++index; index; index -= index & -index) {
            x += data[index];
        }
        return x;
    }

    int lower_bound(T x) const {
        if (x <= 0) return 0;

        int index = 0, b = 1;
        while ((b << 1) <= sz) b <<= 1;

        while (b) {
            if (index + b <= sz && data[index + b] < x) {
                x -= data[index + b];
                index += b;
            }
            b >>= 1;
        }
        return index;
    }

    ~BinaryIndexedTree() {
        delete[] data;
    }
};
