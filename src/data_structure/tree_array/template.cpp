
#include <vector>
#include <cassert>
#include <limits>
#include <algorithm>


class PointAddRangeSum {
public:
    explicit PointAddRangeSum(int n) : n(n), t(n + 1, 0) {}

    static int lowestBit(int i) {
        return i & (-i);
    }

    [[noreturn]] void build(const std::vector<int> &nums) {
        assert(nums.size() == n);
        std::vector<int> pre(n + 1, 0);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] + nums[i];
            t[i + 1] = pre[i + 1] - pre[i + 1 - lowestBit(i + 1)];
        }
    }

    void pointAdd(int i, int mi) {
        assert(1 <= i && i <= n);
        while (i < t.size()) {
            t[i] += mi;
            i += lowestBit(i);
        }
    }

    std::vector<int> get() {
        std::vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            nums[i] = preSum(i + 1);
        }
        for (int i = n - 1; i > 0; i--) {
            nums[i] -= nums[i - 1];
        }
        return nums;
    }

    int rangeSum(int x, int y) {
        assert(1 <= x && x <= y && y <= n);
        int res = x > 1 ? preSum(y) - preSum(x - 1) : preSum(y);
        return res;
    }

private:
    int n;
    std::vector<int> t;

    int preSum(int i) {
        assert(1 <= i && i <= n);
        int mi = 0;
        while (i > 0) {
            mi += t[i];
            i -= lowestBit(i);
        }
        return mi;
    }
};


class PointAscendPreMax {
public:
    explicit PointAscendPreMax(int n, int initial = std::numeric_limits<int>::min())
            : n(n), initial(initial), t(n + 1, initial) {}

    static int lowestBit(int i) {
        return i & (-i);
    }

    int preMax(int i) {
        assert(1 <= i && i <= n);
        int mx = initial;
        while (i) {
            mx = std::max(mx, t[i]);
            i -= lowestBit(i);
        }
        return mx;
    }

    void pointAscend(int i, int mx) {
        assert(1 <= i && i <= n);
        while (i < t.size()) {
            t[i] = std::max(t[i], mx);
            i += lowestBit(i);
        }
    }

private:
    int n;
    int initial;
    std::vector<int> t;
};


class PointAscendRangeMax {
public:
    explicit PointAscendRangeMax(int n, int initial = std::numeric_limits<int>::min())
            : n(n), initial(initial), a(n + 1, initial), t(n + 1, initial) {}

    static int lowestBit(int x) {
        return x & -x;
    }

    static int max(int a, int b) {
        return (a > b) ? a : b;
    }

    void pointAscend(int x, int k) {
        assert(1 <= x && x <= n);
        if (a[x] >= k) {
            return;
        }
        a[x] = k;
        while (x <= n) {
            t[x] = max(t[x], k);
            x += lowestBit(x);
        }
    }

    int rangeMax(int left, int r) {
        assert(1 <= left && left <= r && r <= n);
        int maxVal = initial;
        while (r >= left) {
            if (r - lowestBit(r) >= left - 1) {
                maxVal = max(maxVal, t[r]);
                r -= lowestBit(r);
            } else {
                maxVal = max(maxVal, a[r]);
                r -= 1;
            }
        }
        return maxVal;
    }

private:
    int n;
    int initial;
    std::vector<int> a;
    std::vector<int> t;
};

class PointChangeRangeSum {
public:
    explicit PointChangeRangeSum(int n) : n(n), t(n + 1, 0) {}

    static int lowestBit(int i) {
        return i & (-i);
    }

    void build(const std::vector<int> &nums) {
        assert(nums.size() == n);
        std::vector<int> pre(n + 1, 0);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] + nums[i];
            t[i + 1] = pre[i + 1] - pre[i + 1 - lowestBit(i + 1)];
        }
    }

    void pointChange(int i, int val) {
        assert(1 <= i && i <= n);
        int pre = rangeSum(i, i);
        int gap = val - pre;
        if (gap != 0) {
            while (i < t.size()) {
                t[i] += gap;
                i += lowestBit(i);
            }
        }
    }

    std::vector<int> get() {
        std::vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            nums[i] = preSum(i + 1);
        }
        for (int i = n - 1; i > 0; i--) {
            nums[i] -= nums[i - 1];
        }
        return nums;
    }


    int rangeSum(int x, int y) {
        assert(1 <= x && x <= y && y <= n);
        int res = x > 1 ? preSum(y) - preSum(x - 1) : preSum(y);
        return res;
    }

private:
    int n;
    std::vector<int> t;

    int preSum(int i) {
        assert(1 <= i && i <= n);
        int val = 0;
        while (i > 0) {
            val += t[i];
            i -= lowestBit(i);
        }
        return val;
    }
};


class PointDescendPreMin {
public:
    explicit PointDescendPreMin(int n, int initial = std::numeric_limits<int>::max())
            : n(n), initial(initial), t(n + 1, initial) {}

    static int lowestBit(int i) {
        return i & (-i);
    }

    int preMin(int i) {
        assert(1 <= i && i <= n);
        int val = initial;
        while (i > 0) {
            val = std::min(val, t[i]);
            i -= lowestBit(i);
        }
        return val;
    }

    void pointDescend(int i, int val) {
        assert(1 <= i && i <= n);
        while (i < t.size()) {
            t[i] = std::min(t[i], val);
            i += lowestBit(i);
        }
    }

private:
    int n;
    int initial;
    std::vector<int> t;
};