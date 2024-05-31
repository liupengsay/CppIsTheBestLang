#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct BinarySearch {
    template<typename F>
    int find_int_right_strictly(int low, int high, F check) {
        while (low < high) {
            int mid = (low + high + 1) / 2;
            if (check(mid)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        return low;
    }
};

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i].first >> nums[i].second;
    }
    sort(nums.begin(), nums.end());

    vector<int> pre_min(n + 1, INT_MAX);
    vector<int> pre_max(n + 1, INT_MIN);
    for (int i = 0; i < n; ++i) {
        int y = nums[i].second;
        pre_min[i + 1] = min(pre_min[i], y);
        pre_max[i + 1] = max(pre_max[i], y);
    }

    vector<int> post_min(n + 1, INT_MAX);
    vector<int> post_max(n + 1, INT_MIN);
    for (int i = n - 1; i >= 0; --i) {
        int y = nums[i].second;
        post_min[i] = min(post_min[i + 1], y);
        post_max[i] = max(post_max[i + 1], y);
    }

    auto check = [&](int x) -> bool {
        int jj = 0;
        for (int ii = 0; ii < n; ++ii) {
            int xx = nums[ii].first;
            while (jj < n && nums[jj].first - xx < x) {
                jj++;
            }
            if (jj == n) return false;
            for (int a : {pre_min[ii + 1], pre_max[ii + 1]}) {
                for (int c : {post_min[jj], post_max[jj]}) {
                    if (abs(a - c) >= x) return true;
                }
            }
        }
        return false;
    };

    BinarySearch bs;
    int ans = bs.find_int_right_strictly(0, 1000000000, check);
    cout << ans << endl;

    return 0;
}
