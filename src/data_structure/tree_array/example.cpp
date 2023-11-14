
#include <vector>
#include <cassert>
#include <random>
#include <iostream>
#include "problem.cpp"

class TestGeneral {
public:
    static void PointAddRangeSumTest() {

        std::random_device rd;
        std::mt19937 gen(rd());

        for (int xx = 0; xx < 100; xx++) {
            int ceil = std::uniform_int_distribution<int>(10, 1000)(gen);
            std::vector<int> nums(ceil);
            std::generate(nums.begin(), nums.end(),
                          [&]() { return std::uniform_int_distribution<int>(-ceil, ceil)(gen); });

            PointAddRangeSum tree_array(ceil);
            tree_array.build(nums);

            for (int _ = 0; _ < ceil; ++_) {
                int d = std::uniform_int_distribution<int>(-ceil, ceil)(gen);
                int i = std::uniform_int_distribution<int>(0, ceil - 1)(gen);
                nums[i] += d;
                tree_array.pointAdd(i + 1, d);

                int left = std::uniform_int_distribution<int>(0, ceil - 1)(gen);
                int right = std::uniform_int_distribution<int>(left, ceil - 1)(gen);

                int expected_sum = std::accumulate(nums.begin() + left, nums.begin() + right + 1, 0);
                int range_sum = tree_array.rangeSum(left + 1, right + 1);

                assert(expected_sum == range_sum);
                assert(nums == tree_array.get());
            }
        }
    }

    static void PointAscendPreMaxTest() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> randDist(10, 1000);
        std::uniform_int_distribution<> lowDist(-1000, 0);
        std::uniform_int_distribution<> highDist(0, 10000);

        for (int initial: {std::numeric_limits<int>::min(), 0}) {
            for (int xx = 0; xx < 100; xx++) {
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
    }

    static void PointAscendRangeMaxTest() {
        std::random_device rd;
        std::mt19937 gen(rd());
        for (int initial: {std::numeric_limits<int>::min(), 0}) {
            for (int xx = 0; xx < 100; xx++) {
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

    static void PointChangeRangeSumTest() {
        std::random_device rd;
        std::mt19937 gen(rd());

        for (int xx = 0; xx < 100; xx++) {
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

    static void PointDescendPreMinTest() {
        std::random_device rd;
        std::mt19937 gen(rd());

        const int inf = std::numeric_limits<int>::max();
        for (int initial: {inf, 10000}) {
            for (int xx = 0; xx < 100; xx++) {
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

    static void PointDescendRangeMinTest() {
        std::random_device rd;
        std::mt19937 gen(rd());

        const int inf = std::numeric_limits<int>::max();
        for (int initial: {inf, 10000}) {
            for (int xx = 0; xx < 100; xx++) {
                int n = std::uniform_int_distribution<>(10, 1000)(gen);
                int low = -10000;
                int high = 10000;

                PointDescendRangeMin treeArray(n, initial);
                std::vector<int> nums(n, initial);

                for (int _ = 0; _ < 100; _++) {
                    int x = std::uniform_int_distribution<>(low, high)(gen);
                    int i = std::uniform_int_distribution<>(0, n - 1)(gen);
                    nums[i] = std::min(nums[i], x);
                    treeArray.pointDescend(i + 1, x);

                    int ll = std::uniform_int_distribution<>(0, n - 1)(gen);
                    int rr = std::uniform_int_distribution<>(ll, n - 1)(gen);
                    int expected = *std::min_element(nums.begin() + ll, nums.begin() + rr + 1);
                    int result = treeArray.rangeMin(ll + 1, rr + 1);
                    assert(result == expected);
                }
            }
        }
    }

    static void PointXorRangeXorTest() {
        std::random_device rd;
        std::mt19937 gen(rd());

        for (int xx = 0; xx < 100; xx++) {
            int n = std::uniform_int_distribution<>(10, 1000)(gen);
            int low = -10000;
            int high = 10000;
            std::vector<int> nums(n);
            for (int i = 0; i < n; i++) {
                nums[i] = std::uniform_int_distribution<>(low, high)(gen);
            }

            PointXorRangeXor treeArray(n);
            treeArray.build(nums);

            for (int _ = 0; _ < 100; _++) {
                int x = std::uniform_int_distribution<>(low, high)(gen);
                int i = std::uniform_int_distribution<>(0, n - 1)(gen);
                nums[i] ^= x;
                treeArray.pointXor(i + 1, x);
                assert(treeArray.get() == nums);

                int ll = std::uniform_int_distribution<>(0, n - 1)(gen);
                int rr = std::uniform_int_distribution<>(ll, n - 1)(gen);
                int res = 0;
                for (int j = ll; j <= rr; j++) {
                    res ^= nums[j];
                }
                assert(res == treeArray.rangeXor(ll + 1, rr + 1));
            }
        }
    }

    static void RangeAddRangeSumTest() {
        std::random_device rd;
        std::mt19937 gen(rd());

        for (int xx = 0; xx < 100; xx++) {
            for (int yy = 0; yy < 10; yy++) {
                int n = std::uniform_int_distribution<>(10, 1000)(gen);
                std::vector<int> nums(n);
                for (int i = 0; i < n; i++) {
                    nums[i] = std::uniform_int_distribution<>(-10000, 10000)(gen);
                }

                RangeAddRangeSum treeArray(n);
                treeArray.build(nums);

                for (int _ = 0; _ < 10; _++) {
                    int x = std::uniform_int_distribution<>(-10000, 10000)(gen);
                    int ll = std::uniform_int_distribution<>(0, n - 1)(gen);
                    int rr = std::uniform_int_distribution<>(ll, n - 1)(gen);

                    for (int j = ll; j <= rr; j++) {
                        nums[j] += x;
                    }
                    treeArray.rangeAdd(ll + 1, rr + 1, x);
                    assert(treeArray.get() == nums);

                    ll = std::uniform_int_distribution<>(0, n - 1)(gen);
                    rr = std::uniform_int_distribution<>(ll, n - 1)(gen);
                    assert(treeArray.rangeSum(ll + 1, rr + 1) ==
                           std::accumulate(nums.begin() + ll, nums.begin() + rr + 1, 0));
                }
            }
        }
    }

    static void PointAddRangeSum2DTest() {
        std::random_device rd;
        std::mt19937 gen(rd());

        int m = 100;
        int n = 100;
        int high = 100000;

        PointAddRangeSum2D tree(m, n);
        std::vector<std::vector<int>> grid(m, std::vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                grid[i][j] = std::uniform_int_distribution<>(-high, high)(gen);
                tree.pointAdd(i + 1, j + 1, grid[i][j]);
            }
        }

        for (int _ = 0; _ < m; _++) {
            int row = std::uniform_int_distribution<>(0, m - 1)(gen);
            int col = std::uniform_int_distribution<>(0, n - 1)(gen);
            int x = std::uniform_int_distribution<>(-high, high)(gen);
            grid[row][col] += x;
            tree.pointAdd(row + 1, col + 1, x);

            int x1 = std::uniform_int_distribution<>(0, m - 1)(gen);
            int y1 = std::uniform_int_distribution<>(0, n - 1)(gen);
            int x2 = std::uniform_int_distribution<>(x1, m - 1)(gen);
            int y2 = std::uniform_int_distribution<>(y1, n - 1)(gen);

            int sum = 0;
            for (int i = x1; i <= x2; i++) {
                for (int j = y1; j <= y2; j++) {
                    sum += grid[i][j];
                }
            }

            assert(tree.rangeSum(x1 + 1, y1 + 1, x2 + 1, y2 + 1) == sum);
        }
    }

    static void RangeAddRangeSum2DTest() {
        int m = 100;
        int n = 100;
        int high = 100000;
        RangeAddRangeSum2D tree(m, n);
        std::vector<std::vector<int>> grid(m, std::vector<int>(n));

        std::random_device rd;
        std::mt19937 gen(rd());

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = std::uniform_int_distribution<int>(-high, high)(gen);
                tree.rangeAdd(i + 1, j + 1, i + 1, j + 1, grid[i][j]);
            }
        }

        for (int i = 0; i < m; ++i) {
            int x1 = std::uniform_int_distribution<int>(0, m - 1)(gen);
            int y1 = std::uniform_int_distribution<int>(0, n - 1)(gen);
            int x2 = std::uniform_int_distribution<int>(x1, m - 1)(gen);
            int y2 = std::uniform_int_distribution<int>(y1, n - 1)(gen);
            int x = std::uniform_int_distribution<int>(-high, high)(gen);

            for (int row = x1; row <= x2; row++) {
                for (int col = y1; col <= y2; col++) {
                    grid[row][col] += x;
                }
            }

            tree.rangeAdd(x1 + 1, y1 + 1, x2 + 1, y2 + 1, x);

            x1 = std::uniform_int_distribution<int>(0, m - 1)(gen);
            y1 = std::uniform_int_distribution<int>(0, n - 1)(gen);
            x2 = std::uniform_int_distribution<int>(x1, m - 1)(gen);
            y2 = std::uniform_int_distribution<int>(y1, n - 1)(gen);
            int expected = 0;
            for (int row = x1; row <= x2; row++) {
                for (int col = y1; col <= y2; col++) {
                    expected += grid[row][col];
                }
            }
            assert(tree.rangeQuery(x1 + 1, y1 + 1, x2 + 1, y2 + 1) == expected);
        }
    }

    static void SolutionTest() {
        std::vector<int> nums={3, 4, -1};
        assert(Solution::lc_2659(nums)==5);
    }
};


int main() {
    TestGeneral::PointAddRangeSumTest();
    TestGeneral::PointAscendPreMaxTest();
    TestGeneral::PointAscendRangeMaxTest();
    TestGeneral::PointChangeRangeSumTest();
    TestGeneral::PointDescendPreMinTest();
    TestGeneral::PointDescendRangeMinTest();
    TestGeneral::PointXorRangeXorTest();
    TestGeneral::RangeAddRangeSumTest();
    TestGeneral::PointAddRangeSum2DTest();
    TestGeneral::RangeAddRangeSum2DTest();
    TestGeneral::SolutionTest();
    return 0;
}
