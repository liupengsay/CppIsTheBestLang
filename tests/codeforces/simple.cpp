#include <iostream>
#include <vector>
#include <string>

//class FastIO {
//public:
//    static int read_int() {
//        int num;
//        std::cin >> num;
//        return num;
//    }
//
//    static float read_float() {
//        float num;
//        std::cin >> num;
//        return num;
//    }
//
//    static std::vector<int> read_list_ints() {
//        int n;
//        std::cin >> n;
//        std::vector<int> nums(n);
//        for (int i = 0; i < n; i++) {
//            std::cin >> nums[i];
//        }
//        return nums;
//    }
//
//    static std::vector<int> read_list_ints_minus_one() {
//        int n;
//        std::cin >> n;
//        std::vector<int> nums(n);
//        for (int i = 0; i < n; i++) {
//            std::cin >> nums[i];
//            nums[i] -= 1;
//        }
//        return nums;
//    }
//
//    static std::string read_str() {
//        std::string str;
//        std::cin >> str;
//        return str;
//    }
//
//    static std::vector<std::string> read_list_strs() {
//        int n;
//        std::cin >> n;
//        std::vector<std::string> strs(n);
//        for (int i = 0; i < n; i++) {
//            std::cin >> strs[i];
//        }
//        return strs;
//    }
//
//    static void st(int x) {
//        std::cout << x << std::endl;
//    }
//
//    static void lst(const std::vector<int>& x) {
//        for (int num : x) {
//            std::cout << num << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    static int max(int a, int b) {
//        return (a > b) ? a : b;
//    }
//
//    static int min(int a, int b) {
//        return (a < b) ? a : b;
//    }
//
//    static int ceil(int a, int b) {
//        return a / b + (a % b != 0);
//    }
//};
//
//std::string lg_p1542() {
//
//    int n;
//    std::cin >> n;
//    std::vector<std::vector<int>> nums(n, std::vector<int>(3));
//    for (int i = 0; i < n; ++i) {
//        std::cin >> nums[i][0] >> nums[i][1] >> nums[i][2];
//    }
//
//    auto check= [&] (double xx) {
//        // 最早与最晚出发
//        auto add = [&](std::vector<int> &lst1, std::vector<int> &lst2) {
//            // 进行分数加减
//            int a = lst1[0], b = lst1[1];
//            int c = lst2[0], d = lst2[1];
//            int d1 = a * d + c * b;
//            int d2 = b * d;
//            std::vector<int> res = {d1, d2};
//            return res;
//        };
//
//        std::vector<int> t1 = {0, 1};
//        std::vector<double> res = {xx, 1};
//        while (((int)res[0] - res[0]) > 1e-20) {
//            res[0] *= 10;
//            res[1] *= 10;
//        }
//        std::vector<int> tmp = {(int)res[0], (int)res[1]};
//        for (auto &vec: nums) {
//            int x = vec[0], y = vec[1], s = vec[2];
//            std::vector<int> nex = {s * tmp[1], tmp[0]};
//            std::vector<int> cur = add(t1, nex);
//            if (cur[0] > y * cur[1]) {
//                return false;
//            }
//            t1 = cur;
//            if (cur[0] < x * cur[1]){
//                t1 = {x, 1};
//            }
//
//        }
//        return true;
//    };
//
//
//    double ans = BinarySearch::find_float_left(1e-4, 1e7, check);
//    char buffer[32];
//    sprintf(buffer, "%.2f", ans);
//    return buffer;
//}


int main() {
    std::cout << INT_MAX << std::endl;
    return 0;
}