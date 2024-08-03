#include <iostream>
#include <vector>
#include <cmath>
#include <deque>
#include <limits>

class TreeAncestorMaxSubNode {
public:
    int val, pref, suf, sm;

    TreeAncestorMaxSubNode(int x) : val(std::max(x, 0)), pref(std::max(x, 0)), suf(std::max(x, 0)), sm(x) {}
};

class TreeAncestorMaxSub {
public:
    TreeAncestorMaxSub(const std::vector<std::vector<int>> &edges, const std::vector<int> &values) {
        int n = edges.size();
        this->values = values;
        parent.assign(n, -1);
        depth.assign(n, -1);
        std::deque<int> stack = {0};
        depth[0] = 0;
        while (!stack.empty()) {
            int i = stack.front();
            stack.pop_front();
            for (int j: edges[i]) {
                if (depth[j] == -1) {
                    depth[j] = depth[i] + 1;
                    parent[j] = i;
                    stack.push_back(j);
                }
            }
        }

        cols = std::max(2, static_cast<int>(std::ceil(std::log2(n))) + 1);
        dp.assign(cols * n, -1);
        weight.assign(cols * n, TreeAncestorMaxSubNode(0));
        for (int i = 0; i < n; ++i) {
            dp[i * cols] = parent[i];
            if (i) {
                weight[i * cols] = TreeAncestorMaxSubNode(values[parent[i]]);
            } else {
                weight[i * cols] = TreeAncestorMaxSubNode(0);
            }
        }

        for (int j = 1; j < cols; ++j) {
            for (int i = 0; i < n; ++i) {
                int father = dp[i * cols + j - 1];
                TreeAncestorMaxSubNode pre = weight[i * cols + j - 1];
                if (father != -1) {
                    dp[i * cols + j] = dp[father * cols + j - 1];
                    weight[i * cols + j] = merge(pre, weight[father * cols + j - 1]);
                }
            }
        }
    }

    static TreeAncestorMaxSubNode merge(const TreeAncestorMaxSubNode &a, const TreeAncestorMaxSubNode &b) {
        TreeAncestorMaxSubNode ret(0);
        ret.pref = std::max(a.pref, a.sm + b.pref);
        ret.suf = std::max(b.suf, b.sm + a.suf);
        ret.sm = a.sm + b.sm;
        ret.val = std::max(std::max(a.val, b.val), a.suf + b.pref);
        return ret;
    }

    static TreeAncestorMaxSubNode reverse(TreeAncestorMaxSubNode &a) {
        std::swap(a.suf, a.pref);
        return a;
    }

    TreeAncestorMaxSubNode get_ancestor_node_max(int x, int y) {
        TreeAncestorMaxSubNode ans(values[x]);
        while (depth[x] > depth[y]) {
            int d = depth[x] - depth[y];
            ans = merge(ans, weight[x * cols + static_cast<int>(std::log2(d))]);
            x = dp[x * cols + static_cast<int>(std::log2(d))];
        }
        return ans;
    }

    int get_kth_ancestor(int node, int k) {
        for (int i = cols - 1; i >= 0; --i) {
            if (k & (1 << i)) {
                node = dp[node * cols + i];
                if (node == -1) break;
            }
        }
        return node;
    }

    int get_lca(int x, int y) {
        if (depth[x] < depth[y]) std::swap(x, y);
        while (depth[x] > depth[y]) {
            int d = depth[x] - depth[y];
            x = dp[x * cols + static_cast<int>(std::log2(d))];
        }
        if (x == y) return x;
        for (int k = static_cast<int>(std::log2(depth[x])); k >= 0; --k) {
            if (dp[x * cols + k] != dp[y * cols + k]) {
                x = dp[x * cols + k];
                y = dp[y * cols + k];
            }
        }
        return dp[x * cols];
    }

    int get_max_con_sum(int x, int y) {
        if (x == y) return TreeAncestorMaxSubNode(values[x]).val;
        int z = get_lca(x, y);
        if (z == x) {
            TreeAncestorMaxSubNode ans = get_ancestor_node_max(y, x);
            return ans.val;
        }
        if (z == y) {
            TreeAncestorMaxSubNode ans = get_ancestor_node_max(x, y);
            return ans.val;
        }

        int ax = get_kth_ancestor(x, depth[x] - depth[z]);
        int by = get_kth_ancestor(y, depth[y] - depth[z] - 1);
        TreeAncestorMaxSubNode a = get_ancestor_node_max(x, ax);
        TreeAncestorMaxSubNode b = get_ancestor_node_max(y, by);
        TreeAncestorMaxSubNode ans = merge(a, reverse(b));
        return ans.val;
    }

    std::vector<int> values;
private:
    std::vector<int> parent, depth, dp;
    std::vector<TreeAncestorMaxSubNode> weight;
    int cols;
};

class Solution {
public:
    Solution() {}

    static void main() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);

        int t;
        std::cin >> t;
        while (t--) {
            int n;
            std::cin >> n;
            std::vector<int> sub(1, 1);
            std::vector<std::vector<int>> dct(1);
            std::vector<std::tuple<int, int, int>> query;
            for (int i = 0; i < n; ++i) {
                std::string op;
                std::cin >> op;
                if (op == "+") {
                    int v, x;
                    std::cin >> v >> x;
                    --v;
                    sub.push_back(x);
                    dct[v].push_back(sub.size() - 1);
                    dct.push_back({});
                } else {
                    int u, v, k;
                    std::cin >> u >> v >> k;
                    query.emplace_back(u - 1, v - 1, k);
                }
            }

            TreeAncestorMaxSub ceil(dct, sub);
            std::vector<int> sub2(sub.size(), 0);
            for (int i = 0; i < sub.size(); ++i) {
                sub2[i] = -sub[i];
            }
            TreeAncestorMaxSub floor(dct, sub2);

            for (const auto &[u, v, k]: query) {
                int high = ceil.get_max_con_sum(u, v);
                int low = -floor.get_max_con_sum(u, v);
                std::cout << (low <= k && k <= high ? "YES" : "NO") << "\n";
            }
        }
    }
};

int main() { //https://codeforces.com/contest/1843/problem/F2
    Solution::main();
    return 0;
}
