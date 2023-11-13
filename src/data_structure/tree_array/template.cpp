
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

class PointDescendRangeMin {
public:
    explicit PointDescendRangeMin(int n, int initial = std::numeric_limits<int>::max())
            : n(n), initial(initial), a(n + 1, initial), t(n + 1, initial) {}

    static int lowestBit(int x) {
        return x & -x;
    }

    static int min(int a, int b) {
        return (a < b) ? a : b;
    }

    void pointDescend(int x, int k) {
        assert(1 <= x && x <= n);
        if (a[x] <= k) {
            return;
        }
        a[x] = k;
        while (x <= n) {
            t[x] = min(t[x], k);
            x += lowestBit(x);
        }
    }

    int rangeMin(int left, int r) {
        assert(1 <= left && left <= r && r <= n);
        int minVal = initial;
        while (r >= left) {
            if (r - lowestBit(r) >= left - 1) {
                minVal = min(minVal, t[r]);
                r -= lowestBit(r);
            } else {
                minVal = min(minVal, a[r]);
                r -= 1;
            }
        }
        return minVal;
    }

private:
    int n;
    int initial;
    std::vector<int> a;
    std::vector<int> t;
};


class PointXorRangeXor {
public:
    explicit PointXorRangeXor(int n)
            : n(n), t(n + 1, 0) {}

    static int lowestBit(int i) {
        return i & (-i);
    }

    void build(const std::vector<int> &nums) {
        assert(nums.size() == n);
        std::vector<int> pre(n + 1, 0);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] ^ nums[i];
            t[i + 1] = pre[i + 1] ^ pre[i + 1 - lowestBit(i + 1)];
        }
    }

    std::vector<int> get() {
        std::vector<int> result;
        for (int i = 0; i < n; i++) {
            result.push_back(rangeXor(i + 1, i + 1));
        }
        return result;
    }

    void pointXor(int i, int val) {
        assert(1 <= i && i <= n);
        while (i <= n) {
            t[i] ^= val;
            i += lowestBit(i);
        }
    }

    int rangeXor(int x, int y) {
        assert(1 <= x && x <= y && y <= n);
        return x > 1 ? preXor(y) ^ preXor(x - 1) : preXor(y);
    }

private:
    int n;
    std::vector<int> t;

    int preXor(int i) {
        assert(1 <= i && i <= n);
        int val = 0;
        while (i) {
            val ^= t[i];
            i -= lowestBit(i);
        }
        return val;
    }

};


class RangeAddRangeSum {
public:
    explicit RangeAddRangeSum(int n)
            : n(n), t1(n + 1, 0), t2(n + 1, 0) {}

    static int lowestBit(int x) {
        return x & (-x);
    }

    void add(int k, int v) {
        int v1 = k * v;
        while (k <= n) {
            t1[k] += v;
            t2[k] += v1;
            k += lowestBit(k);
        }
    }

    static int sum(const std::vector<int> &t, int k) {
        int ret = 0;
        while (k) {
            ret += t[k];
            k -= lowestBit(k);
        }
        return ret;
    }

    void build(const std::vector<int> &nums) {
        assert(nums.size() == n);
        for (int i = 0; i < n; i++) {
            rangeAdd(i + 1, i + 1, nums[i]);
        }
    }

    std::vector<int> get() {
        std::vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            nums[i] = rangeSum(i + 1, i + 1);
        }
        return nums;
    }

    void rangeAdd(int left, int right, int v) {
        add(left, v);
        add(right + 1, -v);
    }

    int rangeSum(int left, int right) {
        int a = (right + 1) * sum(t1, right) - sum(t2, right);
        int b = left * sum(t1, left - 1) - sum(t2, left - 1);
        return a - b;
    }

private:
    int n;
    std::vector<int> t1;
    std::vector<int> t2;
};

class PointAddRangeSum2D {
public:
    explicit PointAddRangeSum2D(int m, int n)
            : m(m), n(n), tree(m + 1, std::vector<int>(n + 1, 0)) {}

    void pointAdd(int x, int y, int val) {
        int i = x;
        while (i <= m) {
            int j = y;
            while (j <= n) {
                tree[i][j] += val;
                j += (j & -j);
            }
            i += (i & -i);
        }
    }

    int query(int x, int y) {
        int res = 0;
        int i = x;
        while (i > 0) {
            int j = y;
            while (j > 0) {
                res += tree[i][j];
                j -= (j & -j);
            }
            i -= (i & -i);
        }
        return res;
    }

    int rangeSum(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
    }

private:
    int m;
    int n;
    std::vector<std::vector<int>> tree;
};


class RangeAddRangeSum2D {
public:
    explicit RangeAddRangeSum2D(int m, int n) : m(m), n(n), t1(m + 1, std::vector<int>(n + 1)),
                                                t2(m + 1, std::vector<int>(n + 1)),
                                                t3(m + 1, std::vector<int>(n + 1)),
                                                t4(m + 1, std::vector<int>(n + 1)) {}


    void rangeAdd(int x1, int y1, int x2, int y2, int val) {
        add(x1, y1, val);
        add(x1, y2 + 1, -val);
        add(x2 + 1, y1, -val);
        add(x2 + 1, y2 + 1, val);
    }


    int rangeQuery(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
    }

private:
    int m;
    int n;
    std::vector<std::vector<int>> t1;
    std::vector<std::vector<int>> t2;
    std::vector<std::vector<int>> t3;
    std::vector<std::vector<int>> t4;

    void add(int x, int y, int val) {
        int i = x;
        while (i <= m) {
            int j = y;
            while (j <= n) {
                t1[i][j] += val;
                t2[i][j] += val * x;
                t3[i][j] += val * y;
                t4[i][j] += val * x * y;
                j += (j & -j);
            }
            i += (i & -i);
        }
    }

    int query(int x, int y) {
        assert(0 <= x && x <= m && 0 <= y && y <= n);
        int res = 0;
        int i = x;
        while (i > 0) {
            int j = y;
            while (j > 0) {
                res += (x + 1) * (y + 1) * t1[i][j] - (y + 1) * t2[i][j] - (x + 1) * t3[i][j] + t4[i][j];
                j -= (j & -j);
            }
            i -= (i & -i);
        }
        return res;
    }

};