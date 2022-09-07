#include "graph/dijkstra.hpp"

#include <gtest/gtest.h>

#include <random>
#include <set>

#include "data_structure/union_find.hpp"

using namespace std;

const long long INF = 1ll << 60;

vector<vector<pair<long long, int>>> generate_random_undirected_graph(int n) {
    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> distrib(0, n - 1);

    vector<vector<pair<long long, int>>> graph(n);

    UnionFind uf(n);

    set<pair<int, int>> edges;

    while (uf.size(0) < n) {
        int u = distrib(engine);
        int v = distrib(engine);

        if (u == v) continue;
        if (u > v) swap(u, v);
        if (edges.count({u, v})) continue;

        long long c = distrib(engine) + 1;

        graph[u].emplace_back(c, v);
        graph[v].emplace_back(c, u);

        uf.unite(u, v);
        edges.insert({u, v});
    }

    return graph;
}

vector<vector<pair<long long, int>>> generate_random_undirected_complete_graph(int n) {
    random_device seed_gen;
    mt19937 engine(seed_gen());

    uniform_int_distribution<> distrib(0, n - 1);

    vector<vector<pair<long long, int>>> graph(n);

    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            long long c = distrib(engine) + 1;

            graph[u].emplace_back(c, v);
            graph[v].emplace_back(c, u);
        }
    }

    return graph;
}

vector<vector<pair<long long, int>>> generate_worst_undirected_complete_graph(int n) {
    vector<vector<pair<long long, int>>> graph(n);

    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            long long c = (long long)(n - u);
            if (v - u == 1) c = 0;

            graph[u].emplace_back(c, v);
            graph[v].emplace_back(c, u);
        }
    }

    return graph;
}

template <typename T>
std::vector<std::vector<T>> warshall_floyd(const std::vector<std::vector<std::pair<T, int>>>& graph) {
    const T INF = std::numeric_limits<T>::max();
    std::vector<std::vector<T>> distance(graph.size(), std::vector<T>(graph.size(), INF));
    for (int i = 0; i < graph.size(); i++) distance[i][i] = 0;

    for (int i = 0; i < graph.size(); i++) {
        for (const auto& [cost, j] : graph[i]) {
            distance[i][j] = min(distance[i][j], cost);
        }
    }

    for (int k = 0; k < graph.size(); k++) {
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph.size(); j++) {
                if (distance[i][k] < INF && distance[k][j] < INF && distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    return distance;
}

bool test_dijkstra_on_small_graph(int n, function<vector<vector<pair<long long, int>>>(int)> generate_graph) {
    int src = 0;

    vector graph = generate_graph(n);

    auto dist_array_wf = warshall_floyd(graph);

    auto dist_f = dijkstra_with_fibonacci_heap(src, graph);

    auto dist_b = dijkstra_with_binary_heap(src, graph);

    bool ret = true;

    for (int i = 0; i < n; i++) {
        if (dist_array_wf[src][i] != dist_b[i]) {
            ret = false;
        }

        if (dist_f[i] != dist_b[i]) {
            ret = false;
        }
    }

    return ret;
}

bool test_dijkstra(int n, function<vector<vector<pair<long long, int>>>(int)> generate_graph) {
    int src = 0;

    vector graph = generate_graph(n);

    auto dist_f = dijkstra_with_fibonacci_heap(src, graph);

    auto dist_b = dijkstra_with_binary_heap(src, graph);

    bool ret = true;

    for (int i = 0; i < n; i++) {
        if (dist_f[i] != dist_b[i]) {
            ret = false;
        }
    }

    return ret;
}

TEST(DijkstraTest, DijkstraOnSmallRandomUndirectedCompleteGraph) {
    auto generate_graph = generate_random_undirected_complete_graph;

    ASSERT_TRUE(test_dijkstra(10, generate_graph));
    ASSERT_TRUE(test_dijkstra(10, generate_graph));
    ASSERT_TRUE(test_dijkstra(10, generate_graph));
    ASSERT_TRUE(test_dijkstra(10, generate_graph));
    ASSERT_TRUE(test_dijkstra(10, generate_graph));
    ASSERT_TRUE(test_dijkstra(100, generate_graph));
    ASSERT_TRUE(test_dijkstra(100, generate_graph));
    ASSERT_TRUE(test_dijkstra(100, generate_graph));
    ASSERT_TRUE(test_dijkstra(100, generate_graph));
}

TEST(DijkstraTest, DijkstraOnSmallRandomUndirectedGraph) {
    auto generate_graph = generate_random_undirected_graph;

    ASSERT_TRUE(test_dijkstra(10, generate_graph));
    ASSERT_TRUE(test_dijkstra(10, generate_graph));
    ASSERT_TRUE(test_dijkstra(10, generate_graph));
    ASSERT_TRUE(test_dijkstra(10, generate_graph));
    ASSERT_TRUE(test_dijkstra(10, generate_graph));
    ASSERT_TRUE(test_dijkstra(100, generate_graph));
    ASSERT_TRUE(test_dijkstra(100, generate_graph));
    ASSERT_TRUE(test_dijkstra(100, generate_graph));
    ASSERT_TRUE(test_dijkstra(100, generate_graph));
}

TEST(DijkstraTest, DijkstraOnSmallWorstUndirectedCompleteGraph) {
    auto generate_graph = generate_worst_undirected_complete_graph;

    ASSERT_TRUE(test_dijkstra(10, generate_graph));
    ASSERT_TRUE(test_dijkstra(100, generate_graph));
}

TEST(DijkstraTest, DijkstraOnRandomUndirectedGraph) {
    auto generate_graph = generate_random_undirected_graph;

    ASSERT_TRUE(test_dijkstra(1000, generate_graph));
    ASSERT_TRUE(test_dijkstra(1000, generate_graph));
    ASSERT_TRUE(test_dijkstra(10000, generate_graph));
    ASSERT_TRUE(test_dijkstra(10000, generate_graph));
    ASSERT_TRUE(test_dijkstra(50000, generate_graph));
    ASSERT_TRUE(test_dijkstra(100000, generate_graph));
}

TEST(DikstraTest, DijkstraOnRandomUndirectedCompleteGraph) {
    auto generate_graph = generate_random_undirected_complete_graph;

    ASSERT_TRUE(test_dijkstra(1000, generate_graph));
    ASSERT_TRUE(test_dijkstra(1000, generate_graph));
    ASSERT_TRUE(test_dijkstra(5000, generate_graph));
}

TEST(DikstraTest, DijkstraOnWorstUndirectedCompleteGraph) {
    auto generate_graph = generate_worst_undirected_complete_graph;

    ASSERT_TRUE(test_dijkstra(1000, generate_graph));
    ASSERT_TRUE(test_dijkstra(5000, generate_graph));
}
