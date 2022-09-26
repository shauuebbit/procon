#include "data_structure/partial_retroactive_priority_queue.hpp"

#include <gtest/gtest.h>

#include <queue>
#include <random>
#include <vector>

using namespace std;

TEST(PartialRetroactivePriorityQueueTest, PushLarge) {
    PartialRetroactivePriorityQueue<double, int> prpq;
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < 300000; i++) {
        if (i % 1000 != 1) {
            prpq.push(i * (i % 2 ? 1 : -1));
            pq.push(i * (i % 2 ? 1 : -1));

            ASSERT_EQ(prpq.top(), pq.top());
            ASSERT_EQ(prpq.size(), pq.size());
        }
    }
}

TEST(PartialRetroactivePriorityQueueTest, PopLarge) {
    PartialRetroactivePriorityQueue<double, int> prpq;
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < 300000; i++) {
        if (i % 1000 != 1) {
            prpq.push(i * (i % 2 ? 1 : -1));
            pq.push(i * (i % 2 ? 1 : -1));
        }
    }

    while (!pq.empty()) {
        prpq.pop();
        pq.pop();

        if (!pq.empty()) {
            ASSERT_EQ(prpq.top(), pq.top());
            ASSERT_EQ(prpq.size(), pq.size());
        }
    }

    ASSERT_TRUE(prpq.empty());
}

TEST(PartialRetroactivePriorityQueueTest, PushPopLarge) {
    PartialRetroactivePriorityQueue<double, int> prpq;
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < 300000; i++) {
        if (i % 1000 != 1) {
            prpq.push(i * (i % 2 ? 1 : -1));
            pq.push(i * (i % 2 ? 1 : -1));
        } else {
            prpq.pop();
            pq.pop();
        }

        if (!pq.empty()) {
            ASSERT_EQ(prpq.top(), pq.top());
            ASSERT_EQ(prpq.size(), pq.size());
        }
    }
}

TEST(PartialRetroactivePriorityQueueTest, RandomPushPop) {
    random_device seed_gen;
    mt19937 engine(seed_gen());

    const long long MAX = 1ll << 60;

    uniform_int_distribution<> dist_type(0, 3);
    uniform_int_distribution<long long> dist_key(-MAX, MAX);

    PartialRetroactivePriorityQueue<int, long long> prpq;
    priority_queue<long long, vector<long long>, greater<long long>> pq;

    int q = 300000;

    for (int t = 0; t < q; t++) {
        int p = dist_type(engine);
        if (p == 0 && !prpq.empty()) {
            prpq.pop();
            pq.pop();
        } else {
            long long key = dist_key(engine);
            prpq.push(key);
            pq.push(key);
        }

        if (!prpq.empty()) {
            ASSERT_EQ(prpq.top(), pq.top());
        }
    }
}

TEST(PartialRetroactivePriorityQueueTest, RandomInsertPush) {
    random_device seed_gen;
    mt19937 engine(seed_gen());

    const int MAX = 100000;

    const int FIRST = -100;
    const int LAST = 1000;

    uniform_int_distribution<> dist_time(FIRST, LAST);
    uniform_int_distribution<> dist_key(-MAX, MAX);

    PartialRetroactivePriorityQueue<int, int> prpq;
    priority_queue<int, vector<int>, greater<int>> pq;

    int q = 300000;

    for (int t = 0; t < q; t++) {
        int time = dist_time(engine);
        int key = dist_key(engine);

        if (prpq.insert_push(time, key)) {
            pq.push(key);
        }

        if (!prpq.empty()) {
            ASSERT_EQ(prpq.top(), pq.top());
        }

        ASSERT_EQ(prpq.size(), pq.size());
    }
}

TEST(PartialRetroactivePriorityQueueTest, RandomInsertPushInsertPop) {
    random_device seed_gen;
    mt19937 engine(seed_gen());

    const int MAX_TIME = 1000;
    const int MAX_KEY = 10000;

    const int POP = MAX_KEY + 100;
    const int EMPTY = -MAX_KEY - 100;

    uniform_int_distribution<> dist_type(0, 3);
    uniform_int_distribution<> dist_time(0, MAX_TIME);
    uniform_int_distribution<> dist_key(-MAX_KEY, MAX_KEY);

    PartialRetroactivePriorityQueue<int, int> prpq;
    vector<int> operation_sequence(MAX_TIME + 1, EMPTY);
    priority_queue<int, vector<int>, greater<int>> pq;

    int q = 3000;

    for (int t = 0; t < q; t++) {
        int tp = dist_type(engine);
        int time = dist_time(engine);

        if (operation_sequence[time] == EMPTY) {
            if (tp > 0) {
                int key = dist_key(engine);

                ASSERT_TRUE(prpq.insert_push(time, key));

                operation_sequence[time] = key;
            } else {
                int sz = 0;
                int min_sz = 0;
                for (int j = 0; j < time; j++) {
                    if (operation_sequence[j] == POP) {
                        --sz;
                    } else if (operation_sequence[j] != EMPTY) {
                        ++sz;
                    }
                }

                --sz;
                min_sz = min(sz, min_sz);

                for (int j = time + 1; j <= MAX_TIME; j++) {
                    if (operation_sequence[j] == POP) {
                        --sz;
                        min_sz = min(sz, min_sz);
                    } else if (operation_sequence[j] != EMPTY) {
                        ++sz;
                    }
                }

                if (min_sz < 0) {
                    ASSERT_FALSE(prpq.insert_pop(time));
                } else {
                    ASSERT_TRUE(prpq.insert_pop(time));
                    operation_sequence[time] = POP;
                }
            }
        }

        for (int j = 0; j <= MAX_TIME; j++) {
            if (operation_sequence[j] == POP)
                pq.pop();
            else if (operation_sequence[j] != EMPTY)
                pq.push(operation_sequence[j]);
        }

        if (!prpq.empty()) {
            ASSERT_EQ(prpq.top(), pq.top());
        } else {
            ASSERT_TRUE(pq.empty());
        }

        ASSERT_EQ(prpq.size(), pq.size());

        while (!pq.empty()) pq.pop();
    }
}

TEST(PartialRetroactivePriorityQueueTest, RandomInsertPushInsertPopErase) {
    random_device seed_gen;
    mt19937 engine(seed_gen());

    const int MAX_TIME = 1000;
    const int MAX_KEY = 10000;

    const int POP = MAX_KEY + 100;
    const int EMPTY = -MAX_KEY - 100;

    uniform_int_distribution<> dist_type(0, 3);
    uniform_int_distribution<> dist_time(0, MAX_TIME);
    uniform_int_distribution<> dist_key(-MAX_KEY, MAX_KEY);

    PartialRetroactivePriorityQueue<int, int> prpq;
    vector<int> operation_sequence(MAX_TIME + 1, EMPTY);
    priority_queue<int, vector<int>, greater<int>> pq;

    int q = 3000;

    for (int t = 0; t < q; t++) {
        int time = dist_time(engine);

        if (operation_sequence[time] == EMPTY) {
            int tp = dist_type(engine);
            if (tp > 1) {
                int key = dist_key(engine);

                ASSERT_TRUE(prpq.insert_push(time, key));

                operation_sequence[time] = key;
            } else {
                int sz = 0;
                int min_sz = 0;
                for (int j = 0; j < time; j++) {
                    if (operation_sequence[j] == POP) {
                        --sz;
                    } else if (operation_sequence[j] != EMPTY) {
                        ++sz;
                    }
                }

                --sz;
                min_sz = min(sz, min_sz);

                for (int j = time + 1; j <= MAX_TIME; j++) {
                    if (operation_sequence[j] == POP) {
                        --sz;
                        min_sz = min(sz, min_sz);
                    } else if (operation_sequence[j] != EMPTY) {
                        ++sz;
                    }
                }

                if (min_sz < 0) {
                    ASSERT_FALSE(prpq.insert_pop(time));
                } else {
                    ASSERT_TRUE(prpq.insert_pop(time));
                    operation_sequence[time] = POP;
                }
            }
        } else {
            if (operation_sequence[time] == POP) {
                ASSERT_TRUE(prpq.erase(time));
                operation_sequence[time] = EMPTY;
            } else {
                int sz = 0;
                int min_sz = 0;
                for (int j = 0; j < time; j++) {
                    if (operation_sequence[j] == POP) {
                        --sz;
                    } else if (operation_sequence[j] != EMPTY) {
                        ++sz;
                    }
                }

                for (int j = time + 1; j <= MAX_TIME; j++) {
                    if (operation_sequence[j] == POP) {
                        --sz;
                        min_sz = min(sz, min_sz);
                    } else if (operation_sequence[j] != EMPTY) {
                        ++sz;
                    }
                }

                if (min_sz < 0) {
                    ASSERT_FALSE(prpq.erase(time));
                } else {
                    ASSERT_TRUE(prpq.erase(time));
                    operation_sequence[time] = EMPTY;
                }
            }
        }

        for (int j = 0; j <= MAX_TIME; j++) {
            if (operation_sequence[j] == POP)
                pq.pop();
            else if (operation_sequence[j] != EMPTY)
                pq.push(operation_sequence[j]);
        }

        if (!prpq.empty()) {
            ASSERT_EQ(prpq.top(), pq.top());
        } else {
            ASSERT_TRUE(pq.empty());
        }

        ASSERT_EQ(prpq.size(), pq.size());

        while (!pq.empty()) pq.pop();
    }
}
