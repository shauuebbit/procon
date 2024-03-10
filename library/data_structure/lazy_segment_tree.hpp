#pragma once

#include <functional>
#include <vector>

template <class M, class E, class F = std::function<M(M, M)>, class A = std::function<M(M, E)>, class G = std::function<E(E, E)>>
class LazySegmentTree {
   private:
    F op;
    A act;
    G cp;
    M e;
    E id;
    size_t sz;
    mutable std::vector<M> data;
    mutable std::vector<E> lazy;

    void propagate(size_t index) const {
        if (lazy[index] == id) return;
        lazy[index << 1] = cp(lazy[index << 1], lazy[index]);
        lazy[(index << 1) | 1] = cp(lazy[(index << 1) | 1], lazy[index]);
        data[index] = act(data[index], lazy[index]);
        lazy[index] = id;
    }

    void propagate_topdown(size_t index) const {
        size_t h = 0;
        for (size_t i = 1; i < index; i <<= 1) ++h;
        for (size_t i = h; i; --i) propagate(index >> i);
    }

    void recalc(size_t index) const {
        while (index >>= 1) data[index] = op(act(data[index << 1], lazy[index << 1]), act(data[(index << 1) | 1], lazy[(index << 1) | 1]));
    }

   public:
    constexpr LazySegmentTree(size_t sz, const F& op, const A& act, const G& cp, const M& e, const E& id) : op(op), act(act), cp(cp), e(e), id(id), sz(sz), data(sz << 1, e), lazy(sz << 1, id) {}

    constexpr LazySegmentTree(const std::vector<M>& v, const F& op, const A& act, const G& cp, const M& e, const E& id) : op(op), act(act), cp(cp), e(e), id(id), sz(v.size()), data(v.size() << 1, e), lazy(v.size() << 1, id) {
        for (size_t i = 0; i < sz; i++) {
            data[i + sz] = v[i];
        }

        for (size_t i = (int)sz - 1; i > 0; i--) {
            data[i] = op(data[i << 1], data[(i << 1) | 1]);
        }
    }

    constexpr bool set(size_t index, const M& x) {
        if (index >= sz) return false;

        index += sz;

        propagate_topdown(index);

        data[index] = x;
        lazy[index] = id;

        recalc(index);

        return true;
    }

    constexpr void update(const E& g) { update(0, sz, g); }

    constexpr void update(size_t left, size_t right, const E& g) {
        if (left > sz) left = sz;
        if (right > sz) right = sz;
        if (left >= right) return;

        left += sz;
        right += sz;

        propagate_topdown(left);
        propagate_topdown(right - 1);

        for (size_t l = left, r = right; l < r; l >>= 1, r >>= 1) {
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

    constexpr M get(size_t index) const { return fold(index, index + 1); }

    constexpr M fold(size_t left, size_t right) const {
        if (left > sz) left = sz;
        if (right > sz) right = sz;
        if (left >= right) return e;

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

    constexpr M fold() const { return fold(0, sz); }
};
