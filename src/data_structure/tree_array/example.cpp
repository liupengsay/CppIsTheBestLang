
#include <vector>
#include <cassert>
#include <random>
#include <iostream>
#include "template.cpp"

class TestGeneral {
public:
    static void PointAddRangeSumTest() {
        std::random_device rd;
        std::mt19937 gen(rd());

        for (int i = 0; i < 10; i++) {
            int ceil = std::uniform_int_distribution<>(10, 1000)(gen);
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
    };

public:
    static void PointAscendPreMaxTest() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> randDist(10, 1000);
        std::uniform_int_distribution<> lowDist(-1000, 0);
        std::uniform_int_distribution<> highDist(0, 10000);

        for (int initial: {std::numeric_limits<int>::min(), 0}) {
            for (int xx = 0; xx < 10; xx++) {
                int n = randDist(gen);
                int low = (initial == std::numeric_limits<int>::min()) ? -1000 : 0;
                int high = 10000;
                PointAscendPreMax treeArray(n, initial);
                std::vector<int> nums(n, initial);
                std::uniform_int_distribution<> randDistCur(low, high);
                for (int yy = 0; yy < 100; yy++) {

                    int x = randDistCur(gen);
                    int i = std::uniform_int_distribution<>(0, n - 1)(gen);

                    nums[i] = std::max(nums[i], x);
                    treeArray.pointAscend(i + 1, x);
                    std::vector<int> expected = nums;

                    std::partial_sum(expected.begin(), expected.end(), expected.begin(), [](int a, int b) {
                        return std::max(a, b);
                    });
                    std::vector<int> result(n);
                    for (int ii = 0; ii < n; ii++) {
                        result[ii] = treeArray.preMax(ii + 1);
                    }
                    assert(result == expected);
                }
            }
        }
    };

public:
    static void PointAscendRangeMaxTest() {
        std::random_device rd;
        std::mt19937 gen(rd());
        for (int initial: {std::numeric_limits<int>::min(), 0}) {
            for (int xx = 0; xx < 10; xx++) {
                int n = std::uniform_int_distribution<>(10, 1000)(gen);
                int low = (initial == std::numeric_limits<int>::min()) ? -1000 : 0;
                int high = 10000;
                PointAscendRangeMax treeArray(n, initial);
                std::vector<int> nums(n, initial);
                for (int yy = 0; yy < 100; yy++) {
                    int x = std::uniform_int_distribution<>(low, high)(gen);
                    int i = std::uniform_int_distribution<>(0, n - 1)(gen);
                    nums[i] = std::max(nums[i], x);
                    treeArray.pointAscend(i + 1, x);
                    int ll = std::uniform_int_distribution<>(0, n - 1)(gen);
                    int rr = std::uniform_int_distribution<>(ll, n - 1)(gen);
                    int expected = *std::max_element(nums.begin() + ll, nums.begin() + rr + 1);
                    int result = treeArray.rangeMax(ll + 1, rr + 1);
                    assert(result == expected);
                }
            }
        }

    }

public:
    static void PointChangeRangeSumTest() {
        std::random_device rd;
        std::mt19937 gen(rd());

        for (int xx = 0; xx < 10; xx++) {
            int ceil = std::uniform_int_distribution<>(10, 1000)(gen);
            std::vector<int> nums(ceil);
            for (int i = 0; i < ceil; i++) {
                nums[i] = std::uniform_int_distribution<>(-ceil, ceil)(gen);
            }

            PointChangeRangeSum treeArray(ceil);
            treeArray.build(nums);

            for (int _ = 0; _ < ceil; _++) {
                int d = std::uniform_int_distribution<>(-ceil, ceil)(gen);
                int i = std::uniform_int_distribution<>(0, ceil - 1)(gen);
                nums[i] = d;
                treeArray.pointChange(i + 1, d);

                int left = std::uniform_int_distribution<>(0, ceil - 1)(gen);
                int right = std::uniform_int_distribution<>(left, ceil - 1)(gen);
                int expected = 0;
                for (int j = left; j <= right; j++) {
                    expected += nums[j];
                }
                int result = treeArray.rangeSum(left + 1, right + 1);
                assert(result == expected);
                assert(nums == treeArray.get());
            }
        }
    }

public:
    static void PointDescendPreMinTest() {
        std::random_device rd;
        std::mt19937 gen(rd());

        const int inf = std::numeric_limits<int>::max();
        for (int initial: {inf, 10000}) {
            for (int xx = 0; xx < 10; xx++) {
                int n = std::uniform_int_distribution<>(10, 1000)(gen);
                int low = -10000;
                int high = 10000;

                PointDescendPreMin treeArray(n, initial);
                std::vector<int> nums(n, initial);

                for (int _ = 0; _ < 100; _++) {
                    int x = std::uniform_int_distribution<>(low, high)(gen);
                    int i = std::uniform_int_distribution<>(0, n - 1)(gen);
                    nums[i] = std::min(nums[i], x);
                    treeArray.pointDescend(i + 1, x);

                    std::vector<int> expected(n);
                    std::partial_sum(nums.begin(), nums.end(), expected.begin(), [](int a, int b) {
                        return std::min(a, b);
                    });

                    std::vector<int> result(n);
                    for (int ii = 0; ii < n; ii++) {
                        result[ii] = treeArray.preMin(ii + 1);
                    }

                    assert(result == expected);
                }
            }
        }
    }
};

int main() {
    TestGeneral::PointAddRangeSumTest();
    TestGeneral::PointAscendPreMaxTest();
    TestGeneral::PointAscendRangeMaxTest();
    TestGeneral::PointChangeRangeSumTest();
    TestGeneral::PointDescendPreMinTest();
    return 0;
};