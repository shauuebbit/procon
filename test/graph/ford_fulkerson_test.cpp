#include "graph/ford_fulkerson.hpp"

#include <gtest/gtest.h>

#include <functional>
#include <iostream>
#include <random>
#include <set>
#include <vector>

using namespace std;

const long long INF = 1ll << 60;

vector<vector<pair<long long, int>>> generate_random_directed_graph(int n, int m) {
    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> dist(0, n - 1);

    vector<vector<pair<long long, int>>> graph(n);

    set<pair<int, int>> edges;

    while ((int)edges.size() < m) {
        int u = dist(engine);
        int v = dist(engine);

        if (u == v) continue;
        if (u > v) swap(u, v);
        if (edges.count({u, v})) continue;

        long long c = dist(engine) + 1;

        graph[u].emplace_back(c, v);

        edges.insert({u, v});
    }

    return graph;
}

bool test_max_flow_by_ford_fulkerson(int n, int m, function<vector<vector<pair<long long, int>>>(int, int)> generate_graph) {
    int src = 0;
    int dst = n - 1;

    vector g = generate_graph(n, m);

    FordFulkerson<long long> graph(n);

    for (int node = 0; node < (int)g.size(); node++) {
        for (auto [cost, next] : g[node]) {
            graph.add_edge(node, next, cost);
        }
    }

    long long min_cut = INF;

    long long mf = graph.max_flow(src, dst);

    auto mc = graph.min_cut(src);

    bool ret = false;

    for (int b = 0; b < (1 << n); b++) {
        if (~(b >> src) & 1) continue;
        if ((b >> dst) & 1) continue;

        long long f = 0;

        for (int node = 0; node < (int)g.size(); node++) {
            if (~(b >> node) & 1) continue;

            for (auto [cost, next] : g[node]) {
                if ((b >> next) & 1) continue;

                f += cost;
            }
        }
        
        if (f <= min_cut) {
            if (f < min_cut) ret = false;

            min_cut = f;

            bool r = true;
            for (int node = 0; node < (int)g.size(); node++) {
                if (((b >> node) & 1) != (mc[node])) {
                    r = false;
                    break;
                }
            }

            if (r) {
                ret = true;
            }
        }
    }

    return mf == min_cut && ret;
}

TEST(FordFulkersonTest, RandomSmall) {
    ASSERT_TRUE(test_max_flow_by_ford_fulkerson(10, 10, generate_random_directed_graph));
    ASSERT_TRUE(test_max_flow_by_ford_fulkerson(10, 20, generate_random_directed_graph));
    ASSERT_TRUE(test_max_flow_by_ford_fulkerson(20, 50, generate_random_directed_graph));
    ASSERT_TRUE(test_max_flow_by_ford_fulkerson(20, 100, generate_random_directed_graph));
}
