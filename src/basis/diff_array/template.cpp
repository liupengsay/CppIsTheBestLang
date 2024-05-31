#include <vector>
#include <iostream>
#include <cassert>
#include <random>

using namespace std;

class PreFixSumMatrix {
private:
    vector<vector<long long>> pre; // 前缀和数组

public:
    explicit PreFixSumMatrix(vector<vector<long long>>& mat) { // 构造函数
        size_t m = mat.size(), n = mat[0].size();
        pre = vector<vector<long long>>(m + 1, vector<long long>(n + 1, 0)); // 初始化前缀和数组
        for (long long i = 0; i < m; i++) {
            for (long long j = 0; j < n; j++) {
                pre[i + 1][j + 1] = pre[i][j + 1] + pre[i + 1][j] - pre[i][j] + mat[i][j]; // 计算前缀和
            }
        }
    }

    long long query(long long xa, long long ya, long long xb, long long yb) { // 查询函数
        return pre[xb + 1][yb + 1] - pre[xb + 1][ya] - pre[xa][yb + 1] + pre[xa][ya]; // 计算子矩阵和
    }
};



class DiffArray {
public:
    static vector<long long> get_diff_array(long long n, vector<vector<long long>>& shifts) {
        // 计算差分数组
        vector<long long> diff(n, 0);
        for (const auto& shift : shifts) {
            long long i = shift[0], j = shift[1], d = shift[2];
            if (j + 1 < n) {
                diff[j + 1] -= d;
            }
            diff[i] += d;
        }
        for (long long i = 1; i < n; i++) {
            diff[i] += diff[i - 1];
        }
        return diff;
    }

    static vector<long long> get_array_prefix_sum(long long n, vector<long long>& lst) {
        // 计算前缀和
        vector<long long> pre(n + 1, 0);
        for (long long i = 0; i < n; i++) {
            pre[i + 1] = pre[i] + lst[i];
        }
        return pre;
    }

    static long long get_array_range_sum(vector<long long>& pre, long long left, long long right) {
        // 计算区间元素和
        return pre[right + 1] - pre[left];
    }
};


class DiffMatrix {
public:
    static vector<vector<long long>> get_diff_matrix(long long m, long long n, vector<vector<long long>>& shifts) {
        // 二维差分数组
        vector<vector<long long>> diff(m + 2, vector<long long>(n + 2, 0));
        // 索引从 1 开始，矩阵初始值为 0
        for (const auto& shift : shifts) {
            long long xa = shift[0], xb = shift[1], ya = shift[2], yb = shift[3], d = shift[4];
            diff[xa][ya] += d;
            diff[xa][yb + 1] -= d;
            diff[xb + 1][ya] -= d;
            diff[xb + 1][yb + 1] += d;
        }

        // 计算差分数组的前缀和
        for (long long i = 1; i <= m + 1; i++) {
            for (long long j = 1; j <= n + 1; j++) {
                diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
            }
        }

        // 转换成 m 行 n 列的数组并返回
        vector<vector<long long>> res(m, vector<long long>(n, 0));
        for (long long i = 0; i < m; i++) {
            for (long long j = 0; j < n; j++) {
                res[i][j] = diff[i + 1][j + 1];
            }
        }
        return res;
    }

    static vector<vector<long long>> get_diff_matrix2(long long m, long long n, vector<vector<long long>>& shifts) {
        // 二维差分数组
        vector<vector<long long>> diff(m + 1, vector<long long>(n + 1, 0));
        // 索引从 0 开始，矩阵初始值为 0
        for (const auto& shift : shifts) {
            long long xa = shift[0], xb = shift[1], ya = shift[2], yb = shift[3], d = shift[4];
            diff[xa][ya] += d;
            diff[xa][yb + 1] -= d;
            diff[xb + 1][ya] -= d;
            diff[xb + 1][yb + 1] += d;
        }

        // 转换成 m 行 n 列的数组并返回
        vector<vector<long long>> res(m+1, vector<long long>(n+1, 0));
        for (long long i = 0; i < m; i++) {
            for (long long j = 0; j < n; j++) {
                res[i+1][j+1] = res[i + 1][j] + \
                    res[i][j + 1] - res[i][j] + diff[i][j];
            }
        }

        vector<vector<long long>> ret(m, vector<long long>(n, 0));
        for (long long i = 0; i < m; i++) {
            for (long long j = 0; j < n; j++) {
                ret[i][j] = res[i+1][j+1];
            }
        }
        return ret;
    }

    static vector<vector<long long>> get_matrix_prefix_sum(vector<vector<long long>>& mat) {
        // 二维前缀和
        long long m = mat.size(), n = mat[0].size();
        vector<vector<long long>> pre(m + 1, vector<long long>(n + 1, 0));
        for (long long i = 0; i < m; i++) {
            for (long long j = 0; j < n; j++) {
                pre[i + 1][j + 1] = pre[i][j + 1] + pre[i + 1][j] - pre[i][j] + mat[i][j];
            }
        }
        return pre;
    }

    static long long get_matrix_range_sum(vector<vector<long long>>& pre, long long xa, long long ya, long long xb, long long yb) {
        // 二维子矩阵和
        return pre[xb + 1][yb + 1] - pre[xb + 1][ya] - pre[xa][yb + 1] + pre[xa][ya];
    }
};

