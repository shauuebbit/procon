#pragma once

#include <cassert>
#include <unordered_map>

template <typename T>
class Trie {
   private:
    struct Node {
        T value;
        std::unordered_map<T, Node*> nexts;

        Node(T value) : value(value) {}
    };

    Node* root;

    void clear(Node** node) {
        for (auto [c, next] : (*node)->nexts) {
            clear(&next);
        }

        (*node)->nexts.clear();

        delete *node;
        *node = nullptr;
    }

   public:
    Trie() { root = new Node(0); }

    ~Trie() { clear(); }

    void clear() {
        clear(&root);
        assert(!root);
    }

    template <typename R>
    requires std::ranges::range<R> && std::convertible_to<std::ranges::range_value_t<R>, T>
    void add(const R& s) {
        Node* node = root;

        for (const T& c : s) {
            if (!node->nexts.contains(c)) {
                node->nexts[c] = new Node(c);
            }
            node = node->nexts[c];
        }
    }

    template <typename R>
    requires std::ranges::range<R> && std::convertible_to<std::ranges::range_value_t<R>, T>
    bool contains(const R& s) const {
        Node* node = root;

        for (const T& c : s) {
            if (!node->nexts.contains(c)) {
                return false;
            }
            node = node->nexts[c];
        }

        return true;
    }
};
