#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

class BinarySearch {
public:
    static int find_int_left(int low, int high, const std::function<bool(int)> &check) {
        // 模板: 整数范围内二分查找，选择最靠左满足check
        while (low < high - 1) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                high = mid;
            } else {
                low = mid;
            }
        }
        return check(low) ? low : high;
    }

    static int find_int_right(int low, int high, const std::function<bool(int)> &check) {
        // 模板: 整数范围内二分查找，选择最靠右满足check
        while (low < high - 1) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return check(high) ? high : low;
    }

    static double
    find_float_left(double low, double high, const std::function<bool(double)> &check, double error = 1e-6) {
        // 模板: 浮点数范围内二分查找, 选择最靠左满足check
        while (low < high - error) {
            double mid = low + (high - low) / 2;
            if (check(mid)) {
                high = mid;
            } else {
                low = mid;
            }
        }
        return check(low) ? low : high;
    }

    static double
    find_float_right(double low, double high, const std::function<bool(double)> &check, double error = 1e-6) {
        // 模板: 浮点数范围内二分查找, 选择最靠右满足check
        while (low < high - error) {
            double mid = low + (high - low) / 2;
            if (check(mid)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return check(high) ? high : low;
    }
};



std::string lg_p1542() {

    int n;
    std::cin >> n;
    std::vector<std::vector<int>> nums(n, std::vector<int>(3));
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i][0] >> nums[i][1] >> nums[i][2];
    }

    auto check= [&] (double xx) {
        // 最早与最晚出发
        auto add = [&](std::vector<int> &lst1, std::vector<int> &lst2) {
            // 进行分数加减
            int a = lst1[0], b = lst1[1];
            int c = lst2[0], d = lst2[1];
            int d1 = a * d + c * b;
            int d2 = b * d;
            std::vector<int> res = {d1, d2};
            return res;
        };

        std::vector<int> t1 = {0, 1};
        std::vector<double> res = {xx, 1};
        while (((int)res[0] - res[0]) > 1e-20) {
            res[0] *= 10;
            res[1] *= 10;
        }
        std::vector<int> tmp = {(int)res[0], (int)res[1]};
        for (auto &vec: nums) {
            int x = vec[0], y = vec[1], s = vec[2];
            std::vector<int> nex = {s * tmp[1], tmp[0]};
            std::vector<int> cur = add(t1, nex);
            if (cur[0] > y * cur[1]) {
                return false;
            }
            t1 = cur;
            if (cur[0] < x * cur[1]){
                t1 = {x, 1};
            }

        }
        return true;
    };


    double ans = BinarySearch::find_float_left(1e-4, 1e7, check);
    char buffer[32];
    sprintf(buffer, "%.2f", ans);
    return buffer;
}


int main() {
    std::cout << lg_p1542() << std::endl;
    return 0;
}