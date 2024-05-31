#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class RangeAddRangeSumMinMax {
private:
    long long n;
    std::vector<long long> cover;
    std::vector<long long> lazy;
    std::vector<long long> floor;
    std::vector<long long> ceil;

    void pushUp(long long i) {
        cover[i] = cover[2 * i] + cover[2 * i + 1];
        ceil[i] = std::max(ceil[2 * i], ceil[2 * i + 1]);
        floor[i] = std::min(floor[2 * i], floor[2 * i + 1]);
    }

    void makeTag(long long i, long long s, long long t, long long val) {
        cover[i] += val * (t - s + 1);
        floor[i] += val;
        ceil[i] += val;
        lazy[i] += val;
    }

    void pushDown(long long i, long long s, long long m, long long t) {
        if (lazy[i] != 0) {
            cover[2 * i] += lazy[i] * (m - s + 1);
            cover[2 * i + 1] += lazy[i] * (t - m);

            floor[2 * i] += lazy[i];
            floor[2 * i + 1] += lazy[i];

            ceil[2 * i] += lazy[i];
            ceil[2 * i + 1] += lazy[i];

            lazy[2 * i] += lazy[i];
            lazy[2 * i + 1] += lazy[i];

            lazy[i] = 0;
        }

    }

public:
    explicit RangeAddRangeSumMinMax(long long n) : n(n), cover(4 * n, 0), lazy(4 * n, 0), floor(4 * n, 0), ceil(4 * n, 0) {}

    void build(const std::vector<long long> &nums) {
        assert(n == nums.size());
        std::vector<std::vector<long long>> stack;
        stack.push_back({0, n - 1, 1});
        while (!stack.empty()) {
            std::vector<long long> last = stack.back();
            stack.pop_back();
            long long s = last[0];
            long long t = last[1];
            long long ind = last[2];
            if (ind >= 0) {
                if (s == t) {
                    makeTag(ind, s, t, nums[s]);
                } else {
                    stack.push_back({s, t, ~ind});
                    long long m = s + (t - s) / 2;
                    stack.push_back({s, m, 2 * ind});
                    stack.push_back({m + 1, t, 2 * ind + 1});
                }
            } else {
                ind = ~ind;
                pushUp(ind);
            }
        }
    }

    long long rangeAdd(long long left, long long right, long long val) {
        assert(0 <= left && left <= right && right <= n - 1);
        std::vector<std::vector<long long>> stack;
        stack.push_back({0, n - 1, 1});
        long long ans = 0;
        while (!stack.empty()) {
            std::vector<long long> last = stack.back();
            stack.pop_back();
            long long s = last[0];
            long long t = last[1];
            long long i = last[2];
            if (i > 0) {
                if (left <= s && t <= right) {
                    makeTag(i, s, t, val);
                    continue;
                }
                long long m = s + (t - s) / 2;
                pushDown(i, s, m, t);
                stack.push_back({s, t, ~i});
                if (left <= m) {
                    stack.push_back({s, m, 2 * i});
                }
                if (right > m) {
                    stack.push_back({m + 1, t, 2 * i + 1});
                }
            } else {
                i = ~i;
                pushUp(i);
            }

        }
        return ans;
    }

    long long rangeSum(long long left, long long right) {
        std::vector<std::vector<long long>> stack;
        stack.push_back({0, n - 1, 1});
        long long ans = 0;
        while (!stack.empty()) {
            std::vector<long long> last = stack.back();
            stack.pop_back();
            long long s = last[0];
            long long t = last[1];
            long long i = last[2];
            if (left <= s && t <= right) {
                ans += cover[i];
                continue;
            }
            long long m = s + (t - s) / 2;
            pushDown(i, s, m, t);
            if (left <= m) {
                stack.push_back({s, m, 2 * i});
            }
            if (right > m) {
                stack.push_back({m + 1, t, 2 * i + 1});
            }
        }
        return ans;
    }

    long long rangeMin(long long left, long long right) {
        std::vector<std::vector<long long>> stack;
        stack.push_back({0, n - 1, 1});
        long long lowest = std::numeric_limits<long long>::max();
        while (!stack.empty()) {
            std::vector<long long> last = stack.back();
            stack.pop_back();
            long long s = last[0];
            long long t = last[1];
            long long i = last[2];
            if (left <= s && t <= right) {
                lowest = std::min(lowest, floor[i]);
                continue;
            }
            long long m = s + (t - s) / 2;
            pushDown(i, s, m, t);
            if (left <= m) {
                stack.push_back({s, m, 2 * i});
            }
            if (right > m) {
                stack.push_back({m + 1, t, 2 * i + 1});
            }
        }
        return lowest;
    }

    long long rangeMax(long long left, long long right) {
        std::vector<std::vector<long long>> stack;
        stack.push_back({0, n - 1, 1});
        long long highest = std::numeric_limits<long long>::min();
        while (!stack.empty()) {
            std::vector<long long> last = stack.back();
            stack.pop_back();
            long long s = last[0];
            long long t = last[1];
            long long i = last[2];
            if (left <= s && t <= right) {
                highest = std::max(highest, ceil[i]);
                continue;
            }
            long long m = s + (t - s) / 2;
            pushDown(i, s, m, t);
            if (left <= m) {
                stack.push_back({s, m, 2 * i});
            }
            if (right > m) {
                stack.push_back({m + 1, t, 2 * i + 1});
            }
        }
        return highest;
    }

    std::vector<long long> get() {
        std::vector<std::vector<long long>> stack;
        stack.push_back({0, n - 1, 1});
        std::vector<long long> nums(n);
        while (!stack.empty()) {
            std::vector<long long> last = stack.back();
            stack.pop_back();
            long long s = last[0];
            int t = last[1];
            int i = last[2];
            if (s == t) {
                nums[s] = cover[i];
                continue;
            }
            int m = s + (t - s) / 2;
            pushDown(i, s, m, t);
            stack.push_back({s, m, 2 * i});
            stack.push_back({m + 1, t, 2 * i + 1});
        }
        return nums;
    }


};

class PointSetRangeMaxSubSumAlter {
public:
    PointSetRangeMaxSubSumAlter(long long n, long long initial = INF) : n(n), initial(initial) {
        cover.assign(4 * n, 0);
        val.assign(4 * n, vector<long long>(4, 0));
    }

    void build(const vector<int>& nums) {
        vector<vector<long long>> stack = {{0, n - 1, 1}};
        while (!stack.empty()) {
            vector<long long> p =  stack.back();
            long long s = p[0];
            long long t = p[1];
            long long i = p[2];
            stack.pop_back();
            if (i >= 0) {
                if (s == t) {
                    _make_tag(i, nums[s]);
                    continue;
                }
                stack.push_back({s, t, ~i});
                long long m = s + (t - s) / 2;
                stack.push_back({s, m, i * 2});
                stack.push_back({m + 1, t, i * 2 + 1});
            } else {
                i = ~i;
                _push_up(i);
            }
        }
    }

    long long point_set_range_max_sub_sum(long long ind, long long val) {
        long long s = 0, t = n - 1, i = 1;
        while (true) {
            if (s == t && s == ind) {
                _make_tag(i, val);
                break;
            }
            long long m = s + (t - s) / 2;
            if (ind <= m) {
                t = m;
                i *= 2;
            } else {
                s = m + 1;
                i = i * 2 + 1;
            }
        }
        while (i > 1) {
            i /= 2;
            _push_up(i);
        }
        return cover[1];
    }

private:
    long long n, initial;
    vector<long long> cover;
    vector<vector<long long>> val;
    vector<string> map;
    vector<vector<long long>> index = {{0, 0, 0}, {0, 1, 1}, {0, 2, 0}, {0, 3, 1}, {1, 0, 0}, {1, 1, 1}, {2, 0, 2}, {2, 1, 3}, {2, 2, 2}, {2, 3, 3}, {3, 0, 2}, {3, 1, 3}};

    void _make_tag(long long i, long long val) {
        cover[i] = val;
        this->val[i][3] = val;
    }

    void _push_up(long long i) {
        cover[i] = max(cover[i * 2], cover[i * 2 + 1]);
        for (long long j = 0; j < 4; ++j) {
            val[i][j] = max(val[i * 2][j], val[i * 2 + 1][j]);
        }
        for (const auto& p: index) {
            long long x = p[0];
            long long y = p[1];
            long long k = p[2];
            val[i][k] = max(val[i][k], val[i * 2][x] + val[i * 2 + 1][y]);
            cover[i] = max(cover[i], val[i][k]);
        }
    }
};