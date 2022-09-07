#pragma once

#include <functional>
#include <vector>

template <typename M, typename W, typename F = std::function<M(M, M)>, typename G = std::function<M(M, W, int)>, typename H = std::function<M(M, int)>>
class RerootingDP {
   private:
    int n;
    F op;
    M e;
    G propagate;
    H apply;
    std::vector<std::vector<std::pair<W, int>>> graph;
    std::vector<M> dp;

    void bottom_up(int node, int parent) {
        dp[node] = e;

        for (auto& [cost, next] : graph[node]) {
            if (next == parent) continue;

            bottom_up(next, node);

            dp[node] = op(dp[node], propagate(dp[next], cost, next));
        }

        dp[node] = apply(dp[node], node);
    }

    void top_down(int node, int parent, const M& m) {
        std::vector<M> left(graph[node].size() + 1, e), right(graph[node].size() + 1, e);

        for (int i = 0; i < graph[node].size(); i++) {
            const auto& [cost, next] = graph[node][i];

            if (next == parent) {
                left[i + 1] = right[i] = propagate(m, cost, parent);
            } else {
                left[i + 1] = right[i] = propagate(dp[next], cost, next);
            }
        }

        for (int i = 0; i < graph[node].size(); i++) {
            left[i + 1] = op(left[i], left[i + 1]);
        }

        for (int i = graph[node].size(); i > 0; i--) {
            right[i - 1] = op(right[i - 1], right[i]);
        }

        dp[node] = apply(right[0], node);

        for (int i = 0; i < graph[node].size(); i++) {
            const auto& [cost, next] = graph[node][i];

            if (next == parent) continue;

            top_down(next, node, apply(op(left[i], right[i + 1]), node));
        }
    }

   public:
    RerootingDP(int n, const F& op, const M& e, const G& propagate, const H& apply) : n(n), op(op), e(e), propagate(propagate), apply(apply), graph(n), dp(n, e) {}

    RerootingDP(const std::vector<std::vector<std::pair<W, int>>>& graph, const F& op, const M& e, const G& propagate, const H& apply) : n(graph.size()), op(op), e(e), propagate(propagate), apply(apply), graph(graph), dp(graph.size(), e) {}

    void add_edge(int u, int v, W cost = 1) {
        graph[u].emplace_back(cost, v);
        graph[v].emplace_back(cost, u);
    }

    void run() {
        bottom_up(0, -1);
        top_down(0, -1, e);
    }

    M get(int node) {
        return dp[node];
    }
};
