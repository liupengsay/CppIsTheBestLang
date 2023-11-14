#include <vector>
#include <algorithm>
#include "template.cpp"
#include <map>


class Solution {
public:
    static long long lc_2659(std::vector<int> &nums) {
        int n = nums.size();
        long long ans = 0;
        int pre = 1;
        std::map<int, int> dct;
        PointAddRangeSum tree(n);

        for (int i = 0; i < n; i++) {
            dct[nums[i]] = i + 1;
        }

        std::vector<int> sorted_nums = nums;
        std::sort(sorted_nums.begin(), sorted_nums.end());

        for (int num: sorted_nums) {
            int i = dct[num];
            if (pre <= i) {
                ans += i - pre + 1 - tree.rangeSum(pre, i);
            } else {
                ans += n - pre + 1 - tree.rangeSum(pre, n) + i - 1 + 1 - tree.rangeSum(1, i);
            }
            tree.pointAdd(i, 1);
            pre = i;
        }

        return ans;
    }
};