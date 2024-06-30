#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include <stack>
#include <cassert>

using namespace std;#include <iostream>
#include <vector>
#include <tuple>
#include <stack>
#include <cassert>

using namespace std;
using namespace std;

class TreeAncestor {
public:
    TreeAncestor(vector<vector<int>> &edges, int root = 0) {
        int n = edges.size();
        parent.resize(n, -1);
        depth.resize(n, -1);
        stack.push_back(root);
        depth[root] = 0;

        while (!stack.empty()) {
            int i = stack.back();
            stack.pop_back();
            for (int j: edges[i]) {
                if (depth[j] == -1) {
                    depth[j] = depth[i] + 1;
                    parent[j] = i;
                    stack.push_back(j);
                }
            }
        }

        cols = max(2, static_cast<int>(ceil(log2(n))));
        dp.assign(n, vector<int>(cols, -1));
        for (int i = 0; i < n; ++i) {
            dp[i][0] = parent[i];
        }

        for (int j = 1; j < cols; ++j) {
            for (int i = 0; i < n; ++i) {
                int father = dp[i][j - 1];
                if (father != -1) {
                    dp[i][j] = dp[father][j - 1];
                }
            }
        }
    }

    int get_kth_ancestor(int node, int k) {
        for (int i = cols - 1; i >= 0; --i) {
            if (k & (1 << i)) {
                node = dp[node][i];
                if (node == -1) {
                    break;
                }
            }
        }
        return node;
    }

    int get_lca(int x, int y) {
        if (depth[x] < depth[y]) {
            swap(x, y);
        }
        while (depth[x] > depth[y]) {
            int d = depth[x] - depth[y];
            x = dp[x][int(log2(d))];
        }
        if (x == y) {
            return x;
        }
        for (int k = int(log2(depth[x])); k >= 0; --k) {
            if (dp[x][k] != dp[y][k]) {
                x = dp[x][k];
                y = dp[y][k];
            }
        }
        return dp[x][0];
    }

    int get_dist(int u, int v) {
        int lca = get_lca(u, v);
        return depth[u] + depth[v] - 2 * depth[lca];
    }

private:
    vector<int> parent;
    vector<int> depth;
    vector<int> stack;
    int cols;
    vector<vector<int>> dp;
};

class HeavyChain {
public:
    int n;
    vector<vector<int>> dct;
    vector<int> parent, cnt_son, weight_son, top, dfn, rev_dfn, depth;

    HeavyChain(const vector<vector<int>>& dct, int root = 0) : n(dct.size()), dct(dct), parent(n, -1), cnt_son(n, 1), weight_son(n, -1), top(n, -1), dfn(n, 0), rev_dfn(n, 0), depth(n, 0) {
        build_weight(root);
        build_dfs(root);
    }

    void build_weight(int root) {
        stack<int> stk;
        stk.push(root);
        while (!stk.empty()) {
            int i = stk.top();
            stk.pop();
            if (i >= 0) {
                stk.push(-i-1);
                for (int j : dct[i]) {
                    if (j != parent[i]) {
                        stk.push(j);
                        parent[j] = i;
                        depth[j] = depth[i] + 1;
                    }
                }
            } else {
                i = -i-1;
                for (int j : dct[i]) {
                    if (j != parent[i]) {
                        cnt_son[i] += cnt_son[j];
                        if (weight_son[i] == -1 || cnt_son[j] > cnt_son[weight_son[i]]) {
                            weight_son[i] = j;
                        }
                    }
                }
            }
        }
    }

    void build_dfs(int root) {
        stack<pair<int, int>> stk;
        stk.emplace(root, root);
        int order = 0;
        while (!stk.empty()) {
            auto [i, tp] = stk.top();
            stk.pop();
            dfn[i] = order;
            rev_dfn[order] = i;
            top[i] = tp;
            order++;
            int w = weight_son[i];
            for (int j : dct[i]) {
                if (j != parent[i] && j != w) {
                    stk.emplace(j, j);
                }
            }
            if (w != -1) {
                stk.emplace(w, tp);
            }
        }
    }

    vector<pair<int, int>> query_chain(int x, int y) {
        vector<pair<int, int>> lst;
        while (top[x] != top[y]) {
            if (depth[top[x]] < depth[top[y]]) {
                swap(x, y);
            }
            assert(dfn[top[x]] <= dfn[x]);
            lst.emplace_back(dfn[top[x]], dfn[x]);
            x = parent[top[x]];
        }
        int a = dfn[x], b = dfn[y];
        if (a > b) swap(a, b);
        lst.emplace_back(a, b);
        return lst;
    }

    int query_lca(int x, int y) {
        while (top[x] != top[y]) {
            if (depth[top[x]] < depth[top[y]]) {
                swap(x, y);
            }
            x = parent[top[x]];
        }
        return depth[x] < depth[y] ? x : y;
    }
};

class RangeSetPointGet {
public:
    int n, initial;
    vector<int> lazy_tag;

    RangeSetPointGet(int n, int initial = -1) : n(n), initial(initial), lazy_tag(4 * n, initial) {}

    void build(const vector<int>& nums) {
        stack<tuple<int, int, int>> stk;
        stk.emplace(0, n - 1, 1);
        while (!stk.empty()) {
            auto [s, t, i] = stk.top();
            stk.pop();
            if (s == t) {
                _make_tag(i, nums[s]);
            } else {
                int m = s + (t - s) / 2;
                stk.emplace(s, m, i << 1);
                stk.emplace(m + 1, t, (i << 1) | 1);
            }
        }
    }

    void range_set(int left, int right, int val) {
        stack<tuple<int, int, int>> stk;
        stk.emplace(0, n - 1, 1);
        while (!stk.empty()) {
            auto [s, t, i] = stk.top();
            stk.pop();
            if (left <= s && t <= right) {
                _make_tag(i, val);
                continue;
            }
            int m = s + (t - s) / 2;
            _push_down(i);
            if (left <= m) {
                stk.emplace(s, m, i << 1);
            }
            if (right > m) {
                stk.emplace(m + 1, t, (i << 1) | 1);
            }
        }
    }

    int point_get(int ind) {
        int s = 0, t = n - 1, i = 1;
        while (true) {
            if (s == t && s == ind) {
                return lazy_tag[i];
            }
            int m = s + (t - s) / 2;
            _push_down(i);
            if (ind <= m) {
                t = m;
                i = i << 1;
            } else {
                s = m + 1;
                i = (i << 1) | 1;
            }
        }
    }

    vector<int> get() {
        stack<tuple<int, int, int>> stk;
        vector<int> nums(n);
        stk.emplace(0, n - 1, 1);
        while (!stk.empty()) {
            auto [s, t, i] = stk.top();
            stk.pop();
            if (s == t) {
                nums[s] = lazy_tag[i];
                continue;
            }
            int m = s + (t - s) / 2;
            _push_down(i);
            stk.emplace(s, m, i << 1);
            stk.emplace(m + 1, t, (i << 1) | 1);
        }
        return nums;
    }

private:
    void _push_down(int i) {
        if (lazy_tag[i] != initial) {
            lazy_tag[i << 1] = lazy_tag[i];
            lazy_tag[(i << 1) | 1] = lazy_tag[i];
            lazy_tag[i] = initial;
        }
    }

    void _make_tag(int i, int val) {
        lazy_tag[i] = val;
    }
};