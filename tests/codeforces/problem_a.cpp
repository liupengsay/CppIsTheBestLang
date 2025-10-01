#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;

const int INF = 1e16;

class PointSetRangeMaxSubSum {
public:
    int n;
    vector<int> cover, left, right, sum;

    PointSetRangeMaxSubSum(int n, int initial = INF) : n(n) {
        cover.resize(4 * n, -initial);
        left.resize(4 * n, -initial);
        right.resize(4 * n, -initial);
        sum.resize(4 * n, 0);
    }

    void build(const vector<int>& nums) {
        vector<tuple<int, int, int>> stack;
        stack.push_back({0, n - 1, 1});

        while (!stack.empty()) {
            auto [s, t, i] = stack.back();
            stack.pop_back();

            if (i >= 0) {
                if (s == t) {
                    _make_tag(i, nums[s]);
                    continue;
                }
                stack.push_back({s, t, -i-1});
                int m = s + (t - s) / 2;
                stack.push_back({s, m, i << 1});
                stack.push_back({m + 1, t, (i << 1) | 1});
            } else {
                i = -i-1;
                _push_up(i);
            }
        }
    }

    void _make_tag(int i, int val) {
        cover[i] = val;
        left[i] = val;
        right[i] = val;
        sum[i] = val;
    }

    static vector<int> _range_merge_to_disjoint(const vector<int>& res1, const vector<int>& res2) {
        vector<int> res(4, -INF);
        res[0] = max(res1[0], res2[0]);
        res[0] = max(res[0], res1[2] + res2[1]);
        res[1] = max(res1[1], res1[3] + res2[1]);
        res[2] = max(res2[2], res2[3] + res1[2]);
        res[3] = res1[3] + res2[3];
        return res;
    }

    void _push_up(int i) {
        vector<int> res1 = {cover[i << 1], left[i << 1], right[i << 1], sum[i << 1]};
        vector<int> res2 = {cover[(i << 1) | 1], left[(i << 1) | 1], right[(i << 1) | 1], sum[(i << 1) | 1]};
        vector<int> merged = _range_merge_to_disjoint(res1, res2);
        cover[i] = merged[0];
        left[i] = merged[1];
        right[i] = merged[2];
        sum[i] = merged[3];
    }

    int point_set_range_max_sub_sum(int ind, int val) {
        int s = 0, t = n - 1, i = 1;
        while (true) {
            if (s == t && s == ind) {
                _make_tag(i, val);
                break;
            }
            int m = s + (t - s) / 2;
            if (ind <= m) {
                t = m;
                i = i << 1;
            } else {
                s = m+1;
                i = (i << 1) | 1;
            }
        }
        while (i > 1) {
            i /= 2;
            _push_up(i);
        }
        return cover[1];
    }
};

class Solution {
public:
    int maxSubarraySum(vector<int>& nums) {
        int n = nums.size();
        PointSetRangeMaxSubSum tree(n);
        tree.build(nums);

        unordered_map<int, vector<int>> dct;
        for (int i = 0; i < n; ++i) {
            dct[nums[i]].push_back(i);
        }

        int ans = tree.point_set_range_max_sub_sum(0, nums[0]);
        for (const auto& [x, indices] : dct) {
            if (indices.size() < n) {
                int cur = -1;
                for (int i : indices) {
                    cur = tree.point_set_range_max_sub_sum(i, 0);
                }
                if (cur > 0) {
                    ans = max(ans, cur);
                }
                for (int i : indices) {
                    tree.point_set_range_max_sub_sum(i, x);
                }
            }
        }
        return ans;
    }
};
