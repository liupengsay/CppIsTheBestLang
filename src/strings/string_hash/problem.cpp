#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
#include <tuple>
#include <algorithm>

using namespace std;

class PointSetRangeHashReverse {
public:
    long long n, p, mod;
    vector<long long> pp, left_to_right, right_to_left;

    PointSetRangeHashReverse(long long n) : n(n) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis_p(26, 100);
        uniform_int_distribution<> dis_mod(1000000007, (1 << 31) - 1);

        p = dis_p(gen);
        mod = dis_mod(gen);
        pp = vector<long long>(n + 1, 1);
        for (long long j = 0; j < n; ++j) {
            pp[j + 1] = (pp[j] * p) % mod;
        }
        left_to_right = vector<long long>(4 * n, 0);
        right_to_left = vector<long long>(4 * n, 0);
    }

    void build(const vector<long long>& nums) {
        vector<tuple<long long, long long, long long>> stack = {make_tuple(0, n - 1, 1)};
        while (!stack.empty()) {
            auto [s, t, i] = stack.back();
            stack.pop_back();
            if (i >= 0) {
                if (s == t) {
                    left_to_right[i] = nums[s];
                    right_to_left[i] = nums[s];
                } else {
                    stack.push_back(make_tuple(s, t, ~i));
                    long long m = s + (t - s) / 2;
                    stack.push_back(make_tuple(s, m, i << 1));
                    stack.push_back(make_tuple(m + 1, t, (i << 1) | 1));
                }
            } else {
                i = ~i;
                push_up(i, s, t);
            }
        }
    }

    void push_up(long long i, long long s, long long t) {
        long long m = s + (t - s) / 2;
        long long length = t - m;
        left_to_right[i] = (left_to_right[i << 1] * pp[length] + left_to_right[(i << 1) | 1]) % mod;

        length = m - s + 1;
        right_to_left[i] = (right_to_left[(i << 1) | 1] * pp[length] + right_to_left[i << 1]) % mod;
    }

    vector<long long> get() {
        vector<tuple<long long, long long, long long>> stack = {make_tuple(0, n - 1, 1)};
        vector<long long> nums(n, 0);
        while (!stack.empty()) {
            auto [s, t, i] = stack.back();
            stack.pop_back();
            if (s == t) {
                nums[s] = left_to_right[i];
                continue;
            }
            long long m = s + (t - s) / 2;
            stack.push_back(make_tuple(s, m, i << 1));
            stack.push_back(make_tuple(m + 1, t, (i << 1) | 1));
        }
        return nums;
    }

    void point_set(long long left, long long right, long long val) {
        vector<tuple<long long, long long, long long>> stack = {make_tuple(0, n - 1, 1)};
        while (!stack.empty()) {
            auto [s, t, i] = stack.back();
            stack.pop_back();
            if (i >= 0) {
                if (left <= s && t <= right) {
                    right_to_left[i] = left_to_right[i] = val;
                    continue;
                }
                long long m = s + (t - s) / 2;
                stack.push_back(make_tuple(s, t, ~i));
                if (left <= m) {
                    stack.push_back(make_tuple(s, m, i << 1));
                }
                if (right > m) {
                    stack.push_back(make_tuple(m + 1, t, (i << 1) | 1));
                }
            } else {
                i = ~i;
                push_up(i, s, t);
            }
        }
    }

    long long range_hash(long long left, long long right) {
        vector<tuple<long long, long long, long long>> stack = {make_tuple(0, n - 1, 1)};
        long long ans = 0;
        while (!stack.empty()) {
            auto [s, t, i] = stack.back();
            stack.pop_back();
            if (left <= s && t <= right) {
                long long length = t - s + 1;
                ans = (ans * pp[length] + left_to_right[i]) % mod;
                continue;
            }
            long long m = s + (t - s) / 2;
            if (right > m) {
                stack.push_back(make_tuple(m + 1, t, (i << 1) | 1));
            }
            if (left <= m) {
                stack.push_back(make_tuple(s, m, i << 1));
            }
        }
        return ans;
    }

    long long range_hash_reverse(long long left, long long right) {
        vector<tuple<long long, long long, long long>> stack = {make_tuple(0, n - 1, 1)};
        long long ans = 0;
        while (!stack.empty()) {
            auto [s, t, i] = stack.back();
            stack.pop_back();
            if (left <= s && t <= right) {
                long long length = t - s + 1;
                ans = (ans * pp[length] + right_to_left[i]) % mod;
                continue;
            }
            long long m = s + (t - s) / 2;
            if (left <= m) {
                stack.push_back(make_tuple(s, m, i << 1));
            }
            if (right > m) {
                stack.push_back(make_tuple(m + 1, t, (i << 1) | 1));
            }
        }
        return ans;
    }
};

class Solution {
public:
    void main() {
        long long n;
        cin >> n;
        PointSetRangeHashReverse tree1(n);
        vector<long long> nums(n);
        for (long long i = 0; i < n; ++i) {
            cin >> nums[i];
            nums[i]--;
        }
        for (long long num : nums) {
            tree1.point_set(num, num, 1);
            if (num == 0 || num == n - 1) {
                continue;
            }
            long long length = min(num + 1, n - num);
            long long cur1 = tree1.range_hash(num - length + 1, num);
            long long cur2 = tree1.range_hash_reverse(num, num + length - 1);
            if (cur1 != cur2) {
                cout << "YES" << endl;
                return;
            }
        }
        cout << "NO" << endl;
    }
};

int main() { // https://codeforces.com/problemset/problem/452/F
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    sol.main();

    return 0;
}
