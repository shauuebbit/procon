#pragma once

#include <memory>
#include <vector>

template <typename K>
class FibonacciHeap {
   private:
    struct Node {
        size_t id;
        K key;

        std::weak_ptr<Node> parent;
        std::shared_ptr<Node> child;
        std::shared_ptr<Node> right;
        std::weak_ptr<Node> left;

        size_t rank;
        bool marked;

        Node(size_t id, K key) : id(id), key(key), rank(0), marked(false) {}
    };

    std::shared_ptr<Node> min_node_ptr;
    size_t sz;

    std::vector<std::weak_ptr<Node>> node_pool;

    std::shared_ptr<Node> make_node(size_t id, K key) {
        std::shared_ptr node_ptr = std::make_shared<Node>(id, key);
        node_ptr->left = node_ptr;

        return node_ptr;
    }

    std::shared_ptr<Node> merge(std::shared_ptr<Node> node_ptr1, std::shared_ptr<Node> node_ptr2) {
        if (!node_ptr2) return node_ptr1;
        if (!node_ptr1) return node_ptr2;

        if (node_ptr1->key > node_ptr2->key) {
            std::swap(node_ptr1, node_ptr2);
        }

        std::shared_ptr<Node> rightmost_ptr1 = node_ptr1->left.lock();
        std::shared_ptr<Node> rightmost_ptr2 = node_ptr2->left.lock();

        rightmost_ptr1->right = node_ptr2;
        node_ptr2->left = rightmost_ptr1;
        node_ptr1->left = rightmost_ptr2;

        return node_ptr1;
    }

    std::shared_ptr<Node> shrink(std::shared_ptr<Node> node_ptr) {
        std::shared_ptr<Node> left = node_ptr->left.lock();
        std::shared_ptr<Node> parent = node_ptr->parent.lock();

        if (left->right == node_ptr) {
            left->right = node_ptr->right;

            if (node_ptr->right) {
                node_ptr->right->left = left;
            } else {
                if (parent)
                    parent->child->left = left;
                else
                    min_node_ptr->left = left;
            }
        } else {
            if (parent) {
                parent->child = node_ptr->right;
            } else if (min_node_ptr == node_ptr) {
                min_node_ptr = node_ptr->right;
            }

            if (node_ptr->right) {
                node_ptr->right->left = left;
            }
        }

        node_ptr->left = node_ptr;
        node_ptr->right.reset();
        node_ptr->parent.reset();

        return node_ptr;
    }

    std::shared_ptr<Node> link(std::shared_ptr<Node> node_ptr1, std::shared_ptr<Node> node_ptr2) {
        if (node_ptr1->key > node_ptr2->key) {
            std::swap(node_ptr1, node_ptr2);
        }

        node_ptr2->marked = false;

        node_ptr2->parent = node_ptr1;
        node_ptr1->child = merge(node_ptr1->child, node_ptr2);
        ++(node_ptr1->rank);

        return node_ptr1;
    }

    std::shared_ptr<Node> linking_step() {
        std::vector<std::shared_ptr<Node>> root_list;

        for (std::shared_ptr<Node> node_ptr = min_node_ptr; node_ptr;) {
            std::shared_ptr<Node> p = node_ptr;
            node_ptr = node_ptr->right;
            p = shrink(p);

            size_t rank = p->rank;

            while (rank < root_list.size() && root_list[rank]) {
                p = link(p, root_list[rank]);
                root_list[rank].reset();
                ++rank;
            }

            while (root_list.size() <= rank) {
                root_list.push_back(std::shared_ptr<Node>());
            }

            root_list[rank] = p;
        }

        std::shared_ptr<Node> ret;

        for (size_t rank = 0; rank < root_list.size(); rank++) {
            ret = merge(ret, root_list[rank]);
        }

        return ret;
    }

    void cut(std::shared_ptr<Node> node_ptr) {
        if (node_ptr == min_node_ptr) return;

        std::shared_ptr<Node> parent = node_ptr->parent.lock();

        if (!parent && min_node_ptr->key <= node_ptr->key) return;

        node_ptr = shrink(node_ptr);

        min_node_ptr = merge(min_node_ptr, node_ptr);

        if (parent) {
            --(parent->rank);

            if (parent->marked)
                cut(parent);
            else
                parent->marked = true;

            node_ptr->parent.reset();
        }
    }

   public:
    FibonacciHeap() : sz(0) {}

    size_t push(K key) {
        size_t id = node_pool.size();

        std::shared_ptr<Node> node_ptr = make_node(id, key);

        node_pool.push_back(node_ptr);
        ++sz;

        min_node_ptr = merge(min_node_ptr, node_ptr);

        return id;
    }

    std::pair<size_t, K> top() { return {min_node_ptr->id, min_node_ptr->key}; }

    bool pop() {
        if (empty()) return false;

        if (min_node_ptr->child) min_node_ptr->child->parent.reset();

        if (min_node_ptr->right) {
            min_node_ptr->right->left = min_node_ptr->left;
        }

        min_node_ptr = merge(min_node_ptr->right, min_node_ptr->child);

        min_node_ptr = linking_step();

        --sz;

        return true;
    }

    bool contains(size_t id) { return id >= node_pool.size() || !node_pool[id].expired(); }

    K get_key(size_t id) { return node_pool[id].lock()->key; }

    bool decrease_key(size_t id, K diff) {
        if (!contains(id)) return false;
        if (diff < 0) return false;

        std::shared_ptr<Node> node_ptr = node_pool[id].lock();

        node_ptr->key -= diff;

        cut(node_ptr);

        return true;
    }

    bool erase(size_t id) {
        if (!contains(id)) return false;

        std::shared_ptr<Node> node_ptr = node_pool[id].lock();

        if (node_ptr == min_node_ptr) return pop();

        for (std::shared_ptr<Node> p = node_ptr->child; p;) {
            std::shared_ptr<Node> q = p;
            p = p->right;
            q = shrink(q);
            min_node_ptr = merge(min_node_ptr, q);
        }

        std::shared_ptr<Node> parent = node_ptr->parent.lock();
        node_ptr = shrink(node_ptr);

        if (parent) {
            --(parent->rank);

            if (parent->marked)
                cut(parent);
            else
                parent->marked = true;
        }

        --sz;

        return true;
    }

    bool empty() { return sz == 0; }

    size_t size() { return sz; }

    void clear() {
        min_node_ptr.reset();
        sz = 0;
        node_pool.clear();
    }
};
