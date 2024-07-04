#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>

class FastIO {
public:
    long long read_int() {
        long long x;
        std::cin >> x;
        return x;
    }

    std::vector<long long> read_list_ints(long long n) {
        std::vector<long long> v(n);
        for (long long i = 0; i < n; ++i) {
            std::cin >> v[i];
        }
        return v;
    }

    void st(long long ans) {
        std::cout << ans << "\n";
    }
};

class TernarySearch {
public:
    static long long find_floor_point_int(const auto& fun, long long left, long long right, long long error = 1) {
        while (left < right - error) {
            long long diff = (right - left) / 3;
            long long mid1 = left + diff;
            long long mid2 = left + 2 * diff;
            long long dist1 = fun(mid1);
            long long dist2 = fun(mid2);
            if (dist1 < dist2) {
                right = mid2;
            } else if (dist1 > dist2) {
                left = mid1;
            } else {
                left = mid1;
                right = mid2;
            }
        }
        return left;
    }
};

class Solution {
public:
    void main() {
        FastIO ac;
        long long n = ac.read_int();
        long long a = ac.read_int();
        long long r = ac.read_int();
        long long m = ac.read_int();
        std::vector<long long> h = ac.read_list_ints(n);

        std::sort(h.begin(), h.end());
        std::vector<long long> pre(n + 1, 0);
        std::partial_sum(h.begin(), h.end(), pre.begin() + 1);

        auto check = [&](long long x) -> long long {
            long long i = std::lower_bound(h.begin(), h.end(), x) - h.begin();
            long long low = (long long)x * i - pre[i];
            long long high = pre[n] - pre[i] - (long long)(n - i) * x;
            long long y = std::min(low, high);
            long long res = y * std::min(m, a + r);
            res += (low - y) * a + (high - y) * r;
            return res;
        };

        long long mid = TernarySearch::find_floor_point_int(check, 0, *std::max_element(h.begin(), h.end()));
        long long ans = LLONG_MAX;
        for (long long x = mid - 5; x <= mid + 5; ++x) {
            if (x >= 0) {
                ans = std::min(ans, check(x));
            }
        }
        ac.st(ans);
    }
};

int main() {
    Solution().main();
    return 0;
}
