#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    long long t;
    cin >> t;  // Read the number of test cases

    while (t--) {
        long long m, x;
        cin >> m >> x;

        vector<pair<long long, long long>> nums(m);
        long long tot = 0;

        // Reading the input
        for (long long i = 0; i < m; ++i) {
            cin >> nums[i].first >> nums[i].second;
            tot += nums[i].second;
        }

        vector<long long> dp(tot + 1, LLONG_MIN);
        dp[0] = 0;

        for (long long i = 0; i < m; ++i) {
            long long c = nums[i].first;
            long long h = nums[i].second;

            if (i > 0) {
                for (long long j = 0; j <= tot; ++j) {
                    if (dp[j] != LLONG_MIN) {
                        dp[j] += x;
                    }
                }
            }

            for (long long j = tot; j >= h; --j) {
                if (dp[j - h] >= c) {
                    dp[j] = max(dp[j], dp[j - h] - c);
                }
            }
        }

        for (long long ans = tot; ans >= 0; --ans) {
            if (dp[ans] >= 0) {
                cout << ans << endl;
                break;
            }
        }
    }

    return 0;
}
