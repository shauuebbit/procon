#pragma once

#include <limits>
#include <queue>
#include <vector>

template <typename T>
class FordFulkerson {
   private:
    struct Edge {
        T capacity;
        int from;
        int to;
    };

    std::vector<std::vector<Edge>> graph;

   public:
    FordFulkerson(int n) : graph(n) {}

    void add_edge(int from, int to, T capacity) {
        graph[from].push_back({capacity, (int)graph[to].size(), to});
        graph[to].push_back({T(0), (int)graph[from].size() - 1, from});
    }

    T max_flow(int src, int dst) {
        int t = 0;

        std::vector<int> used(graph.size(), -1);
        auto dfs = [&](auto&& this_function, int node, T current_flow) {
            if (node == dst) return current_flow;

            used[node] = t;

            for (Edge& e : graph[node]) {
                if (used[e.to] == t || e.capacity <= 0) continue;

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

        for (T f; (f = dfs(dfs, src, std::numeric_limits<T>::max())); ++t) {
            flow += f;
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
