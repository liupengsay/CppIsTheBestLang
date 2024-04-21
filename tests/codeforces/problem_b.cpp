#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

class Solution {
public:
    void solve() {
        int n, k;
        std::cin >> n >> k;

        std::vector<std::vector<std::pair<int, int>>> dct(n);
        for (int i = 1; i < n; i++) {
            int x, y, z;
            std::cin >> x >> y >> z;
            x--;
            y--;
            dct[x].emplace_back(y, z);
        }
        for (int i = 0; i < n; i++) {
            std::reverse(dct[i].begin(), dct[i].end());
        }

        if (n == 1) {
            std::cout << 0 << std::endl;
            return;
        }

        std::vector<int> dis(n);
        std::stack<int> st;
        st.push(0);
        while (!st.empty()) {
            int x = st.top();
            st.pop();
            for (auto [y, w]: dct[x]) {
                dis[y] = dis[x] + w;
                st.push(y);
            }
        }

        int low = 0;
        int high = 1000000000;

        int ans = binarySearch(low, high, k, dis, dct);
        std::cout << ans << std::endl;
    }

private:
    int findHigh(const std::vector<std::vector<std::pair<int, int>>> &dct) {
        std::stack<std::pair<int, int>> st;
        int d = 0;
        st.push({0, 0});
        while (!st.empty()) {
            auto [a, s] = st.top();
            st.pop();
            if (a >= 0) {
                d += s;
                st.push({~a, s});
                for (auto [b, dd]: dct[a]) {
                    st.push({b, dd});
                }
            } else {
                d += s;
            }
        }
        return d;
    }

    bool check(int t, int k, const std::vector<int> &dis, const std::vector<std::vector<std::pair<int, int>>> &dct) {
        std::stack<std::pair<int, int>> st;
        int d = 0;
        int res = 0;
        st.push({0, 0});
        while (!st.empty()) {
            auto [a, s] = st.top();
            st.pop();
            if (a >= 0) {
                d += s;
                st.push({~a, s});
                for (auto [b, dd]: dct[a]) {
                    st.push({b, dd});
                }
            } else {
                a = ~a;
                if (dct[a].empty()) {
                    if (d + dis[a] > t) {
                        res++;
                        if (res + 1 > k) {
                            return false;
                        }
                        d = dis[a];
                    }
                }
                d += s;
            }
        }
        return true;
    }

    int binarySearch(int low, int high, int k, const std::vector<int> &dis,
                     const std::vector<std::vector<std::pair<int, int>>> &dct) {
        while (low < high - 1) {
            int mid = low + (high - low) / 2;
            if (check(mid, k, dis, dct)) {
                high = mid;
            } else {
                low = mid;
            }
        }
        return check(low, k, dis, dct) ? low : high;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}