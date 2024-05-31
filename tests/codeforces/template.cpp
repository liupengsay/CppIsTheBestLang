#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <sstream>


class FastIO {
public:
    static long long read_long long() {
        long long x;
        std::cin >> x;
        return x;
    }

    static double read_float() {
        double x;
        std::cin >> x;
        return x;
    }

    static std::vector<long long> read_list_long longs() {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::vector<long long> nums;
        long long x;
        while (ss >> x) {
            nums.push_back(x);
        }
        return nums;
    }

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

    static std::vector<long long> read_list_long longs_minus_one() {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::vector<long long> nums;
        long long x;
        while (ss >> x) {
            nums.push_back(x - 1);
        }
        return nums;
    }

    static std::string read_str() {
        std::string line;
        std::getline(std::cin, line);
        return line;
    }


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


    static std::vector<char> read_list_str() {
        std::string line;
        std::getline(std::cin, line);
        std::vector<char> chars(line.begin(), line.end());
        return chars;
    }


    template<typename T>
    static void st(const T &x) {
        std::cout << x << std::endl;
    }


    static void lst(const std::vector<long long> &nums) {
        for (long long i = 0; i < nums.size(); i++) {
            std::cout << nums[i];
            if (i < nums.size() - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }


    static void lst(const std::vector<double> &nums) {
        for (long long i = 0; i < nums.size(); i++) {
            std::cout << nums[i];
            if (i < nums.size() - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }


    static long long round_5(double x) {
        long long res = static_cast<long long>(x);
        if (x - res >= 0.5) {
            res += 1;
        }
        return res;
    }


    template<typename T>
    static T max(const T &a, const T &b) {
        return a > b ? a : b;
    }


    template<typename T>
    static T min(const T &a, const T &b) {
        return a < b ? a : b;
    }
};


long long main() {
    std::cout << "FastIO::read_long long ready" << std::endl;
    long long read_long long = FastIO::read_long long();
    std::cout << "which is " << read_long long << std::endl;

    std::cout << "FastIO::read_float ready" << std::endl;
    double read_float = FastIO::read_float();
    std::cout << "which is " << read_float << std::endl;

    std::cout << "FastIO::read_list_long longs ready" << std::endl;
    std::vector<long long> read_list_long longs = FastIO::read_list_long longs();
    std::cout << "which is " << read_list_long longs[0] << " " << read_list_long longs[1] << std::endl;

    std::cout << "FastIO::read_list_floats ready" << std::endl;
    std::vector<double> read_list_floats = FastIO::read_list_floats();
    std::cout << "which is " << read_list_floats[0] << " " << read_list_floats[1] << std::endl;


    std::cout << "FastIO::read_list_long longs_minus_one ready" << std::endl;
    std::vector<long long> read_list_long longs_minus_one = FastIO::read_list_long longs_minus_one();
    std::cout << "which is " << read_list_long longs_minus_one[0] << " " << read_list_long longs_minus_one[1] << std::endl;

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