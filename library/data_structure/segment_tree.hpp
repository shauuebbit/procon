#pragma once

#include <functional>
#include <vector>

template <class M, class F = std::function<M(M, M)>>
class SegmentTree {
   private:
    std::vector<M> data;
    F op;
    M e;
    int sz;

   public:
    SegmentTree(int sz, const F& op, const M& e) : op(op), e(e), sz(sz), data(sz << 1, e) {}

    SegmentTree(const std::vector<M>& v, const F& op, const M& e) : op(op), e(e), sz(v.size()), data(v.size() << 1, e) {
        for (int i = 0; i < sz; i++) {
            data[i + sz] = v[i];
        }

        for (int i = (int)sz - 1; i > 0; i--) {
            data[i] = op(data[i << 1], data[(i << 1) | 1]);
        }
    }

    bool update(int index, const M& x) {
        if (index < 0 || index >= sz) return false;
        index += sz;
        data[index] = x;

        while (index >>= 1) {
            data[index] = op(data[index << 1], data[(index << 1) | 1]);
        }

        return true;
    }

    M fold(int left, int right) {
        if (left < 0) left = 0;
        if (right > sz) right = sz;
        M l = e, r = e;

        for (left += sz, right += sz; left < right; left >>= 1, right >>= 1) {
            if (left & 1) l = op(l, data[left++]);
            if (right & 1) r = op(data[--right], r);
        }

        return op(l, r);
    }
};
