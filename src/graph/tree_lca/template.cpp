#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

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

int main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> dct(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;  // Adjust for 0-based indexing
        dct[u].push_back(v);
        dct[v].push_back(u);
    }

    TreeAncestor tree(dct, 0);

    for (int i = 0; i < q; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;  // Adjust for 0-based indexing
        int dis = tree.get_dist(u, v);
        if (dis % 2 == 0) {
            cout << "Town" << endl;
        } else {
            cout << "Road" << endl;
        }
    }

    return 0;
}
