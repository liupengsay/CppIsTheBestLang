#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();

class FastIO {
public:
    static int readInt() {
        int x;
        cin >> x;
        return x;
    }

    static vector<int> readListInts() {
        int n;
        cin >> n;
        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }
        return nums;
    }

    static void print(int x) {
        cout << x << endl;
    }
};

class Solution {
public:
    static void main() {
        int m, n, k;
        m = FastIO::readInt();
        n = FastIO::readInt();
        k = FastIO::readInt();

        vector<vector<int>> grid(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            grid[i] = FastIO::readListInts();
        }

        auto check = [&](int x, int y) {
            vector<vector<int>> dis(m, vector<int>(n, INF));
            dis[x][y] = 0;
            deque<vector<int>> stack;
            stack.push_back({x, y, 0});
            while (!stack.empty()) {
                vector<int> curr = stack.front();
                stack.pop_front();
                int x = curr[0];
                int y = curr[1];
                int d = curr[2];
                vector<vector<int>> directions = {{x + 1, y}, {x - 1, y}, {x, y - 1}, {x, y + 1}};
                for (const vector<int>& dir : directions) {
                    int a = dir[0];
                    int b = dir[1];
                    if (a >= 0 && a < m && b >= 0 && b < n && grid[a][b] != -1 && dis[a][b] > d + k) {
                        dis[a][b] = d + k;
                        stack.push_back({a, b, d + k});
                    }
                }
            }
            return dis;
        };

        vector<vector<int>> dis1 = check(0, 0);
        vector<vector<int>> dis2 = check(m - 1, n - 1);
        int ans = INF;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ans = min(ans, dis1[i][j] + dis2[i][j]);
            }
        }
        int pre = INF;
        int post = INF;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != -1) {
                    pre = min(pre, dis1[i][j] + grid[i][j]);
                    post = min(post, dis2[i][j] + grid[i][j]);
                }
            }
        }
        if (pre + post < ans) {
            ans = pre + post;
        }
        FastIO::print(ans < INF ? ans : -1);
    }
};

int main() {
    Solution::main();
    return 0;
}