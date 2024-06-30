#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>
#include <stack>
#include <climits>

using namespace std;

const int INF = INT_MAX;

class Tarjan {
public:
    Tarjan() {}

    tuple<set<int>, vector<pair<int, int>>, vector<int>, vector<int>> get_cut(int n, const vector<vector<int>>& edges) {
        vector<int> order(n, INF), low(n, INF), visit(n, 0), child(n, 0), parent(n, -1);
        set<int> cutting_point;
        vector<pair<int, int>> cutting_edge;
        int dfs_id = 0;

        for (int i = 0; i < n; ++i) {
            if (!visit[i]) {
                stack<pair<int, int>> stk;
                stk.emplace(i, 0);
                while (!stk.empty()) {
                    int cur = stk.top().first;
                    int ind = stk.top().second;
                    stk.pop();
                    if (!visit[cur]) {
                        visit[cur] = 1;
                        order[cur] = low[cur] = dfs_id++;
                    }
                    if (ind == edges[cur].size()) {
                        int nex = parent[cur];
                        if (nex != -1) {
                            int pa = parent[nex];
                            low[nex] = min(low[nex], low[cur]);
                            if (low[cur] > order[nex]) {
                                cutting_edge.emplace_back(min(nex, cur), max(nex, cur));
                            }
                            if (pa != -1 && low[cur] >= order[nex]) {
                                cutting_point.insert(nex);
                            } else if (pa == -1 && child[nex] > 1) {
                                cutting_point.insert(nex);
                            }
                        }
                    } else {
                        stk.emplace(cur, ind + 1);
                        int nex = edges[cur][ind];
                        if (nex == parent[cur]) {
                            continue;
                        }
                        if (!visit[nex]) {
                            parent[nex] = cur;
                            child[cur]++;
                            stk.emplace(nex, 0);
                        } else {
                            low[cur] = min(low[cur], order[nex]);
                        }
                    }
                }
            }
        }
        return make_tuple(cutting_point, cutting_edge, parent, order);
    }
};

class Solution {
public:
    Solution() {}

    static void main() {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> edges(n);
        vector<pair<int, int>> nums;
        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            --x; --y;
            edges[x].push_back(y);
            edges[y].push_back(x);
            nums.emplace_back(x, y);
        }

        Tarjan tarjan;
        auto [cutting_point, cutting_edge, parent, order] = tarjan.get_cut(n, edges);

        if (cutting_edge.empty()) {
            for (const auto& [x, y] : nums) {
                if (x == parent[y]) {
                    cout << x + 1 << " " << y + 1 << endl;
                } else if (y == parent[x]) {
                    cout << y + 1 << " " << x + 1 << endl;
                } else if (order[x] > order[y]) {
                    cout << x + 1 << " " << y + 1 << endl;
                } else {
                    cout << y + 1 << " " << x + 1 << endl;
                }
            }
        } else {
            cout << 0 << endl;
        }
    }
};

int main() {
    Solution::main();
    return 0;
}
