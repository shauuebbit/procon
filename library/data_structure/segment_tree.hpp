#pragma once

#include <functional>
#include <vector>

template <class M, class F = std::function<M(M, M)>>
class SegmentTree {
   private:
    std::vector<M> data;
    F op;
    M e;
    size_t sz;

   public:
    SegmentTree(size_t sz, const F& op, const M& e) : data(sz << 1, e), op(op), e(e), sz(sz) {}

    SegmentTree(const std::vector<M>& v, const F& op, const M& e) : data(v.size() << 1, e), op(op), e(e), sz(v.size()) {
        for (size_t i = 0; i < sz; i++) {
            data[i + sz] = v[i];
        }

        if (sz > 0) {
            for (size_t i = sz - 1; i > 0; i--) {
                data[i] = op(data[i << 1], data[(i << 1) | 1]);
            }
        }
    }

    bool set(size_t index, const M& x) {
        if (index >= sz) return false;
        index += sz;
        data[index] = x;

        while (index >>= 1) {
            data[index] = op(data[index << 1], data[(index << 1) | 1]);
        }

        return true;
    }

    M get(size_t index) { return fold(index, index + 1); }

    M fold(size_t left, size_t right) {
        if (right > sz) right = sz;
        M l = e, r = e;

        for (left += sz, right += sz; left < right; left >>= 1, right >>= 1) {
            if (left & 1) l = op(l, data[left++]);
            if (right & 1) r = op(data[--right], r);
        }

        return op(l, r);
    }

    M fold() { return fold(0, sz); }
};
