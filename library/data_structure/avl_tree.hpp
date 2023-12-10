#pragma once

#include <cstddef>

template <typename K>
class AVLTree {
   private:
    struct Node {
        K key;
        int height;
        size_t sub_size;
        Node* parent;
        Node* left_child;
        Node* right_child;

        Node(K key) : key(key), height(0), sub_size(1), parent(nullptr), left_child(nullptr), right_child(nullptr) {}
    };

    Node* base;

    size_t sz;

    Node* create_node(K key, Node* parent) {
        Node* ret = new Node(key);
        ret->parent = parent;
        ret->left_child = base;
        ret->right_child = base;
        return ret;
    }

    inline int get_height(Node* v) const { return (v->left_child->height < v->right_child->height ? v->right_child->height : v->left_child->height) + 1; }
    inline int bias(Node* v) const { return v->left_child->height - v->right_child->height; }

    void revise_node(Node* v) {
        v->height = get_height(v);
        v->sub_size = v->left_child->sub_size + v->right_child->sub_size + 1;
    }

    Node* min_node(Node* v) const {
        while (v->left_child != base) v = v->left_child;
        return v;
    }

    Node* max_node(Node* v) const {
        while (v->right_child != base) v = v->right_child;
        return v;
    }

    Node* find_node_by_key(K key) const {
        Node* current = base->right_child;
        for (; current != base; current = (key < current->key ? current->left_child : current->right_child))
            if (key == current->key) return current;
        return base;
    }

    Node* find_kth_node(size_t k) const {
        if (k >= sz) return base;

        Node* current = base->right_child;
        while (current != base) {
            if (current->left_child->sub_size == k)
                return current;
            else if (current->left_child->sub_size > k)
                current = current->left_child;
            else {
                k -= current->left_child->sub_size + 1;
                current = current->right_child;
            }
        }

        return base;
    }

    Node* rotate_left(Node* v) {
        Node* right = v->right_child;

        v->right_child = right->left_child;
        right->left_child->parent = v;
        (v->parent->right_child == v ? v->parent->right_child : v->parent->left_child) = right;
        right->parent = v->parent;
        right->left_child = v;
        v->parent = right;

        revise_node(v);
        revise_node(right);
        return right;
    }

    Node* rotate_right(Node* v) {
        Node* left = v->left_child;

        v->left_child = left->right_child;
        left->right_child->parent = v;
        (v->parent->right_child == v ? v->parent->right_child : v->parent->left_child) = left;
        left->parent = v->parent;
        left->right_child = v;
        v->parent = left;

        revise_node(v);
        revise_node(left);
        return left;
    }

    void balance(Node* v) {
        while (v != base) {
            if (bias(v) == 2) {
                if (bias(v->left_child) == -1) rotate_left(v->left_child);
                v = rotate_right(v);
            } else if (bias(v) == -2) {
                if (bias(v->right_child) == 1) rotate_right(v->right_child);
                v = rotate_left(v);
            } else
                revise_node(v);

            v = v->parent;
        }
    }

   public:
    AVLTree() : sz(0) {
        base = new Node(0);
        base->height = -1;
        base->sub_size = 0;
        base->parent = base;
        base->left_child = base;
        base->right_child = base;
    }

    bool insert(K key) {
        Node *current = base->right_child, *parent = base;

        for (; current != base; parent = current, current = (key < current->key ? current->left_child : current->right_child))
            if (key == current->key) return false;

        if (size() && key < parent->key)
            parent->left_child = create_node(key, parent);
        else
            parent->right_child = create_node(key, parent);

        balance(parent);
        ++sz;
        return true;
    }

    bool erase(K key) {
        Node* current = base->right_child;

        for (; current != base; current = (key < current->key ? current->left_child : current->right_child)) {
            if (key == current->key) {
                Node* changed_node = nullptr;
                if (current->right_child == base) {
                    (current->parent->right_child == current ? current->parent->right_child : current->parent->left_child) = current->left_child;
                    current->left_child->parent = current->parent;
                    changed_node = current->parent;
                    delete current;
                } else {
                    Node* right_min = min_node(current->right_child);
                    current->key = right_min->key;
                    (right_min->parent == current ? current->right_child : right_min->parent->left_child) = right_min->right_child;
                    right_min->right_child->parent = right_min->parent;
                    changed_node = right_min->parent;
                    delete right_min;
                }

                balance(changed_node);
                --sz;
                return true;
            }
        }
        return false;
    }

    inline bool empty() const { return base->right_child == base; }
    inline size_t size() const { return sz; }

    inline K get_min() const { return min_node(base->right_child)->value; }
    inline K get_max() const { return max_node(base->right_child)->value; }
    inline bool contains(K key) const { return find_node_by_key(key) != base; }

    inline K get_kth_element(size_t k) const { return find_kth_node(k)->key; }

    void clear() {
        Node* current = base->right_child;
        while (current != base) {
            if (current->left_child != base)
                current = current->left_child;
            else if (current->right_child != base)
                current = current->right_child;
            else {
                current = current->parent;
                if (current->left_child != base) {
                    delete current->left_child;
                    current->left_child = base;
                } else {
                    delete current->right_child;
                    current->right_child = base;
                }
            }
        }

        sz = 0;
    }

    ~AVLTree() {
        clear();
        delete base;
    }
};
