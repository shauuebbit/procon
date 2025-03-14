#pragma once

#include <vector>

// Generate std::vector<T>
// len \in [min_len, max_len], val \in [min_val, max_val]
template <typename T>
class VecGenerator {
   private:
    size_t min_size;
    size_t max_size;
    T min_val;
    T max_val;

    struct Iterator;

    struct Sentinel {
       private:
        friend Iterator;

        size_t unreachable_len;

       public:
        Sentinel(size_t unreachable_len) : unreachable_len(unreachable_len) {}
    };

    struct Iterator {
        friend Sentinel;
       private:
        T min_val;
        T max_val;
        std::vector<T> vals;

        void next() {
            if (min_val != max_val) {
                for (size_t i = vals.size(); i-- > 0;) {
                    if (vals[i] < max_val) {
                        vals[i] += 1;
                        return;
                    } else {
                        vals[i] = min_val;
                    }
                }
            }

            vals.push_back(min_val);
        }

       public:
        constexpr explicit Iterator(size_t init_len, const T& min_val, const T& max_val) : min_val(min_val), max_val(max_val), vals(init_len, min_val) {}

        constexpr const std::vector<T>& operator*() const noexcept { return this->vals; }

        constexpr Iterator& operator++() {
            this->next();
            return *this;
        }

        friend constexpr bool operator==(const Iterator& iterator, const Sentinel& sentinel) {
            return iterator.vals.size() == sentinel.unreachable_len;
        }
        friend constexpr bool operator==(const Sentinel& sentinel, const Iterator& iterator) {
            return iterator == sentinel;
        }
    };

   public:
    VecGenerator(size_t min_size, size_t max_size, const T& min_val, const T& max_val) : min_size(min_size), max_size(max_size), min_val(min_val), max_val(max_val) {}

    constexpr auto begin() const { return Iterator(min_size, min_val, max_val); }
    constexpr auto end() const { return Sentinel(max_size + 1); }
};
