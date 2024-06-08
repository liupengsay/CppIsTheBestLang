#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

class UnionFind {
public:
    UnionFind(int n) : root_or_size(n, -1), n(n) {}

    void initialize() {
        for (int i = 0; i < n; ++i) {
            root_or_size[i] = -1;
        }
    }

    int find(int x) {
        int y = x;
        while (root_or_size[x] >= 0) {
            x = root_or_size[x];
        }
        while (y != x) {
            root_or_size[y] = x;
            y = root_or_size[y];
        }
        return x;
    }

    bool union_left(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);
        if (root_x == root_y) return false;
        root_or_size[root_x] += root_or_size[root_y];
        root_or_size[root_y] = root_x;
        return true;
    }

    bool union_right(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);
        if (root_x == root_y) return false;
        root_or_size[root_y] += root_or_size[root_x];
        root_or_size[root_x] = root_y;
        return true;
    }

    bool is_connected(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return -root_or_size[find(x)];
    }

    std::unordered_map<int, std::vector<int>> get_root_part() {
        std::unordered_map<int, std::vector<int>> result;
        for (int i = 0; i < n; ++i) {
            result[find(i)] = part[find(i)];
        }
        return result;
    }

private:
    std::vector<int> root_or_size;
    std::unordered_map<int, std::vector<int>> part;
    int n;
};

class FastIO {
public:
    int read_int() {
        int x;
        std::cin >> x;
        return x;
    }

    void st(const std::string& x) {
        std::cout << x << std::endl;
    }
};

class Solution {
public:
    static void main() {
        int q;
        FastIO ac;
        std::cin >> q;
        for (int _ = 0; _ < q; ++_) {
            int n;
            std::cin >> n;
            std::vector<int> x(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> x[i];
            }
            std::vector<int> p(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> p[i];
            }
            UnionFind ufl(n), ufr(n);
            for (int i = 1; i < n; ++i) {
                if (x[i] - x[i - 1] <= p[i]) {
                    ufl.union_left(i - 1, i);
                }
            }
            for (int i = n - 2; i >= 0; --i) {
                if (x[i + 1] - x[i] <= p[i]) {
                    ufr.union_right(i, i + 1);
                }
            }
            if (ufl.is_connected(0, n - 1) || ufr.is_connected(0, n - 1)) {
                ac.st("YES");
            } else {
                bool connected = false;
                for (int i = 0; i < n - 1; ++i) {
                    if ((ufl.is_connected(0, i) && ufr.is_connected(i + 1, n - 1)) ||
                        (ufr.is_connected(0, i) && ufl.is_connected(i + 1, n - 1)) ||
                        (ufr.is_connected(0, i) && ufr.is_connected(i + 1, n - 1)) ||
                        (ufl.is_connected(0, i) && ufl.is_connected(i + 1, n - 1))) {
                        connected = true;
                        break;
                    }
                }
                ac.st(connected ? "YES" : "NO");
            }
        }
    }
};

int main() {
    Solution::main();
    return 0;
}
