#pragma once

#include <functional>
#include <vector>

template <class M, class E, class F = std::function<M(M, M)>, class A = std::function<M(M, E)>, class G = std::function<E(E, E)>>
class LazySegmentTree {
   private:
    std::vector<M> data;
    std::vector<E> lazy;
    F op;
    G cp;
    A act;
    M e;
    E id;
    int sz;

    void propagate(int index) {
        if (lazy[index] == id) return;
        lazy[index << 1] = cp(lazy[index << 1], lazy[index]);
        lazy[(index << 1) | 1] = cp(lazy[(index << 1) | 1], lazy[index]);
        data[index] = act(data[index], lazy[index]);
        lazy[index] = id;
    }

    void propagate_topdown(int index) {
        int h = 0;
        for (int i = 1; i < index; i <<= 1) ++h;
        for (int i = h; i; i--) propagate(index >> i);
    }

    void recalc(int index) {
        while (index >>= 1) data[index] = op(act(data[index << 1], lazy[index << 1]), act(data[(index << 1) | 1], lazy[(index << 1) | 1]));
    }

   public:
    LazySegmentTree(int sz, const F& op, const A& act, const G& cp, const M& e, const E& id) : op(op), act(act), cp(cp), e(e), id(id), sz(sz), data(sz << 1, e), lazy(sz << 1, id) {}

    LazySegmentTree(const std::vector<M>& v, const F& op, const A& act, const G& cp, const M& e, const E& id) : op(op), act(act), cp(cp), e(e), id(id), sz(v.size()), data(v.size() << 1, e), lazy(v.size() << 1, id) {
        for (int i = 0; i < sz; i++) {
            data[i + sz] = v[i];
        }

        for (int i = (int)sz - 1; i > 0; i--) {
            data[i] = op(data[i << 1], data[(i << 1) | 1]);
        }
    }

    void update(int left, int right, const E& g) {
        if (left < 0) left = 0;
        if (right > sz) right = sz;
        left += sz;
        right += sz;

        propagate_topdown(left);
        propagate_topdown(right - 1);

        for (int l = left, r = right; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                lazy[l] = cp(lazy[l], g);
                ++l;
            }
            if (r & 1) {
                --r;
                lazy[r] = cp(lazy[r], g);
            }
        }

        recalc(left);
        recalc(right - 1);
    }

    M fold(int left, int right) {
        if (left < 0) left = 0;
        if (right > sz) right = sz;
        left += sz;
        right += sz;

        propagate_topdown(left);
        propagate_topdown(right - 1);

        M l = e, r = e;

        for (; left < right; left >>= 1, right >>= 1) {
            if (left & 1) {
                l = op(l, act(data[left], lazy[left]));
                ++left;
            }
            if (right & 1) {
                --right;
                r = op(act(data[right], lazy[right]), r);
            }
        }

        return op(l, r);
    }

    M fold() { return fold(0, sz); }
};
