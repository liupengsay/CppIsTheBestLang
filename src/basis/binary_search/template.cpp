#include <functional>

class BinarySearch {
public:

    static long long find_long long_left(long long low, long long high, const std::function<bool(long long)> &check) {
        // 模板: 整数范围内二分查找，选择最靠左满足check
        while (low < high - 1) {
            long long mid = low + (high - low) / 2;
            if (check(mid)) {
                high = mid;
            } else {
                low = mid;
            }
        }
        return check(low) ? low : high;
    }

    static long long find_long long_right(long long low, long long high, const std::function<bool(long long)> &check) {
        // 模板: 整数范围内二分查找，选择最靠右满足check
        while (low < high - 1) {
            long long mid = low + (high - low) / 2;
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
