#pragma once

#include <functional>
#include <vector>

template <typename I, typename M, typename W, typename F = std::function<M(M, M)>, typename G = std::function<M(M, W, I)>, typename H = std::function<M(M, I)>>
class RerootingDP {
   private:
    F op;
    M e;
    G propagate;
    H apply;
    std::vector<std::vector<std::pair<W, I>>> graph;
    std::vector<M> dp;

    bool built;

    constexpr void bottom_up(I node, const std::optional<I>& parent) {
        dp[node] = e;

        for (auto& [cost, next] : graph[node]) {
            if (parent && next == parent.value()) continue;

            bottom_up(next, node);

            dp[node] = op(dp[node], propagate(dp[next], cost, next));
        }

        dp[node] = apply(dp[node], node);
    }

    constexpr void top_down(I node, const std::optional<I>& parent, const M& m) {
        std::vector<M> left(graph[node].size() + 1, e), right(graph[node].size() + 1, e);

        for (I i = 0; i < (I)graph[node].size(); i++) {
            const auto& [cost, next] = graph[node][i];

            if (parent && next == parent.value()) {
                left[i + 1] = right[i] = propagate(m, cost, parent.value());
            } else {
                left[i + 1] = right[i] = propagate(dp[next], cost, next);
            }
        }

        for (I i = 0; i < (I)graph[node].size(); i++) {
            left[i + 1] = op(left[i], left[i + 1]);
        }

        for (I i = graph[node].size(); i > 0; i--) {
            right[i - 1] = op(right[i - 1], right[i]);
        }

        dp[node] = apply(right[0], node);

        for (I i = 0; i < (I)graph[node].size(); i++) {
            const auto& [cost, next] = graph[node][i];

            if (parent && next == parent) continue;

            top_down(next, node, apply(op(left[i], right[i + 1]), node));
        }
    }

    constexpr bool run(I root) {
        if (built) return false;

        bottom_up(root, std::nullopt);
        top_down(root, std::nullopt, e);

        built = true;
        return true;
    }

   public:
    constexpr RerootingDP(size_t n, const F& op, const M& e, const G& propagate, const H& apply) : op(op), e(e), propagate(propagate), apply(apply), graph(n), dp(n, e), built(false) {}

    constexpr RerootingDP(const std::vector<std::vector<std::pair<W, I>>>& graph, const F& op, const M& e, const G& propagate, const H& apply) : op(op), e(e), propagate(propagate), apply(apply), graph(graph), dp(graph.size(), e), built(false) {}

    constexpr bool add_edge(I u, I v, W cost = 1) {
        assert(u < (I)graph.size());
        assert(v < (I)graph.size());

        if (built) return false;

        graph[u].emplace_back(cost, v);
        graph[v].emplace_back(cost, u);

        return true;
    }

    constexpr M get(I node) {
        if (!built) run(node);

        return dp[node];
    }
};
