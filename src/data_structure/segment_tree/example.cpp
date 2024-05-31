
#include <vector>
#include <cassert>
#include <random>
#include "template.cpp"


class TestGeneral {
public:
    static void RangeAddRangeSumMinMaxTest() {
        std::random_device rd;
        std::mt19937 gen(rd());
        long long low = -10000;
        long long high = 10000;


        std::vector<long long> nums(high);
        for (long long i = 0; i < high; i++) {
            nums[i] = std::uniform_long long_distribution<>(low, high)(gen);
        }

        RangeAddRangeSumMinMax segmentTree(high);
        segmentTree.build(nums);

        for (long long _ = 0; _ < high; _++) {
            long long num = std::uniform_long long_distribution<>(-high, high)(gen);
            long long left = std::uniform_long long_distribution<>(0, high - 1)(gen);
            long long right = std::uniform_long long_distribution<>(left, high - 1)(gen);

            for (long long j = left; j <= right; j++) {
                nums[j] += num;
            }
            segmentTree.rangeAdd(left, right, num);
            left = std::uniform_long long_distribution<>(0, high - 1)(gen);
            right = std::uniform_long long_distribution<>(left, high - 1)(gen);

            long long expected = *std::min_element(nums.begin() + left, nums.begin() + right + 1);
            long long result = segmentTree.rangeMin(left, right);
            assert(result == expected);

            expected = *std::max_element(nums.begin() + left, nums.begin() + right + 1);
            result = segmentTree.rangeMax(left, right);
            assert(result == expected);

            expected = std::accumulate(nums.begin() + left, nums.begin() + right + 1, 0);
            result = segmentTree.rangeSum(left, right);
            assert(result == expected);

            left = std::uniform_long long_distribution<>(0, high - 1)(gen);
            right = left;
            num = std::uniform_long long_distribution<>(-high, high)(gen);
            segmentTree.rangeAdd(left, right, num);
            for (long long j = left; j <= right; j++) {
                nums[j] += num;
            }

            expected = *std::min_element(nums.begin() + left, nums.begin() + right + 1);
            result = segmentTree.rangeMin(left, right);
            assert(result == expected);

            expected = *std::max_element(nums.begin() + left, nums.begin() + right + 1);
            result = segmentTree.rangeMax(left, right);
            assert(result == expected);

            expected = std::accumulate(nums.begin() + left, nums.begin() + right + 1, 0);
            result = segmentTree.rangeSum(left, right);
            assert(result == expected);

        }
        assert(segmentTree.get() == nums);
    }
};

int main() {
    TestGeneral::RangeAddRangeSumMinMaxTest();
    return 0;
}
