#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cassert>


class RangeAddRangeSumMinMax {
private:
    int n;
    std::vector<int> cover;
    std::vector<int> lazy;
    std::vector<int> floor;
    std::vector<int> ceil;

    void pushUp(int i) {
        cover[i] = cover[2 * i] + cover[2 * i + 1];
        ceil[i] = std::max(ceil[2 * i], ceil[2 * i + 1]);
        floor[i] = std::min(floor[2 * i], floor[2 * i + 1]);
    }

    void makeTag(int i, int s, int t, int val) {
        cover[i] += val * (t - s + 1);
        floor[i] += val;
        ceil[i] += val;
        lazy[i] += val;
    }

    void pushDown(int i, int s, int m, int t) {
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
    explicit RangeAddRangeSumMinMax(int n) : n(n), cover(4 * n, 0), lazy(4 * n, 0), floor(4 * n, 0), ceil(4 * n, 0) {}

    void build(const std::vector<int> &nums) {
        assert(n == nums.size());
        std::vector<std::vector<int>> stack;
        stack.push_back({0, n - 1, 1});
        while (!stack.empty()) {
            std::vector<int> last = stack.back();
            stack.pop_back();
            int s = last[0];
            int t = last[1];
            int ind = last[2];
            if (ind >= 0) {
                if (s == t) {
                    makeTag(ind, s, t, nums[s]);
                } else {
                    stack.push_back({s, t, ~ind});
                    int m = s + (t - s) / 2;
                    stack.push_back({s, m, 2 * ind});
                    stack.push_back({m + 1, t, 2 * ind + 1});
                }
            } else {
                ind = ~ind;
                pushUp(ind);
            }
        }
    }

    int rangeAdd(int left, int right, int val) {
        assert(0 <= left && left <= right && right <= n - 1);
        std::vector<std::vector<int>> stack;
        stack.push_back({0, n - 1, 1});
        int ans = 0;
        while (!stack.empty()) {
            std::vector<int> last = stack.back();
            stack.pop_back();
            int s = last[0];
            int t = last[1];
            int i = last[2];
            if (i > 0) {
                if (left <= s && t <= right) {
                    makeTag(i, s, t, val);
                    continue;
                }
                int m = s + (t - s) / 2;
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

    int rangeSum(int left, int right) {
        std::vector<std::vector<int>> stack;
        stack.push_back({0, n - 1, 1});
        int ans = 0;
        while (!stack.empty()) {
            std::vector<int> last = stack.back();
            stack.pop_back();
            int s = last[0];
            int t = last[1];
            int i = last[2];
            if (left <= s && t <= right) {
                ans += cover[i];
                continue;
            }
            int m = s + (t - s) / 2;
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

    int rangeMin(int left, int right) {
        std::vector<std::vector<int>> stack;
        stack.push_back({0, n - 1, 1});
        int lowest = std::numeric_limits<int>::max();
        while (!stack.empty()) {
            std::vector<int> last = stack.back();
            stack.pop_back();
            int s = last[0];
            int t = last[1];
            int i = last[2];
            if (left <= s && t <= right) {
                lowest = std::min(lowest, floor[i]);
                continue;
            }
            int m = s + (t - s) / 2;
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

    int rangeMax(int left, int right) {
        std::vector<std::vector<int>> stack;
        stack.push_back({0, n - 1, 1});
        int highest = std::numeric_limits<int>::min();
        while (!stack.empty()) {
            std::vector<int> last = stack.back();
            stack.pop_back();
            int s = last[0];
            int t = last[1];
            int i = last[2];
            if (left <= s && t <= right) {
                highest = std::max(highest, ceil[i]);
                continue;
            }
            int m = s + (t - s) / 2;
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

    std::vector<int> get() {
        std::vector<std::vector<int>> stack;
        stack.push_back({0, n - 1, 1});
        std::vector<int> nums(n);
        while (!stack.empty()) {
            std::vector<int> last = stack.back();
            stack.pop_back();
            int s = last[0];
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