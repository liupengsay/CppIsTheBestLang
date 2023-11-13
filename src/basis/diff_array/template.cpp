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

