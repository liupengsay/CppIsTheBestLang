#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define ac FastIO


class FastIO {
public:
    static long long read_int() {
        long long num;
        std::cin >> num;
        return num;
    }

    static float read_float() {
        float num;
        std::cin >> num;
        return num;
    }

    static std::vector<long long> read_list_ints() {
        long long n;
        std::cin >> n;
        std::vector<long long> nums(n);
        for (long long i = 0; i < n; i++) {
            std::cin >> nums[i];
        }
        return nums;
    }

    static std::vector<long long> read_list_ints_minus_one() {
        long long n;
        std::cin >> n;
        std::vector<long long> nums(n);
        for (long long i = 0; i < n; i++) {
            std::cin >> nums[i];
            nums[i] -= 1;
        }
        return nums;
    }

    static std::string read_str() {
        std::string str;
        std::cin >> str;
        return str;
    }

    static std::vector<std::string> read_list_strs() {
        long long n;
        std::cin >> n;
        std::vector<std::string> strs(n);
        for (long long i = 0; i < n; i++) {
            std::cin >> strs[i];
        }
        return strs;
    }

    static void st(long long x) {
        std::cout << x << std::endl;
    }

    static void lst(const std::vector<long long> &x) {
        for (long long num: x) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    static long long max(long long a, long long b) {
        return (a > b) ? a : b;
    }

    static long long min(long long a, long long b) {
        return (a < b) ? a : b;
    }

    static long long ceil(long long a, long long b) {
        return a / b + (a % b != 0);
    }

    static long long floor(long long a, long long b) {
        if (a > 0) {
            return a / b;
        }
        long long res = a / b;
        if (a % b) {
            res--;
        }
        return res;
    }
};



class Solution {
public:
    static void main() {

    }
};


int main() {
    Solution::main();
    return 0;
}