#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;  // Read the number of test cases

    while (t--) {
        int a, b, n, m;
        cin >> a >> b >> n >> m;

        set<pair<int, int>> lst_x, lst_y, pre;

        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            lst_x.emplace(x, y);
            lst_y.emplace(y, x);
            pre.emplace(x, y);
        }

        vector<int> ans(2, 0);
        int order = 0;
        int x1 = 1, y1 = 1;
        int x2 = a, y2 = b;

        for (int i = 0; i < m; ++i) {
            string s;
            int k;
            cin >> s >> k;

            if (s == "U") {
                x1 += k;
                while (!lst_x.empty() && lst_x.begin()->first < x1) {
                    auto it = lst_x.begin();
                    int xx = it->first, yy = it->second;
                    lst_x.erase(it);
                    if (pre.count({xx, yy})) {
                        ans[order]++;
                        pre.erase({xx, yy});
                    }
                }
            } else if (s == "D") {
                x2 -= k;
                while (!lst_x.empty() && lst_x.rbegin()->first > x2) {
                    auto it = prev(lst_x.end());
                    int xx = it->first, yy = it->second;
                    lst_x.erase(it);
                    if (pre.count({xx, yy})) {
                        ans[order]++;
                        pre.erase({xx, yy});
                    }
                }
            } else if (s == "L") {
                y1 += k;
                while (!lst_y.empty() && lst_y.begin()->first < y1) {
                    auto it = lst_y.begin();
                    int yy = it->first, xx = it->second;
                    lst_y.erase(it);
                    if (pre.count({xx, yy})) {
                        ans[order]++;
                        pre.erase({xx, yy});
                    }
                }
            } else if (s == "R") {
                y2 -= k;
                while (!lst_y.empty() && lst_y.rbegin()->first > y2) {
                    auto it = prev(lst_y.end());
                    int yy = it->first, xx = it->second;
                    lst_y.erase(it);
                    if (pre.count({xx, yy})) {
                        ans[order]++;
                        pre.erase({xx, yy});
                    }
                }
            }
            order = 1 - order;
        }

        cout << ans[0] << " " << ans[1] << endl;
    }

    return 0;
}
