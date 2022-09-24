#pragma once

#include <cassert>
#include <functional>

template <typename K, typename V, typename E, typename F = std::function<V(V, V)>, typename A = std::function<V(V, E)>, typename G = std::function<E(E, E)>>
class SplayTree {
   private:
    struct Node {
        K key;
        V value;
        V acc;
        E lazy;
        size_t subtree_size;
        Node* left_child;
        Node* right_child;
        Node* parent;

        Node(const K& key, const V& value) : key(key), value(value), subtree_size(1), left_child(nullptr), right_child(nullptr), parent(nullptr) {}
    };

    F op;
    A act;
    G cp;
    V e;
    E id;

    Node* root;

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

    void propagate(Node* node) {
        if (!node || node->lazy == id) return;
        node->value = act(node->value, node->lazy);
        node->acc = act(node->acc, node->lazy);
        if (node->left_child) {
            node->left_child->lazy = cp(node->left_child->lazy, node->lazy);
        }
        if (node->right_child) {
            node->right_child->lazy = cp(node->right_child->lazy, node->lazy);
        }
        node->lazy = id;
    }

    void recalc(Node* node) {
        if (!node) return;
        node->acc = node->value;
        node->subtree_size = 1;
        if (node->left_child) {
            assert(node->left_child->lazy == id);
            node->acc = op(node->left_child->acc, node->acc);
            node->subtree_size += node->left_child->subtree_size;
        }
        if (node->right_child) {
            assert(node->right_child->lazy == id);
            node->acc = op(node->acc, node->right_child->acc);
            node->subtree_size += node->right_child->subtree_size;
        }
    }

    Node* get_min_key_node(Node* node) {
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

    Node* get_max_key_node(Node* node) {
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

    Node* get_kth_node(size_t index) {
        Node* node = root;

        propagate(node);

        while (true) {
            propagate(node->left_child);
            propagate(node->right_child);

            if (node->left_child) {
                if (index < node->left_child->subtree_size) {
                    node = node->left_child;
                } else if (index == node->left_child->subtree_size) {
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

    Node* lower_bound(Node* node, const K& key) {
        Node* ret = nullptr;

        propagate(node);

        while (node) {
            propagate(node->left_child);
            propagate(node->right_child);

            if (key <= node->key) {
                ret = node;
                if (node->left_child)
                    node = node->left_child;
                else
                    break;
            } else if (node->key < key) {
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

    Node* upper_bound(Node* node, const K& key) {
        Node* ret = nullptr;

        propagate(node);

        while (node) {
            propagate(node->left_child);
            propagate(node->right_child);

            if (key < node->key) {
                ret = node;
                if (node->left_child)
                    node = node->left_child;
                else
                    break;
            } else if (node->key <= key) {
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

    Node* split_left(const K& key) {
        Node* node = lower_bound(root, key);

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

    Node* split_right(const K& key) {
        Node* right = upper_bound(root, key);

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
            root = get_min_key_node(root);

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
            root = get_max_key_node(root);

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
    SplayTree(const F& op, const A& act, const G& cp, const V& e, const E& id) : op(op), act(act), cp(cp), e(e), id(id), root(nullptr) {}

    bool insert(const K& key, const V& value) {
        if (contains(key)) return false;

        Node* right = split_right(key);
        Node* left = root;

        root = new Node(key, value);
        root->acc = e;
        root->lazy = id;

        merge_left(left);
        merge_right(right);

        return true;
    }

    bool erase(const K& key) {
        if (!contains(key)) return false;

        Node* left = split_left(key);
        Node* right = split_right(key);

        delete root;
        root = nullptr;

        merge_left(left);
        merge_right(right);

        return true;
    }

    bool contains(const K& key) {
        Node* node = lower_bound(root, key);
        if (node && node->key == key) {
            assert(node == root);
            return true;
        } else {
            return false;
        }
    }

    bool update(const K& key, const V& value) {
        if (!contains(key)) return false;

        assert(root->lazy == id);

        root->value = value;
        root->acc = value;
        root->lazy = id;

        propagate(root->left_child);
        propagate(root->right_child);
        recalc(root);

        return true;
    }

    void update(const K& left_key, const K& right_key, const E& g) {
        Node* left = split_left(left_key);
        Node* right = split_right(right_key);

        if (root) root->lazy = cp(root->lazy, g);

        merge_left(left);
        merge_right(right);
    }

    V fold(const K& left_key, const K& right_key) {
        Node* left = split_left(left_key);
        Node* right = split_right(right_key);

        V ret = e;
        if (root) ret = root->acc;

        merge_left(left);
        merge_right(right);

        return ret;
    }

    size_t get_index(const K& key) {
        assert(contains(key));
        if (root->left_child)
            return root->left_child->subtree_size;
        else
            return 0;
    }

    K get_kth_key(size_t index) {
        assert(index < size());
        return get_kth_node(index)->key;
    }

    V fold() const { return root ? root->acc : e; }

    size_t size() const { return root ? root->subtree_size : 0; }

    bool empty() const { return !root; }

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

    ~SplayTree() { clear(); }
};
