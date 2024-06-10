#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>

using namespace std;

int main() {
    // https://atcoder.jp/contests/abc208/tasks/abc208_e
    long long n, k;
    cin >> n >> k;

    string st = to_string(n);
    long long m = st.size();

    // Memoization for dfs
    map<tuple<long long, bool, bool, long long>, long long> memo;

    function<long long(long long, bool, bool, long long)> dfs = [&](long long i, bool is_limit, bool is_num,
                                                                    long long pre) {
        if (i == m) {
            return is_num && pre <= k ? 1LL : 0LL;
        }
        if (memo.find(make_tuple(i, is_limit, is_num, pre)) != memo.end()) {
            return memo[make_tuple(i, is_limit, is_num, pre)];
        }

        long long res = 0;
        if (!is_num) {
            res += dfs(i + 1, false, false, 0);
        }
        long long low = is_num ? 0 : 1;
        long long high = is_limit ? st[i] - '0' : 9;

        for (long long x = low; x <= high; ++x) {
            long long y = is_num ? pre * x : x;
            if (y > k) {
                y = k + 1;
            }
            res += dfs(i + 1, is_limit && (high == x), true, y);
        }
        memo[make_tuple(i, is_limit, is_num, pre)] = res;
        return res;
    };

    long long ans = dfs(0, true, false, 0);
    cout << ans << endl;

    return 0;
}
