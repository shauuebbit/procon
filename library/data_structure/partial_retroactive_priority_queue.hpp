#pragma once

#include <algorithm>
#include <cassert>
#include <optional>

template <typename T, typename K>
class PartialRetroactivePriorityQueue {
   private:
    struct Node {
        T time;
        std::optional<K> key;
        int label;
        int prefix_sum_label;

        std::optional<K> max_key_not_contained;
        std::optional<K> min_key_contained;
        int min_prefix_sum_label;
        size_t subtree_size;

        int lazy_prefix_sum_label;

        Node* left_child;
        Node* right_child;
        Node* parent;

        Node(const T& time, const std::optional<K>& key, int label)
            : time(time),
              key(key),
              label(label),
              prefix_sum_label(label),
              max_key_not_contained(std::nullopt),
              min_key_contained(key),
              min_prefix_sum_label(label),
              subtree_size(1),
              lazy_prefix_sum_label(0),
              left_child(nullptr),
              right_child(nullptr),
              parent(nullptr) {}
    };

    Node* root;
    size_t sz;

    bool is_left_child(Node* node) {
        assert(node->parent);
        assert(node->parent->left_child == node || node->parent->right_child == node);
        return node == node->parent->left_child;
    }

    void rotate_left(Node* node) {
        Node* right = node->right_child;
        assert(right);
        node->right_child = right->left_child;
        if (node->right_child) node->right_child->parent = node;
        if (node->parent) {
            (is_left_child(node) ? node->parent->left_child : node->parent->right_child) = right;
        } else {
            assert(node == root);
            root = right;
        }
        right->parent = node->parent;
        right->left_child = node;
        node->parent = right;
    }

    void rotate_right(Node* node) {
        Node* left = node->left_child;
        assert(left);
        node->left_child = left->right_child;
        if (node->left_child) node->left_child->parent = node;
        if (node->parent) {
            (is_left_child(node) ? node->parent->left_child : node->parent->right_child) = left;
        } else {
            assert(node == root);
            root = left;
        }
        left->parent = node->parent;
        left->right_child = node;
        node->parent = left;
    }

    void splay(Node* node) {
        while (node && node->parent) {
            Node* parent = node->parent;

            bool is_left = is_left_child(node);

            if (!parent->parent) {
                is_left ? rotate_right(parent) : rotate_left(parent);
                recalc(parent);
                break;
            }

            Node* grandparent = parent->parent;

            if (is_left_child(parent) == is_left) {
                if (is_left) {
                    rotate_right(grandparent);
                    rotate_right(parent);
                } else {
                    rotate_left(grandparent);
                    rotate_left(parent);
                }
            } else {
                if (is_left) {
                    rotate_right(parent);
                    rotate_left(grandparent);
                } else {
                    rotate_left(parent);
                    rotate_right(grandparent);
                }
            }

            recalc(grandparent);
            recalc(parent);
            recalc(node);
        }

        recalc(node);
    }

    bool chmin_key(std::optional<K>& x, const std::optional<K>& y) {
        if (y) {
            if (!x || x.value() > y.value()) {
                x = y;
                return true;
            }
            return false;
        }
        return false;
    }

    bool chmax_key(std::optional<K>& x, const std::optional<K>& y) {
        if (y) {
            if (!x || x.value() < y.value()) {
                x = y;
                return true;
            }
            return false;
        }
        return false;
    }

    void propagate(Node* node) {
        if (!node || node->lazy_prefix_sum_label == 0) return;
        node->prefix_sum_label += node->lazy_prefix_sum_label;
        node->min_prefix_sum_label += node->lazy_prefix_sum_label;
        if (node->left_child) {
            node->left_child->lazy_prefix_sum_label += node->lazy_prefix_sum_label;
        }
        if (node->right_child) {
            node->right_child->lazy_prefix_sum_label += node->lazy_prefix_sum_label;
        }
        node->lazy_prefix_sum_label = 0;
    }

    void recalc(Node* node) {
        if (!node) return;
        node->min_prefix_sum_label = node->prefix_sum_label;
        node->max_key_not_contained = node->label == 1 ? node->key : std::nullopt;
        node->min_key_contained = node->label == 0 ? node->key : std::nullopt;
        node->subtree_size = 1;
        if (node->left_child) {
            assert(node->left_child->lazy_prefix_sum_label == 0);
            node->min_prefix_sum_label = std::min(node->left_child->min_prefix_sum_label, node->min_prefix_sum_label);
            chmax_key(node->max_key_not_contained, node->left_child->max_key_not_contained);
            chmin_key(node->min_key_contained, node->left_child->min_key_contained);
            node->subtree_size += node->left_child->subtree_size;
        }
        if (node->right_child) {
            assert(node->right_child->lazy_prefix_sum_label == 0);
            node->min_prefix_sum_label = std::min(node->min_prefix_sum_label, node->right_child->min_prefix_sum_label);
            chmax_key(node->max_key_not_contained, node->right_child->max_key_not_contained);
            chmin_key(node->min_key_contained, node->right_child->min_key_contained);
            node->subtree_size += node->right_child->subtree_size;
        }
    }

    Node* get_leftmost_node(Node* node) {
        if (!node) return node;

        propagate(node);

        while (node->left_child) {
            propagate(node->left_child);
            propagate(node->right_child);

            node = node->left_child;
        }

        propagate(node->right_child);

        splay(node);

        return node;
    }

    Node* get_rightmost_node(Node* node) {
        if (!node) return node;

        propagate(node);

        while (node->right_child) {
            propagate(node->left_child);
            propagate(node->right_child);

            node = node->right_child;
        }

        propagate(node->left_child);

        splay(node);

        return node;
    }

    Node* get_kth_node(Node* node, size_t index) {
        propagate(node);

        while (true) {
            propagate(node->left_child);
            propagate(node->right_child);

            if (node->left_child) {
                if (index < node->left_child->subtree_size) {
                    node = node->left_child;
                } else if (index < node->left_child->subtree_size + 1) {
                    break;
                } else {
                    index -= node->left_child->subtree_size + 1;
                    node = node->right_child;
                }
            } else {
                if (index == 0) {
                    break;
                } else {
                    --index;
                    node = node->right_child;
                }
            }
        }

        splay(node);

        return node;
    }

    Node* left_nearest_bridge(const T& time) {
        Node* right = split_right(time);

        Node* bridge = get_rightmost_node(root);

        assert(bridge);

        propagate(bridge);

        while (bridge) {
            propagate(bridge->left_child);
            propagate(bridge->right_child);

            if (bridge->right_child && bridge->right_child->min_prefix_sum_label == 0) {
                bridge = bridge->right_child;
            } else if (bridge->prefix_sum_label == 0) {
                break;
            } else {
                bridge = bridge->left_child;
            }
        }

        splay(bridge);

        merge_right(right);

        if (bridge) {
            bridge = upper_bound(root, bridge->time);
        } else {
            bridge = get_leftmost_node(root);
        }
        assert(bridge);

        splay(bridge);

        return bridge;
    }

    Node* right_nearest_bridge(const T& time) {
        Node* right = split_right(time);

        Node* bridge = get_rightmost_node(root);

        merge_right(right);

        assert(bridge);
        if (bridge->prefix_sum_label > 0) {
            Node* left = split_left(bridge->time);

            propagate(bridge);

            while (bridge) {
                propagate(bridge->left_child);
                propagate(bridge->right_child);

                if (bridge->left_child && bridge->left_child->min_prefix_sum_label == 0) {
                    bridge = bridge->left_child;
                } else if (bridge->prefix_sum_label == 0) {
                    break;
                } else {
                    bridge = bridge->right_child;
                }
            }

            splay(bridge);

            merge_left(left);
        }

        return bridge;
    }

    Node* lower_bound(Node* node, const T& time) {
        Node* ret = nullptr;

        propagate(node);

        while (node) {
            propagate(node->left_child);
            propagate(node->right_child);

            if (time <= node->time) {
                ret = node;
                if (node->left_child)
                    node = node->left_child;
                else
                    break;
            } else if (node->time < time) {
                if (node->right_child)
                    node = node->right_child;
                else
                    break;
            }
        }

        if (ret) {
            splay(ret);
        } else {
            splay(node);
        }

        return ret;
    }

    Node* upper_bound(Node* node, const T& time) {
        Node* ret = nullptr;

        propagate(node);

        while (node) {
            propagate(node->left_child);
            propagate(node->right_child);

            if (time < node->time) {
                ret = node;
                if (node->left_child)
                    node = node->left_child;
                else
                    break;
            } else if (node->time <= time) {
                if (node->right_child)
                    node = node->right_child;
                else
                    break;
            }
        }

        if (ret) {
            splay(ret);
        } else {
            splay(node);
        }

        return ret;
    }

    Node* get_rightmost_node_with_max_key_not_contained(Node* node) {
        propagate(node);

        while (node) {
            propagate(node->left_child);
            propagate(node->right_child);

            if (node->right_child && node->right_child->max_key_not_contained == node->max_key_not_contained) {
                node = node->right_child;
            } else if (node->label == 1 && node->key.value() == node->max_key_not_contained.value()) {
                break;
            } else {
                node = node->left_child;
            }
        }

        splay(node);

        return node;
    }

    Node* get_leftmost_node_with_min_key_contained(Node* node) {
        propagate(node);

        while (node) {
            propagate(node->left_child);
            propagate(node->right_child);

            if (node->left_child && node->left_child->min_key_contained == node->min_key_contained) {
                node = node->left_child;
            } else if (node->label == 0 && node->key.value() == node->min_key_contained.value()) {
                break;
            } else {
                node = node->right_child;
            }
        }

        splay(node);

        return node;
    }

    Node* split_left(const T& time) {
        Node* node = lower_bound(root, time);

        Node* left = nullptr;

        if (node) {
            left = node->left_child;
            node->left_child = nullptr;
            if (left) left->parent = nullptr;
            propagate(node->right_child);
            recalc(node);
        } else {
            left = root;
            root = nullptr;
        }

        return left;
    }

    Node* split_right(const T& time) {
        Node* right = upper_bound(root, time);

        if (right) {
            root = right->left_child;
            right->left_child = nullptr;
            recalc(right);
            if (root) {
                root->parent = nullptr;
                propagate(root->left_child);
                recalc(root);
            }
        }

        return right;
    }

    void merge_left(Node* left) {
        if (root) {
            root = get_leftmost_node(root);

            root->left_child = left;
            if (root->left_child) {
                root->left_child->parent = root;
            }

            propagate(root->left_child);
            propagate(root->right_child);
            recalc(root);
        } else {
            root = left;
        }
    }

    void merge_right(Node* right) {
        if (root) {
            root = get_rightmost_node(root);

            root->right_child = right;
            if (root->right_child) {
                root->right_child->parent = root;
            }

            propagate(root->left_child);
            propagate(root->right_child);
            recalc(root);
        } else {
            root = right;
        }
    }

   public:
    PartialRetroactivePriorityQueue() : root(nullptr), sz(0) {}

    bool insert_push(const T& time, const K& key) {
        if (contains(time)) return false;

        Node* right = split_right(time);
        Node* left = get_rightmost_node(root);

        root = new Node(time, key, 1);
        if (left) {
            propagate(left);
            root->prefix_sum_label += left->prefix_sum_label;
        }
        if (right) ++right->lazy_prefix_sum_label;
        merge_left(left);
        merge_right(right);

        Node* bridge = left_nearest_bridge(time);

        left = split_left(bridge->time);

        root = get_rightmost_node_with_max_key_not_contained(root);

        root->label = 0;
        --(root->prefix_sum_label);
        right = split_right(root->time);
        if (right) --right->lazy_prefix_sum_label;
        merge_left(left);
        merge_right(right);

        ++sz;

        return true;
    }

    bool insert_pop(const T& time) {
        if (contains(time)) return false;

        Node* left = split_left(time);
        merge_left(left);

        if (!left) return false;

        Node* bridge = right_nearest_bridge(time);

        Node* right = split_right(bridge->time);

        if (!root->min_key_contained) {
            merge_right(right);
            return false;
        }

        Node* node = get_leftmost_node_with_min_key_contained(root);

        node->label = 1;
        ++(node->prefix_sum_label);
        merge_right(right);
        right = split_right(node->time);
        if (right) ++right->lazy_prefix_sum_label;
        merge_right(right);

        right = split_right(time);

        left = get_rightmost_node(root);

        root = new Node(time, std::nullopt, -1);
        if (left) {
            propagate(left);
            root->prefix_sum_label += left->prefix_sum_label;
        }
        if (right) --right->lazy_prefix_sum_label;
        merge_left(left);
        merge_right(right);

        --sz;

        return true;
    }

    T push(const K& key) {
        Node* node = get_rightmost_node(root);
        T time = 0;
        if (node) time = node->time + 1;

        insert_push(time, key);

        return time;
    }

    T pop() {
        Node* node = get_rightmost_node(root);
        T time = node->time + 1;

        insert_pop(time);

        return time;
    }

    bool erase(const T& time) {
        if (!contains(time)) return false;

        if (is_push(time)) {
            return erase_push(time);
        } else if (is_pop(time)) {
            return erase_pop(time);
        }

        return false;
    }

    bool erase_pop(const T& time) {
        if (!is_pop(time)) return false;

        Node* left = split_left(time);
        Node* right = split_right(time);

        delete root;
        root = nullptr;

        if (right) ++right->lazy_prefix_sum_label;
        merge_left(left);
        merge_right(right);

        Node* bridge = left_nearest_bridge(time);

        left = split_left(bridge->time);

        root = get_rightmost_node_with_max_key_not_contained(root);

        root->label = 0;
        --(root->prefix_sum_label);
        right = split_right(root->time);
        if (right) --right->lazy_prefix_sum_label;
        merge_left(left);
        merge_right(right);

        ++sz;

        return true;
    }

    bool erase_push(const T& time) {
        if (!is_push(time)) return false;

        if (root->label == 0) {
            Node* left = split_left(time);
            Node* right = split_right(time);
            delete root;
            root = nullptr;
            merge_left(left);
            merge_right(right);
            --sz;
            return true;
        }

        Node* bridge = right_nearest_bridge(time);

        Node* right = split_right(bridge->time);

        if (!root->min_key_contained) {
            merge_right(right);
            return false;
        }

        Node* node = get_leftmost_node_with_min_key_contained(root);

        node->label = 1;
        ++(node->prefix_sum_label);
        merge_right(right);
        right = split_right(node->time);
        if (right) ++right->lazy_prefix_sum_label;
        merge_right(right);

        Node* left = split_left(time);
        right = split_right(time);

        delete root;
        root = nullptr;

        if (right) --right->lazy_prefix_sum_label;
        merge_left(left);
        merge_right(right);

        --sz;

        return true;
    }

    K top() const {
        assert(!empty());
        return root->min_key_contained.value();
    }

    bool contains(const T& time) {
        Node* node = lower_bound(root, time);
        if (node && node->time == time) {
            assert(node == root);
            return true;
        } else {
            return false;
        }
    }

    bool is_push(const T& time) {
        Node* node = lower_bound(root, time);
        if (node && node->time == time && node->label >= 0) {
            assert(node == root);
            return true;
        } else {
            return false;
        }
    }

    bool is_pop(const T& time) {
        Node* node = lower_bound(root, time);
        if (node && node->time == time && node->label < 0) {
            assert(node == root);
            return true;
        } else {
            return false;
        }
    }

    size_t get_index(const T& time) {
        assert(contains(time));
        if (root->left_child)
            return root->left_child->subtree_size;
        else
            return 0;
    }

    K get_kth_time(size_t index) {
        assert(root && index < root->subtree_size);
        return get_kth_node(index)->time;
    }

    size_t operation_sequence_len() const { return root ? root->subtree_size : 0; }

    size_t size() const { return sz; }

    bool empty() const { return sz == 0; }

    void clear() {
        Node* node = root;

        while (node) {
            if (node->left_child) {
                node = node->left_child;
            } else if (node->right_child) {
                node = node->right_child;
            } else {
                Node* parent = node->parent;
                if (parent) {
                    if (node == parent->left_child) {
                        delete node;
                        parent->left_child = nullptr;
                    } else {
                        delete node;
                        parent->right_child = nullptr;
                    }
                } else {
                    delete node;
                    root = nullptr;
                }
                node = parent;
            }
        }
    }

    ~PartialRetroactivePriorityQueue() { clear(); }
};
