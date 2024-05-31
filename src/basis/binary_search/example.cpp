
#include <vector>
#include <cassert>
#include <iostream>
#include "template.cpp"
using namespace std;


class TestGeneral {
public:
    static void BinarySearchTest() {
        std::vector<long long> nums = {1, 2, 2, 2, 3, 4};
        long long low = 0;
        size_t high = nums.size() - 1;

        // 整数二分测试
        auto check_left = [&](long long x) -> bool {
            return nums[x] >= 2;
        };
        assert(BinarySearch::find_long long_left(low, high, check_left) == 1);

        auto check_right = [&](long long x) -> bool {
            return nums[x] <= 2;
        };
        assert(BinarySearch::find_long long_right(low, high, check_right) == 3);


        double low_double = 0.0;
        double high_double = 1e9;
        double target = 2.0 / 3;
        double error = 1e-5;

        // 浮点数二分测试
        auto check_left_double = [&](double x) -> bool {
            return x * 3 >= 2;
        };

        double x_pre_left = BinarySearch::find_float_left(low_double, high_double, check_left_double);
        assert(abs(x_pre_left - target) <= error);

        auto check_right_double = [&](double x) -> bool {
            return x * 3 <= 2;
        };
        double x_pre_right = BinarySearch::find_float_right(low_double, high_double, check_right_double);
        assert(abs(x_pre_right - target) <= error);
    }

};


int main() {
    TestGeneral::BinarySearchTest();
    return 0;
};