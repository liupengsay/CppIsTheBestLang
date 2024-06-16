#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <unordered_map>

using namespace std;

class UnionFind {
public:
    vector<int> root;
    vector<int> size;
    int part;

    UnionFind(int n) {
        root.resize(n);
        size.resize(n, 0);
        part = n;
        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }
    }

    int find(int x) {
        int y = x;
        while (x != root[x]) {
            x = root[x];
        }
        while (y != x) {
            int temp = root[y];
            root[y] = x;
            y = temp;
        }
        return x;
    }

    bool union_sets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return false;
        if (size[rootX] >= size[rootY]) {
            swap(rootX, rootY);
        }
        root[rootX] = rootY;
        size[rootY] += size[rootX];
        size[rootX] = 0;
        part--;
        return true;
    }

    unordered_map<int, vector<int>> get_root_part() {
        unordered_map<int, vector<int>> part_map;
        int n = root.size();
        for (int i = 0; i < n; ++i) {
            part_map[find(i)].push_back(i);
        }
        return part_map;
    }
};

vector<vector<int>> get_diff_matrix3(int m, int n, const vector<tuple<int, int, int, int, int>>& shifts) {
    vector<int> diff((m + 1) * (n + 1), 0);
    for (const auto& shift : shifts) {
        int xa, xb, ya, yb, d;
        tie(xa, xb, ya, yb, d) = shift;
        assert(0 <= xa && xa <= xb && xb <= m - 1);
        assert(0 <= ya && ya <= yb && yb <= n - 1);
        diff[xa * (n + 1) + ya] += d;
        diff[xa * (n + 1) + yb + 1] -= d;
        diff[(xb + 1) * (n + 1) + ya] -= d;
        diff[(xb + 1) * (n + 1) + yb + 1] += d;
    }

    vector<int> res((m + 1) * (n + 1), 0);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            res[(i + 1) * (n + 1) + j + 1] = res[(i + 1) * (n + 1) + j] + res[i * (n + 1) + j + 1]
                                             - res[i * (n + 1) + j] + diff[i * (n + 1) + j];
        }
    }

    vector<vector<int>> result(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = res[(i + 1) * (n + 1) + j + 1];
        }
    }
    return result;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int m, n;
        cin >> m >> n;
        vector<string> grid(m);
        for (int i = 0; i < m; ++i) {
            cin >> grid[i];
        }

        UnionFind uf(m * n);
        vector<int> row(m, 0), col(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '#') {
                    uf.size[i * n + j] = 1;
                } else {
                    row[i]++;
                    col[j]++;
                }
            }
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '#') {
                    if (i + 1 < m && grid[i + 1][j] == '#') {
                        uf.union_sets(i * n + j, (i + 1) * n + j);
                    }
                    if (j + 1 < n && grid[i][j + 1] == '#') {
                        uf.union_sets(i * n + j, i * n + j + 1);
                    }
                }
            }
        }

        auto group = uf.get_root_part();
        vector<tuple<int, int, int, int, int>> lst;

        for (const auto& g : group) {
            if (uf.size[g.first] > 0) {
                int x1 = max(*min_element(g.second.begin(), g.second.end(), [n](int a, int b) { return a / n < b / n; }) / n - 1, 0);
                int x2 = min(*max_element(g.second.begin(), g.second.end(), [n](int a, int b) { return a / n < b / n; }) / n + 1, m - 1);
                int y1 = max(*min_element(g.second.begin(), g.second.end(), [n](int a, int b) { return a % n < b % n; }) % n - 1, 0);
                int y2 = min(*max_element(g.second.begin(), g.second.end(), [n](int a, int b) { return a % n < b % n; }) % n + 1, n - 1);
                lst.emplace_back(x1, x2, y1, y2, -uf.size[g.first]);
                lst.emplace_back(x1, x2, 0, n - 1, uf.size[g.first]);
                lst.emplace_back(0, m - 1, y1, y2, uf.size[g.first]);
            }
        }

        auto res = get_diff_matrix3(m, n, lst);
        vector<int> lst_flat;
        for (const auto& row : res) {
            lst_flat.insert(lst_flat.end(), row.begin(), row.end());
        }

        int ans = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                ans = max(ans, row[i] + col[j] - (grid[i][j] == '.') + lst_flat[i * n + j]);
            }
        }

        cout << ans << endl;
    }
    return 0;
}
