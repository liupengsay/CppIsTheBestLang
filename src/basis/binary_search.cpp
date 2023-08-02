
/*

算法：二分查找
功能：利用单调性确定最优选择，通常可以使用SortedList、Bisect，还可以使用精度控制二分
题目：xx（xx）
===================================力扣===================================
4. 寻找两个正序数组的中位数（https://leetcode.cn/problems/median-of-two-sorted-arrays/）经典二分思想查找题
81. 搜索旋转排序数组 II（https://leetcode.cn/problems/search-in-rotated-sorted-array-ii/）经典有重复数字的旋转数组
154. 寻找旋转排序数组中的最小值 II（https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/）经典有重复数字的旋转数组
162. 寻找峰值（https://leetcode.cn/problems/find-peak-element/）经典二分思想查找题
2426 满足不等式的数对数目（https://leetcode.cn/problems/number-of-pairs-satisfying-inequality/）根据不等式变换和有序集合进行二分查找
2179 统计数组中好三元组数目（https://leetcode.cn/problems/count-good-triplets-in-an-array/）维护区间范围内的个数
2141 同时运行 N 台电脑的最长时间（https://leetcode.cn/problems/maximum-running-time-of-n-computers/）贪心选择最大的 N 个电池作为基底，然后二分确定在其余电池的加持下可以运行的最长时间
2102 序列顺序查询（https://leetcode.cn/problems/sequentially-ordinal-rank-tracker/）使用有序集合维护优先级姓名实时查询
2563. 统计公平数对的数目（https://leetcode.cn/problems/count-the-number-of-fair-pairs/）使用二分查找确定范围个数
2604. 吃掉所有谷子的最短时间（https://leetcode.cn/problems/minimum-time-to-eat-all-grains/）二分加指针贪心 check
1201. 丑数 III（https://leetcode.cn/problems/ugly-number-iii/）二分加容斥原理计数
1739. 放置盒子（https://leetcode.cn/problems/building-boxes/）可推公式二分也可数学方法计算
1889. 装包裹的最小浪费空间（https://leetcode.cn/problems/minimum-space-wasted-from-packaging/）排序加贪心二分
2071. 你可以安排的最多任务数目（https://leetcode.cn/problems/maximum-number-of-tasks-you-can-assign/）经典二分加贪心

===================================洛谷===================================
P1577 切绳子（https://www.luogu.com.cn/problem/P1577）数学整除向下取整与二分
P1570 KC 喝咖啡（https://www.luogu.com.cn/problem/P1570）公式转换后使用贪心加二分
P1843 奶牛晒衣服（https://www.luogu.com.cn/problem/P1843）贪心加二分
P2309 loidc，卖卖萌（https://www.luogu.com.cn/problem/P2309）使用前缀和有序列表加二分求解和为正数的子串个数
P2390 地标访问（https://www.luogu.com.cn/problem/P2390）枚举加二分起始也可以使用双指针
P2759 奇怪的函数（https://www.luogu.com.cn/problem/P2759）公式变换后使用二分求解
P1404 平均数（https://www.luogu.com.cn/problem/P1404）公式变换后使用前缀和加二分
P2855 [USACO06DEC]River Hopscotch S（https://www.luogu.com.cn/problem/P2855）使用贪心加二分
P2884 [USACO07MAR]Monthly Expense S（https://www.luogu.com.cn/problem/P2884）最大最小之类的经典二分问题
P2985 [USACO10FEB]Chocolate Eating S（https://www.luogu.com.cn/problem/P2985）使用贪心加二分进行模拟
P3184 [USACO16DEC]Counting Haybales S（https://www.luogu.com.cn/problem/P3184）二分查找区间范围内个数
P3611 [USACO17JAN]Cow Dance Show S（https://www.luogu.com.cn/problem/P3611）二分贪心加堆优化模拟
P3743 kotori的设备（https://www.luogu.com.cn/problem/P3743）经典二分查找注意check函数
P4058 [Code+#1]木材（https://www.luogu.com.cn/problem/P4058）经典二分查找注意check函数
P4670 [BalticOI 2011 Day2]Plagiarism（https://www.luogu.com.cn/problem/P4670）排序后二分查找计数
P5119 [USACO18DEC]Convention S（https://www.luogu.com.cn/problem/P5119）经典贪心加二分问题
P5250 【深基17.例5】木材仓库（https://www.luogu.com.cn/problem/P5250）维护一个有序集合
P6174 [USACO16JAN]Angry Cows S（https://www.luogu.com.cn/problem/P6174）经典贪心加二分问题
P6281 [USACO20OPEN] Social Distancing S（https://www.luogu.com.cn/problem/P6281）经典贪心加二分问题
P6423 [COCI2008-2009#2] SVADA（https://www.luogu.com.cn/problem/P6423）利用单调性进行二分计算
P7177 [COCI2014-2015#4] MRAVI（https://www.luogu.com.cn/problem/P7177）二分加树形dfs模拟
P1314 [NOIP2011 提高组] 聪明的质监员（https://www.luogu.com.cn/problem/P1314）经典二分寻找最接近目标值的和
P3017 [USACO11MAR]Brownie Slicing G（https://www.luogu.com.cn/problem/P3017）经典二分将矩阵分成a*b个子矩阵且子矩阵和的最小值最大
P1083 [NOIP2012 提高组] 借教室（https://www.luogu.com.cn/problem/P1083）经典二分结合差分进行寻找第一个失效点
P1281 书的复制（https://www.luogu.com.cn/problem/P1281）典型二分并输出方案
P1381 单词背诵（https://www.luogu.com.cn/problem/P1381）典型二分加滑动窗口check，脑筋急转弯
P1419 寻找段落（https://www.luogu.com.cn/problem/P1419）二分加优先队列
P1525 [NOIP2010 提高组] 关押罪犯（https://www.luogu.com.cn/problem/P1525）经典二分加BFS进行二分图划分，可以使用染色法或者并查集
P1542 包裹快递（https://www.luogu.com.cn/problem/P1542）二分加使用分数进行高精度计算
P2237 [USACO14FEB]Auto-complete S（https://www.luogu.com.cn/problem/P2237）脑筋急转弯排序后二分查找
P2810 Catch the theives（https://www.luogu.com.cn/problem/P2810）二分加枚举
P3718 [AHOI2017初中组]alter（https://www.luogu.com.cn/problem/P3718）二分加贪心
P3853 [TJOI2007]路标设置（https://www.luogu.com.cn/problem/P3853）经典二分贪心题
P4343 [SHOI2015]自动刷题机（https://www.luogu.com.cn/problem/P4343）上下界二分加模拟
P5844 [IOI2011]ricehub（https://www.luogu.com.cn/problem/P5844）经典中位数贪心与前缀和二分
P5878 奖品（https://www.luogu.com.cn/problem/P5878）经典二分加枚举
P6004 [USACO20JAN] Wormhole Sort S（https://www.luogu.com.cn/problem/P6004）经典二分加并查集
P6058 [加油武汉]体温调查（https://www.luogu.com.cn/problem/P6058）使用深搜序与离线 LCA 计算相邻叶子之间距离并二分确定时间
P6069 『MdOI R1』Group（https://www.luogu.com.cn/problem/P6069）经典方差计算公式变形，使用二分加变量维护区间的方差值大小
P6733 「Wdsr-2」间歇泉（https://www.luogu.com.cn/problem/P6733）二分加STL进行 Check
P8161 [JOI 2022 Final] 自学 (Self Study)（https://www.luogu.com.cn/problem/P8161）经典贪心加二分求解
P8198 [传智杯 #4 决赛] 背单词的小智（https://www.luogu.com.cn/problem/P8198）经典二分加指针
P9050 [PA2021] Sumy（https://www.luogu.com.cn/problem/P9050）经典二分注意值域区间与贪心模拟

================================CodeForces================================
https://codeforces.com/problemset/problem/1251/D（使用贪心进行中位数二分求解）
https://codeforces.com/problemset/problem/830/A（使用贪心进行距离点覆盖二分求解）
https://codeforces.com/problemset/problem/847/E（使用贪心二分与指针进行判断）
https://codeforces.com/problemset/problem/732/D（使用贪心二分与指针进行判断）
https://codeforces.com/problemset/problem/778/A（二分和使用指针判断是否check
https://codeforces.com/problemset/problem/913/C（DP预处理最优单价，再二分加贪心进行模拟求解）

G2. Teleporters (Hard Version)（https://codeforces.com/problemset/problem/1791/G2）贪心排序，前缀和枚举二分
D. Multiplication Table（https://codeforces.com/problemset/problem/448/D）经典二分查找计算n*m的乘法表第k大元素
D. Cleaning the Phone（https://codeforces.com/problemset/problem/1475/D）贪心排序，前缀和枚举二分
D. Odd-Even Subsequence（https://codeforces.com/problemset/problem/1370/D）利用单调性二分，再使用贪心check
D. Max Median（https://codeforces.com/problemset/problem/1486/D）利用单调性二分，再使用经典哈希前缀和计算和为正数的最长连续子序列
D2. Coffee and Coursework (Hard Version)（https://codeforces.com/problemset/problem/1118/D2）利用单调性贪心二分
I. Photo Processing（https://codeforces.com/problemset/problem/883/I）二分加双指针dp

================================AcWing================================
120. 防线（https://www.acwing.com/problem/content/122/）根据单调性二分
14. 不修改数组找出重复的数字（https://www.acwing.com/problem/content/description/15/）利用鸽巢原理二分查找重复的数，修改数组且只用O(1)空间

参考：OI WiKi（xx）
*/

#include <functional>
#include <vector>
#include <cassert>
#include <iostream>
using namespace std;

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

class Solution{

};

class TestGeneral {
public:
    static void BinarySearchTest() {
        std::vector<int> nums = {1, 2, 2, 2, 3, 4};
        int low = 0;
        size_t high = nums.size() - 1;

        // 整数二分测试
        auto check_left = [&](int x) -> bool {
            return nums[x] >= 2;
        };
        assert(BinarySearch::find_int_left(low, high, check_left) == 1);

        auto check_right = [&](int x) -> bool {
            return nums[x] <= 2;
        };
        assert(BinarySearch::find_int_right(low, high, check_right) == 3);


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
        cout << "BinarySearchTest Done" << endl;
    }

};


int main() {
    TestGeneral::BinarySearchTest();
    return 0;
};