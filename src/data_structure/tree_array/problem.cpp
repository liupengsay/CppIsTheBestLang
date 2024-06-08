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

class BinaryIndexedTree {
private:
    vector<int> tree;

public:
    BinaryIndexedTree(int n) : tree(n + 1) {}

    void add(int i) {
        while (i < tree.size()) {
            tree[i] += 1;
            i += i & -i;
        }
    }

    int get(int i) {
        int res = 0;
        while (i > 0) {
            res += tree[i];
            i &= i - 1;
        }
        return res;
    }
};

class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> sortedNums = nums;
        sort(sortedNums.begin(), sortedNums.end());
        unordered_map<int, int> index;
        for (int i = 0; i < n; ++i) {
            index[sortedNums[i]] = i + 1;
        }

        vector<int> arr1 = {nums[0]};
        vector<int> arr2 = {nums[1]};
        BinaryIndexedTree tree1(n), tree2(n);
        tree1.add(index[nums[0]]);
        tree2.add(index[nums[1]]);

        for (int i = 2; i < n; ++i) {
            int count1 = arr1.size() - tree1.get(index[nums[i]]);
            int count2 = arr2.size() - tree2.get(index[nums[i]]);
            if (count1 > count2 || (count1 == count2 && arr1.size() <= arr2.size())) {
                arr1.push_back(nums[i]);
                tree1.add(index[nums[i]]);
            } else {
                arr2.push_back(nums[i]);
                tree2.add(index[nums[i]]);
            }
        }

        arr1.insert(arr1.end(), arr2.begin(), arr2.end());
        return arr1;
    }
};

// 作者：力扣官方题解
// 链接：https://leetcode.cn/problems/distribute-elements-into-two-arrays-ii/solutions/2796537/jiang-yuan-su-fen-pei-dao-liang-ge-shu-z-d5mh/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。