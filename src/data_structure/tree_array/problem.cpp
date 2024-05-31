#include <vector>
#include <algorithm>
#include "template.cpp"
#include <map>


class Solution {
public:
    static long long lc_2659(std::vector<long long> &nums) {
        long long n = nums.size();
        long long ans = 0;
        long long pre = 1;
        std::map<long long, long long> dct;
        PointAddRangeSum tree(n);

        for (long long i = 0; i < n; i++) {
            dct[nums[i]] = i + 1;
        }

        std::vector<long long> sorted_nums = nums;
        std::sort(sorted_nums.begin(), sorted_nums.end());

        for (long long num: sorted_nums) {
            long long i = dct[num];
            if (pre <= i) {
                ans += i - pre + 1 - tree.rangeSum(pre, i);
            } else {
                ans += n - pre + 1 - tree.rangeSum(pre, n) + i - 1 + 1 - tree.rangeSum(1, i);
            }
            tree.PointAdd(i, 1);
            pre = i;
        }

        return ans;
    }
};