#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> nums(n);

    for (int i = 0; i < n; ++i) {
        cin >> nums[i].first >> nums[i].second;
    }

    sort(nums.begin(), nums.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });

    map<int, int> post;

    for (const auto& p : nums) {
        int a = p.first, b = p.second;
        int x = a;
        vector<int> lst;

        while (post.find(x) != post.end()) {
            lst.push_back(x);
            x = post[x];
        }

        if (x > b) {
            cout << "No" << endl;
            return;
        }

        for (int y : lst) {
            post[y] = x + 1;
        }

        post[x] = x + 1;
    }

    cout << "Yes" << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
