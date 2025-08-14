#pragma once

#include <queue>
#include <vector>

#include "data_structure/fibonacci_heap.hpp"
#include "util/chmin_chmax.hpp"

template <typename T>
std::vector<T> dijkstra_with_binary_heap(int src, const std::vector<std::vector<std::pair<T, int>>>& graph) {
    const T INF = std::numeric_limits<T>::max();
    std::vector<T> distance(graph.size(), INF);

    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> pq;

    distance[src] = 0;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();

        if (distance[node] < cost) continue;

        for (const auto& [edge_cost, next] : graph[node]) {
            if (chmin(distance[next], cost + edge_cost)) {
                pq.emplace(distance[next], next);
            }
        }
    }

    return distance;
}

template <typename T>
std::vector<T> dijkstra_with_fibonacci_heap(int src, const std::vector<std::vector<std::pair<T, int>>>& graph) {
    const T INF = std::numeric_limits<T>::max();
    std::vector<T> distance(graph.size(), INF);

    FibonacciHeap<T> heap;

    distance[src] = 0;

    std::vector<int> ids(graph.size()), nodes(graph.size());

    for (int i = 0; i < (int)graph.size(); i++) {
        ids[i] = heap.push(i == src ? 0 : INF);
        nodes[ids[i]] = i;
    }

    while (!heap.empty()) {
        auto [id, cost] = heap.top();
        heap.pop();

        int node = nodes[id];

        if (distance[node] < cost) continue;

        for (auto [c, next] : graph[node]) {
            if (distance[next] > cost + c) {
                heap.decrease_key(ids[next], distance[next] - (cost + c));
                distance[next] = cost + c;
            }
        }
    }

    return distance;
}
