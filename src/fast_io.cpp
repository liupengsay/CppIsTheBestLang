#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class FastIO {
public:
    // 读取一个整数
    static int read_int() {
        int x;
        std::cin >> x;
        return x;
    }

    // 读取一个浮点数
    static double read_float() {
        double x;
        std::cin >> x;
        return x;
    }

    // 读取一行整数列表
    static std::vector<int> read_list_ints() {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::vector<int> nums;
        int x;
        while (ss >> x) {
            nums.push_back(x);
        }
        return nums;
    }

    // 读取一行浮点数列表
    static std::vector<double> read_floats() {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::vector<double> nums;
        double x;
        while (ss >> x) {
            nums.push_back(x);
        }
        return nums;
    }

    // 读取一行整数列表，每个数减一
    static std::vector<int> read_ints_minus_one() {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::vector<int> nums;
        int x;
        while (ss >> x) {
            nums.push_back(x - 1);
        }
        return nums;
    }

    // 读取一行字符串
    static std::string read_str() {
        std::string line;
        std::getline(std::cin, line);
        return line;
    }

    // 读取一行字符串列表
    static std::vector<std::string> read_list_strs() {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::vector<std::string> strs;
        std::string s;
        while (ss >> s) {
            strs.push_back(s);
        }
        return strs;
    }

    // 读取一行字符列表
    static std::vector<char> read_list_str() {
        std::string line;
        std::getline(std::cin, line);
        std::vector<char> chars(line.begin(), line.end());
        return chars;
    }

    // 输出一个对象，并在末尾添加换行符
    template<typename T>
    static void st(const T& x) {
        std::cout << x << std::endl;
    }

    // 输出一行整数列表
    static void lst(const std::vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            std::cout << nums[i];
            if (i < nums.size() - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    // 输出一行浮点数列表
    static void lst(const std::vector<double>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            std::cout << nums[i];
            if (i < nums.size() - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    // 将浮点数四舍五入到最近的整数
    static int round_5(double x) {
        int res = static_cast<int>(x);
        if (x - res >= 0.5) {
            res += 1;
        }
        return res;
    }

    // 返回两个数中的最大值
    template<typename T>
    static T max(const T& a, const T& b) {
        return a > b ? a : b;
    }

    // 返回两个数中的最小值
    template<typename T>
    static T min(const T& a, const T& b) {
        return a < b ? a : b;
    }
};


int main() {
    // 读取一个整数
    int n = FastIO::read_int();

    // 读取一行整数列表
    std::vector<int> nums = FastIO::read_list_ints();

    // 输出结果
    FastIO::st(n);
    FastIO::lst(nums);

    return 0;
}