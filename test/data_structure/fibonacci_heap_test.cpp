#include "data_structure/fibonacci_heap.hpp"

#include <gtest/gtest.h>

#include <queue>

using namespace std;

TEST(FibonacciHeapTest, PushLarge) {
    FibonacciHeap<int> heap;
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < 300000; i++) {
        if (i % 1000 != 1) {
            heap.push(i * (i % 2 ? 1 : -1));
            pq.push(i * (i % 2 ? 1 : -1));

            ASSERT_EQ(heap.top().second, pq.top());
            ASSERT_EQ(heap.size(), pq.size());
        }
    }
}

TEST(FibonacciHeapTest, PopLarge) {
    FibonacciHeap<int> heap;
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < 300000; i++) {
        if (i % 1000 != 1) {
            heap.push(i * (i % 2 ? 1 : -1));
            pq.push(i * (i % 2 ? 1 : -1));
        }
    }

    while (!pq.empty()) {
        heap.pop();
        pq.pop();

        if (!pq.empty()) {
            ASSERT_EQ(heap.top().second, pq.top());
            ASSERT_EQ(heap.size(), pq.size());
        }
    }

    ASSERT_TRUE(heap.empty());
}

TEST(FibonacciHeapTest, PushPopLarge) {
    FibonacciHeap<int> heap;
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < 300000; i++) {
        if (i % 1000 != 1) {
            heap.push(i * (i % 2 ? 1 : -1));
            pq.push(i * (i % 2 ? 1 : -1));
        } else {
            heap.pop();
            pq.pop();
        }

        if (!pq.empty()) {
            ASSERT_EQ(heap.top().second, pq.top());
            ASSERT_EQ(heap.size(), pq.size());
        }
    }
}

TEST(FibonacciHeapTest, DecreaseKey1) {
    FibonacciHeap<int> heap;

    for (int i = 0; i < 10; i++) {
        heap.push(i == 0 ? 0 : 100);
    }

    ASSERT_EQ(heap.size(), 10);

    ASSERT_EQ(heap.top().second, 0);

    heap.pop();
    heap.decrease_key(4, 94);

    ASSERT_EQ(heap.get_key(4), 6);

    heap.decrease_key(9, 92);

    ASSERT_EQ(heap.get_key(9), 8);

    heap.pop();

    heap.decrease_key(7, 92);

    ASSERT_EQ(heap.get_key(7), 8);
}

TEST(FibonacciHeapTest, DecreaseKey2) {
    FibonacciHeap<int> heap;

    for (int i = 0; i < 10; i++) {
        heap.push(i == 0 ? 0 : 100);
    }

    heap.pop();
    heap.decrease_key(6, 96);

    ASSERT_EQ(heap.get_key(6), 4);

    heap.decrease_key(4, 91);

    ASSERT_EQ(heap.get_key(4), 9);

    heap.decrease_key(3, 96);

    ASSERT_EQ(heap.get_key(3), 4);

    heap.decrease_key(9, 93);

    ASSERT_EQ(heap.get_key(9), 7);

    heap.pop();
    heap.pop();
    heap.decrease_key(7, 95);

    ASSERT_EQ(heap.get_key(7), 5);

    heap.decrease_key(4, 3);

    ASSERT_EQ(heap.get_key(4), 6);

    heap.decrease_key(2, 93);

    ASSERT_EQ(heap.get_key(2), 7);

    heap.pop();
    heap.decrease_key(1, 90);

    ASSERT_EQ(heap.get_key(1), 10);
}
