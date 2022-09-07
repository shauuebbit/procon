#pragma once

#include <limits>
#include <queue>
#include <vector>

template <typename T>
class Dinic {
   private:
    struct Edge {
        T capacity;
        int from;
        int to;
    };

    std::vector<std::vector<Edge>> graph;

   public:
    Dinic(int n) : graph(n) {}

    void add_edge(int from, int to, T capacity) {
        graph[from].push_back({capacity, (int)graph[to].size(), to});
        graph[to].push_back({T(0), (int)graph[from].size() - 1, from});
    }

    T max_flow(int src, int dst) {
        std::vector<int> dist, idx;

        auto bfs = [&]() {
            dist.assign(graph.size(), -1);
            std::queue<int> q;
            dist[src] = 0;
            q.push(src);

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (Edge& e : graph[node]) {
                    if (e.capacity <= 0 || dist[e.to] >= 0) continue;

                    dist[e.to] = dist[node] + 1;
                    q.push(e.to);
                }
            }

            return dist[dst] >= 0;
        };

        auto dfs = [&](auto this_function, int node, T current_flow) {
            if (node == dst) return current_flow;

            for (int& next = idx[node]; next < (int)graph[node].size(); ++next) {
                Edge& e = graph[node][next];
                if (e.capacity <= 0 || dist[e.to] <= dist[node]) continue;

                T ret = this_function(this_function, e.to, std::min(current_flow, e.capacity));

                if (ret) {
                    e.capacity -= ret;
                    graph[e.to][e.from].capacity += ret;
                    return ret;
                }
            }

            return T(0);
        };

        T flow(0);

        while (idx.assign(graph.size(), 0), bfs()) {
            for (T f; f = dfs(dfs, src, std::numeric_limits<T>::max());) {
                flow += f;
            }
        }

        return flow;
    }

    std::vector<bool> min_cut(int src) {
        std::vector<bool> ret(graph.size(), false);
        std::queue<int> q;
        q.push(src);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            ret[node] = true;

            for (Edge& e : graph[node]) {
                if (e.capacity == 0 || ret[e.to]) continue;

                ret[e.to] = true;
                q.push(e.to);
            }
        }

        return ret;
    }
};
