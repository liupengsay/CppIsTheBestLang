
#include <vector>
#include <cassert>
#include <random>
#include "template.cpp"


class TestGeneral {
public:
    static void RangeAddRangeSumMinMaxTest() {
        std::random_device rd;
        std::mt19937 gen(rd());
        int low = -10000;
        int high = 10000;


        std::vector<int> nums(high);
        for (int i = 0; i < high; i++) {
            nums[i] = std::uniform_int_distribution<>(low, high)(gen);
        }

        RangeAddRangeSumMinMax segmentTree(high);
        segmentTree.build(nums);

        for (int _ = 0; _ < high; _++) {
            int num = std::uniform_int_distribution<>(-high, high)(gen);
            int left = std::uniform_int_distribution<>(0, high - 1)(gen);
            int right = std::uniform_int_distribution<>(left, high - 1)(gen);

            for (int j = left; j <= right; j++) {
                nums[j] += num;
            }
            segmentTree.rangeAdd(left, right, num);
            left = std::uniform_int_distribution<>(0, high - 1)(gen);
            right = std::uniform_int_distribution<>(left, high - 1)(gen);

            int expected = *std::min_element(nums.begin() + left, nums.begin() + right + 1);
            int result = segmentTree.rangeMin(left, right);
            assert(result == expected);

            expected = *std::max_element(nums.begin() + left, nums.begin() + right + 1);
            result = segmentTree.rangeMax(left, right);
            assert(result == expected);

            expected = std::accumulate(nums.begin() + left, nums.begin() + right + 1, 0);
            result = segmentTree.rangeSum(left, right);
            assert(result == expected);

            left = std::uniform_int_distribution<>(0, high - 1)(gen);
            right = left;
            num = std::uniform_int_distribution<>(-high, high)(gen);
            segmentTree.rangeAdd(left, right, num);
            for (int j = left; j <= right; j++) {
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
