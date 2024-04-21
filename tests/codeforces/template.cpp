#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <sstream>


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
    static std::vector<double> read_list_floats() {
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
    static std::vector<int> read_list_ints_minus_one() {
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
    static void st(const T &x) {
        std::cout << x << std::endl;
    }

    // 输出一行整数列表
    static void lst(const std::vector<int> &nums) {
        for (int i = 0; i < nums.size(); i++) {
            std::cout << nums[i];
            if (i < nums.size() - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    // 输出一行浮点数列表
    static void lst(const std::vector<double> &nums) {
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
    static T max(const T &a, const T &b) {
        return a > b ? a : b;
    }

    // 返回两个数中的最小值
    template<typename T>
    static T min(const T &a, const T &b) {
        return a < b ? a : b;
    }
};


int main() {
    std::cout << "FastIO::read_int ready" << std::endl;
    int read_int = FastIO::read_int();
    std::cout << "which is " << read_int << std::endl;

    std::cout << "FastIO::read_float ready" << std::endl;
    double read_float = FastIO::read_float();
    std::cout << "which is " << read_float << std::endl;

    std::cout << "FastIO::read_list_ints ready" << std::endl;
    std::vector<int> read_list_ints = FastIO::read_list_ints();
    std::cout << "which is " << read_list_ints[0] << " " << read_list_ints[1] << std::endl;

    std::cout << "FastIO::read_list_floats ready" << std::endl;
    std::vector<double> read_list_floats = FastIO::read_list_floats();
    std::cout << "which is " << read_list_floats[0] << " " << read_list_floats[1] << std::endl;


    std::cout << "FastIO::read_list_ints_minus_one ready" << std::endl;
    std::vector<int> read_list_ints_minus_one = FastIO::read_list_ints_minus_one();
    std::cout << "which is " << read_list_ints_minus_one[0] << " " << read_list_ints_minus_one[1] << std::endl;

    std::cout << "FastIO::read_str ready" << std::endl;
    std::string read_str = FastIO::read_str();
    std::cout << "which is " << read_str << std::endl;


    std::cout << "FastIO::read_list_strs ready" << std::endl;
    std::vector<std::string> read_list_strs = FastIO::read_list_strs();
    std::cout << "which is " << read_list_strs[0] << " " << read_list_strs[1] << std::endl;

    std::cout << "FastIO::read_list_str ready" << std::endl;
    std::vector<char> read_list_str = FastIO::read_list_str();
    std::cout << "which is " << read_list_str[0] << " " << read_list_str[1] << std::endl;


    return 0;
}