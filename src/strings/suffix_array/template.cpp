#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <climits>
#include <tuple>

using namespace std;

class SuffixArray {
public:
    SuffixArray() {}

    static tuple<vector<long long>, vector<long long>, vector<long long>> build(const vector<long long>& s, long long sig) {
        long long n = s.size();
        vector<long long> sa(n), rk(n), tmp(n), height(n);
        for (long long i = 0; i < n; ++i) sa[i] = i, rk[i] = s[i];
        long long ll = 0;
        while (true) {
            vector<long long> p;
            for (long long i = n - ll; i < n; ++i) p.push_back(i);
            for (long long i = 0; i < n; ++i) if (sa[i] >= ll) p.push_back(sa[i] - ll);
            vector<long long> cnt(sig, 0);
            for (long long i = 0; i < n; ++i) cnt[rk[i]]++;
            for (long long i = 1; i < sig; ++i) cnt[i] += cnt[i - 1];
            for (long long i = n - 1; i >= 0; --i) sa[--cnt[rk[p[i]]]] = p[i];
            auto equal = [&rk, n](long long i, long long j, long long l) {
                if (rk[i] != rk[j]) return false;
                if (i + l >= n && j + l >= n) return true;
                if (i + l < n && j + l < n) return rk[i + l] == rk[j + l];
                return false;
            };
            sig = 0;
            for (long long i = 0; i < n; ++i) tmp[i]=0;
            tmp[sa[0]] = 0;
            for (long long i = 1; i < n; ++i) tmp[sa[i]] = equal(sa[i], sa[i - 1], ll) ? sig : ++sig;

            for (long long i = 0; i < n; ++i) rk[i]=tmp[i];
            if (++sig == n) break;
            ll = ll > 0 ? (ll << 1) : 1;
        }
        long long k = 0;
        for (long long i = 0; i < n; ++i) {
            if (rk[i] == 0) continue;
            long long j = sa[rk[i] - 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            height[rk[i]] = k;
            k = k-1<0?0:k-1;
        }
        return make_tuple(sa, rk, height);
    }
};

class Solution {
public:
    static void main() {
        long long n;
        cin >> n;
        string str;
        cin >> str;
        vector<long long> s(n);
        for (long long i = 0; i < n; ++i) s[i] = str[i] - 'a';
        auto [sa, rk, nums] = SuffixArray::build(s, 26);
        vector<long long> pre(n, 0);
        stack<long long> stk;
        stk.push(0);
        for (long long i = 1; i < n; ++i) {
            while (!stk.empty() && nums[stk.top()] > nums[i]) stk.pop();
            pre[i] = pre[stk.top()] + nums[i] * (i - stk.top());
            stk.push(i);
        }

        nums.push_back(0);
        vector<long long> post(n + 1, 0);
        stk = stack<long long>();
        stk.push(n);
        for (long long i = n - 1; i >= 0; --i) {
            while (!stk.empty() && nums[stk.top()] > nums[i]) stk.pop();
            post[i] = post[stk.top()] + nums[i] * (stk.top() - i);
            stk.push(i);
        }

        vector<long long> ans(n);
        for (long long i = 0; i < n; ++i) {
            ans[i] = n - i;
            ans[i] += pre[rk[i]] + post[rk[i] + 1];
        }

        for (long long i : ans) cout << i << endl;
    }
};

int main() {
    Solution::main();
    return 0;
}
