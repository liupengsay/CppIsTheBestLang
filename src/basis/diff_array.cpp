
/*

算法：差分数组与前缀和、后缀和、前缀最大子序列和、后缀最大子序列和、二维差分、离散化差分、三维差分、二位前缀和
        功能：用来解决一维数组或者二维数组的加和问题，以及前缀和计算，还有前缀和的前缀和
        题目：

===================================力扣===================================
152. 乘积最大子数组（https://leetcode.cn/problems/maximum-product-subarray/）前缀最大最小乘积，计算最大连续子数组乘积
598. 范围求和 II（https://leetcode.cn/problems/range-addition-ii/）二维差分
2281. 巫师的总力量（https://leetcode.cn/problems/sum-of-total-strength-of-wizards/）枚举当前元素作为最小值的子数组和并使用前缀和的前缀和计算
2251. 花期内花的数目（https://leetcode.cn/problems/number-of-flowers-in-full-bloom/）离散化差分数组
2132. 用邮票贴满网格图（https://leetcode.cn/problems/stamping-the-grid/）用前缀和枚举可行的邮票左上端点，然后查看空白格点左上方是否有可行的邮票点，也可以使用经典的二维差分滚动模拟覆盖进行解决
1229. 安排会议日程（https://leetcode.cn/problems/meeting-scheduler/）离散化差分数组
6292. 子矩阵元素加 1（https://leetcode.cn/problems/increment-submatrices-by-one/)二维差分前缀和
2565. 最少得分子序列（https://leetcode.cn/problems/subsequence-with-the-minimum-score/）使用前后缀指针枚举匹配最长前后缀
644. 子数组最大平均数 II（https://leetcode.cn/problems/maximum-average-subarray-ii/）前缀和加二分计算不短于k的子数组最大平均值
1292. 元素和小于等于阈值的正方形的最大边长（https://leetcode.cn/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/）经典O(mn)复杂度枚举
1674. 使数组互补的最少操作次数（https://leetcode.cn/problems/minimum-moves-to-make-array-complementary/）经典差分数组作用域计数
1714. 数组中特殊等间距元素的和（https://leetcode.cn/problems/sum-of-special-evenly-spaced-elements-in-array/）经典分组加前缀和
1738. 找出第 K 大的异或坐标值（https://leetcode.cn/problems/find-kth-largest-xor-coordinate-value/）经典二维前缀异或和
1895. 最大的幻方（https://leetcode.cn/problems/largest-magic-square/）二维前缀和枚举优化
1943. 描述绘画结果（https://leetcode.cn/problems/describe-the-painting/）经典离散化差分
2021. 街上最亮的位置（https://leetcode.cn/problems/brightest-position-on-street/）经典离散化差分

===================================洛谷===================================
P8772 [蓝桥杯 2022 省 A] 求和（https://www.luogu.com.cn/record/list?user=739032&status=12&page=15）后缀和计算
P2367 语文成绩（https://www.luogu.com.cn/problem/P2367）差分数组记录区间增减变化，最后还原计算最小值
P2280 [HNOI2003]激光炸弹（https://www.luogu.com.cn/problem/P2280）二维前缀和
P3138 [USACO16FEB]Load Balancing S（https://www.luogu.com.cn/problem/P3138）二维前缀和
P3406 海底高铁（https://www.luogu.com.cn/problem/P3406）差分数组计算每段路经过次数，再贪心新选择买卡还是单刷
P3655 不成熟的梦想家 (未熟 DREAMER)（https://www.luogu.com.cn/problem/P3655）差分数组变形模拟
P5542 [USACO19FEB]Painting The Barn S（https://www.luogu.com.cn/problem/P5542）二维差分，需要适配覆盖区间
P5686 [CSP-S2019 江西] 和积和（https://www.luogu.com.cn/problem/P5686）前缀和的前缀和
P6180 [USACO15DEC]Breed Counting S（https://www.luogu.com.cn/problem/P6180）前缀和计数
P6481 [COCI2006-2007] FIREFLY（https://www.luogu.com.cn/problem/P6481）区间更新后进行所有前缀查询
P2956 [USACO09OCT]The Robot Plow G（https://www.luogu.com.cn/problem/P2956）二维差分前缀和
P3397 地毯（https://www.luogu.com.cn/problem/P3397）二维差分前缀和
P1869 愚蠢的组合数（https://www.luogu.com.cn/problem/P1869）使用前缀和记录1-N的因子2的个数继而计算C(N,K)的奇偶性
P7667 [JOI2018] Art Exhibition（https://www.luogu.com.cn/problem/P7667）公式变换，排序后使用前缀和
P2671 [NOIP2015 普及组] 求和（https://www.luogu.com.cn/problem/P2671）前缀加和与前缀计数枚举，分奇偶性讨论
P1719 最大加权矩形（https://www.luogu.com.cn/problem/P1719）求最大子矩阵和，经典枚举矩阵上下边界并使用前缀和计算
P2882 [USACO07MAR]Face The Right Way G（https://www.luogu.com.cn/problem/P2882）贪心枚举加差分验证
P4552 [Poetize6] IncDec Sequence（https://www.luogu.com.cn/problem/P4552）差分数组经典题，明晰差分本质
P1627 [CQOI2009] 中位数（https://www.luogu.com.cn/problem/P1627）经典前后缀中位数大小值差值计数
P1895 数字序列（https://www.luogu.com.cn/problem/P1895）前缀和计数加二分查找，最多不超多10**5
P1982 [NOIP2013 普及组] 小朋友的数字（https://www.luogu.com.cn/problem/P1982）前缀最大连续子段和与前缀最大值
P2070 刷墙（https://www.luogu.com.cn/problem/P2070）哈希离散化差分数组计数
P2190 小Z的车厢（https://www.luogu.com.cn/problem/P2190）环形数组差分
P2352 队爷的新书（https://www.luogu.com.cn/problem/P2352）离散化差分
P2363 马农（https://www.luogu.com.cn/problem/P2363）二维前缀和与枚举
P2706 巧克力（https://www.luogu.com.cn/problem/P2706）不包含障碍点的最大子矩阵和
P2879 [USACO07JAN] Tallest Cow S（https://www.luogu.com.cn/problem/P2879）差分数组经典题与贪心
P3028 [USACO10OCT]Soda Machine G（https://www.luogu.com.cn/problem/P3028）离散化差分计算覆盖区间最多的点
P4030 [Code+#2]可做题1（https://www.luogu.com.cn/problem/P4030）脑筋急转弯加二维前缀和计算
P4440 [COCI2017-2018#3] Programiranje（https://www.luogu.com.cn/problem/P4440）典型前缀和计数
P4623 [COCI2012-2013#6] BUREK（https://www.luogu.com.cn/problem/P4623）离散化差分计数
P6032 选择客栈 加强版（https://www.luogu.com.cn/problem/P6032）经典前后缀计数
P6070 『MdOI R1』Decrease（https://www.luogu.com.cn/problem/P6070）经典二维差分贪心修改实时维护差分与计算前缀和即矩阵最新值
P6278 [USACO20OPEN]Haircut G（https://www.luogu.com.cn/problem/P6278）经典逆序对作用域与差分前缀和计算
P6537 [COCI2013-2014#1] RATAR（https://www.luogu.com.cn/problem/P6537）预处理前缀和加枚举
P6877 [JOI 2020 Final] 長いだけのネクタイ（https://www.luogu.com.cn/problem/P6877）排序贪心前后缀 DP 枚举
P6878 [JOI 2020 Final] JJOOII 2（https://www.luogu.com.cn/problem/P6878）前后缀枚举
P8081 [COCI2011-2012#4] ZIMA（https://www.luogu.com.cn/problem/P8081）差分计数计算作用域
P8033 [COCI2015-2016#7] Prozor（https://www.luogu.com.cn/problem/P8033）二维前缀和计数
P7992 [USACO21DEC] Convoluted Intervals S（https://www.luogu.com.cn/problem/P7992）经典桶计数与作用域差分计数
P7948 [✗✓OI R1] 前方之风（https://www.luogu.com.cn/problem/P7948）排序后预处理前后缀信息指针查询
P8343 [COCI2021-2022#6] Zemljište（https://www.luogu.com.cn/problem/P8343）经典子矩阵前缀和枚举与双指针
P8551 Bassline（https://www.luogu.com.cn/problem/P8551）差分数组经典灵活应用
P8666 [蓝桥杯 2018 省 A] 三体攻击（https://www.luogu.com.cn/problem/P8666）二分加三维差分经典题，滚动模拟覆盖计算
P8715 [蓝桥杯 2020 省 AB2] 子串分值（https://www.luogu.com.cn/problem/P8715）前后缀贡献计数
P8783 [蓝桥杯 2022 省 B] 统计子矩阵（https://www.luogu.com.cn/problem/P8783）经典O(n^3)与双指针枚举计算子矩阵个数

================================CodeForces================================
https://codeforces.com/problemset/problem/33/C（前后缀最大变换和与分割点枚举，经典类型题目）
https://codeforces.com/problemset/problem/797/C（后缀最小值字典序模拟）
https://codeforces.com/problemset/problem/75/D（压缩数组最大子段和）
C. Count Triangles（https://codeforces.com/problemset/problem/1355/C）经典使用作用域差分计算，合法三角形边长个数
C. Tea Tasting（https://codeforces.com/problemset/problem/1795/C）前缀和二分后，经典使用差分计数模拟加和
D. Constant Palindrome Sum（https://codeforces.com/problemset/problem/1343/D）枚举x使用差分数组进行范围计数
E. Counting Rectangles（https://codeforces.com/problemset/problem/1722/E）根据数字取值范围使用二位前缀和计算
D. Absolute Sorting（https://codeforces.com/contest/1772/problem/D）离散差分作用域计数

================================AcWing===================================
99. 激光炸弹（https://www.acwing.com/problem/content/description/101/）二维前缀和
100. 增减序列（https://www.acwing.com/problem/content/102/）差分数组经典题目，明晰本质
101. 最高的牛（https://www.acwing.com/problem/content/103/）查分数组，贪心得出结论
102. 最佳牛围栏（https://www.acwing.com/problem/content/104/）前缀和加二分计算不短于k的子数组最大平均值
121. 赶牛入圈（https://www.acwing.com/problem/content/description/123/）经典离散化前缀和，双指针加二分
126. 最大的和（https://www.acwing.com/problem/content/128/）经典最大子矩形和

参考：OI WiKi（xx）
*/


#include <vector>
#include <iostream>
#include <cassert>
#include <random>

using namespace std;

class PreFixSumMatrix {
private:
    vector<vector<int>> pre; // 前缀和数组

public:
    explicit PreFixSumMatrix(vector<vector<int>>& mat) { // 构造函数
        size_t m = mat.size(), n = mat[0].size();
        pre = vector<vector<int>>(m + 1, vector<int>(n + 1, 0)); // 初始化前缀和数组
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                pre[i + 1][j + 1] = pre[i][j + 1] + pre[i + 1][j] - pre[i][j] + mat[i][j]; // 计算前缀和
            }
        }
    }

    int query(int xa, int ya, int xb, int yb) { // 查询函数
        return pre[xb + 1][yb + 1] - pre[xb + 1][ya] - pre[xa][yb + 1] + pre[xa][ya]; // 计算子矩阵和
    }
};



class DiffArray {
public:
    static vector<int> get_diff_array(int n, vector<vector<int>>& shifts) {
        // 计算差分数组
        vector<int> diff(n, 0);
        for (const auto& shift : shifts) {
            int i = shift[0], j = shift[1], d = shift[2];
            if (j + 1 < n) {
                diff[j + 1] -= d;
            }
            diff[i] += d;
        }
        for (int i = 1; i < n; i++) {
            diff[i] += diff[i - 1];
        }
        return diff;
    }

    static vector<int> get_array_prefix_sum(int n, vector<int>& lst) {
        // 计算前缀和
        vector<int> pre(n + 1, 0);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] + lst[i];
        }
        return pre;
    }

    static int get_array_range_sum(vector<int>& pre, int left, int right) {
        // 计算区间元素和
        return pre[right + 1] - pre[left];
    }
};


class DiffMatrix {
public:
    static vector<vector<int>> get_diff_matrix(int m, int n, vector<vector<int>>& shifts) {
        // 二维差分数组
        vector<vector<int>> diff(m + 2, vector<int>(n + 2, 0));
        // 索引从 1 开始，矩阵初始值为 0
        for (const auto& shift : shifts) {
            int xa = shift[0], xb = shift[1], ya = shift[2], yb = shift[3], d = shift[4];
            diff[xa][ya] += d;
            diff[xa][yb + 1] -= d;
            diff[xb + 1][ya] -= d;
            diff[xb + 1][yb + 1] += d;
        }

        // 计算差分数组的前缀和
        for (int i = 1; i <= m + 1; i++) {
            for (int j = 1; j <= n + 1; j++) {
                diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
            }
        }

        // 转换成 m 行 n 列的数组并返回
        vector<vector<int>> res(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                res[i][j] = diff[i + 1][j + 1];
            }
        }
        return res;
    }

    static vector<vector<int>> get_diff_matrix2(int m, int n, vector<vector<int>>& shifts) {
        // 二维差分数组
        vector<vector<int>> diff(m + 1, vector<int>(n + 1, 0));
        // 索引从 0 开始，矩阵初始值为 0
        for (const auto& shift : shifts) {
            int xa = shift[0], xb = shift[1], ya = shift[2], yb = shift[3], d = shift[4];
            diff[xa][ya] += d;
            diff[xa][yb + 1] -= d;
            diff[xb + 1][ya] -= d;
            diff[xb + 1][yb + 1] += d;
        }

        // 转换成 m 行 n 列的数组并返回
        vector<vector<int>> res(m+1, vector<int>(n+1, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                res[i+1][j+1] = res[i + 1][j] + \
                    res[i][j + 1] - res[i][j] + diff[i][j];
            }
        }

        vector<vector<int>> ret(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ret[i][j] = res[i+1][j+1];
            }
        }
        return ret;
    }

    static vector<vector<int>> get_matrix_prefix_sum(vector<vector<int>>& mat) {
        // 二维前缀和
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> pre(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                pre[i + 1][j + 1] = pre[i][j + 1] + pre[i + 1][j] - pre[i][j] + mat[i][j];
            }
        }
        return pre;
    }

    static int get_matrix_range_sum(vector<vector<int>>& pre, int xa, int ya, int xb, int yb) {
        // 二维子矩阵和
        return pre[xb + 1][yb + 1] - pre[xb + 1][ya] - pre[xa][yb + 1] + pre[xa][ya];
    }
};




class Solution{

};

class TestGeneral {
public:
    static void PreFixSumMatrixTest() {
        // 测试用例
        vector<vector<int>> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        PreFixSumMatrix pfsm(mat);
        assert(pfsm.query(0, 0, 0, 0) == 1);
        assert(pfsm.query(0, 0, 1, 1) == 12);
        assert(pfsm.query(1, 1, 2, 2) == 28);
        assert(pfsm.query(0, 0, 2, 2) == 45);
        cout << "PreFixSumMatrixTest Done" << endl;
    }


    static void DiffArrayTest() {
        // 测试用例
        vector<vector<int>> shifts = {{1, 3, 2}, {2, 4, 3}, {0, 2, -2}};
        vector<int> lst = {1, 2, 3, 4, 5};
        int n = static_cast<int>(lst.size());
        vector<int> diff = DiffArray::get_diff_array(n, shifts);
        vector<int> pre = DiffArray::get_array_prefix_sum(n, diff);

        assert(DiffArray::get_array_range_sum(pre, 0, 3) == 6);
        assert(DiffArray::get_array_range_sum(pre, 1, 2) == 3);
        assert( DiffArray::get_array_range_sum(pre, 0, 4) == 9);


        int n2 = 3;
        vector<vector<int>> shifts2 = {{0, 1, 1}, {1, 2, -1}};
        vector<int> diff2 = DiffArray::get_diff_array(n2, shifts2);
        vector<int> target2 = {1, 0, -1};
        assert(diff2 == target2);

        int n3 = 3;
        vector<int> shifts3 = {1, 2, 3};
        vector<int> diff3 = DiffArray::get_array_prefix_sum(n3, shifts3);
        vector<int> target3 = {0, 1, 3, 6};
        assert(diff3 == target3);

        int left = 1;
        int right = 2;

        assert(DiffArray::get_array_range_sum(diff3, left, right) == 5);
        cout << "PreFixSumMatrixTest Done" << endl;
    }


    static void DiffMatrixTest() {
        // 测试用例
        vector<vector<int>> shifts = {{1, 2, 1, 2, 1},
                                      {2, 3, 2, 3, 1},
                                      {2, 2, 2, 2, 2},
                                      {1, 1, 3, 3, 3}};
        vector<vector<int>> target = {{1, 1, 3},
                                      {1, 4, 1},
                                      {0, 1, 1}};
        // 测试 get_diff_matrix 方法
        vector<vector<int>> diff = DiffMatrix::get_diff_matrix(3, 3, shifts);
        assert(diff == target);

        // 测试 get_diff_matrix2 方法
        for (auto &shift: shifts) {
            for (int i = 0; i < 4; i++) {
                shift[i] -= 1;
            }
        }
        vector<vector<int>> diff2 = DiffMatrix::get_diff_matrix2(3, 3, shifts);
        assert(diff2 == target);

        // 使用随机生成测试
        random_device rd;
        mt19937 gen(rd());

        for (int t = 0; t < 10; t++) {
            int m = uniform_int_distribution<int>(1, 100)(gen);
            int n = uniform_int_distribution<int>(1, 100)(gen);

            vector<vector<int>> ans(m, vector<int>(n, 0));
            vector<vector<int>> shifts2;
            for (int i = 0; i < 100; i++) {
                int xa = uniform_int_distribution<int>(1, m)(gen);
                int xb = uniform_int_distribution<int>(xa, m)(gen);

                int ya = uniform_int_distribution<int>(1, n)(gen);
                int yb = uniform_int_distribution<int>(ya, n)(gen);

                int x = uniform_int_distribution<int>(-100, 100)(gen);
                shifts2.push_back({xa, xb, ya, yb, x});

                for (int a = xa - 1; a < xb; a++) {
                    for (int b = ya - 1; b < yb; b++) {
                        ans[a][b] += x;
                    }
                }
                assert(DiffMatrix::get_diff_matrix(m, n, shifts2) == ans);
            }
        }
        cout << "DiffMatrixTest Done" << endl;
    }

};


int main() {
    TestGeneral::PreFixSumMatrixTest();
    TestGeneral::DiffArrayTest();
    TestGeneral::DiffMatrixTest();
    return 0;
};
