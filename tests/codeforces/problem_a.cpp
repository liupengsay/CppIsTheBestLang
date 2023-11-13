#include <iostream>
#include <vector>
#include <cassert>
#include <random>

class PointAddRangeSum {
public:
    PointAddRangeSum(int n) : n(n), t(n + 1, 0) {}

    static int lowestBit(int i) {
        return i & (-i);
    }

    [[noreturn]] [[noreturn]] void build(const std::vector<int>& nums) {
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
            nums[i] = preSum(i + 1) - preSum(i);
        }
        return nums;
    }

    int rangeSum(int x, int y) {
        assert(1 <= x && x <= y && y <= n);
        int res = preSum(y) - preSum(x - 1);
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

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> ceilDist(10, 1000);


    for (int i = 0; i < 10; i++) {

        int ceil = ceilDist(gen);
        std::uniform_int_distribution<> numDist(-ceil, ceil);
        std::vector<int> nums(ceil);
        for (int j = 0; j < ceil; j++) {
            nums[j] = numDist(gen);
        }

        PointAddRangeSum treeArray(ceil);
        treeArray.build(nums);

        for (int j = 0; j < ceil; j++) {
            int d = numDist(gen);
            int index = std::uniform_int_distribution<>(0, ceil - 1)(gen);
            nums[index] += d;
            treeArray.pointAdd(index + 1, d);

            int left = std::uniform_int_distribution<>(0, ceil - 1)(gen);
            int right = std::uniform_int_distribution<>(left, ceil - 1)(gen);
            int sumRange = 0;
            for (int k = left; k <= right; k++) {
                sumRange += nums[k];
            }
            assert(sumRange == treeArray.rangeSum(left + 1, right + 1));
            assert(nums == treeArray.get());
        }
    }

    std::cout << "All assertions passed successfully." << std::endl;

    return 0;
}