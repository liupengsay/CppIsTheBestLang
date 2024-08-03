#include <iostream>
#include <vector>

const long long MOD = 1000000007;

class Matrix {
public:
    std::vector<std::vector<long long>> mat;
    int size;

    Matrix(int n) : size(n) {
        mat.resize(n, std::vector<long long>(n, 0));
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                for (int k = 0; k < size; ++k) {
                    result.mat[i][j] = (result.mat[i][j] + mat[i][k] * other.mat[k][j] % MOD) % MOD;
                }
            }
        }
        return result;
    }
};

Matrix matrix_pow(Matrix base, long long exp) {
    int n = base.size;
    Matrix result(n);
    for (int i = 0; i < n; ++i) {
        result.mat[i][i] = 1;
    }
    while (exp) {
        if (exp % 2) {
            result = result * base;
        }
        base = base * base;
        exp /= 2;
    }
    return result;
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    if (n < m) {
        std::cout << 1 << std::endl;
        return 0;
    }
    // https://codeforces.com/problemset/problem/1117/D
    Matrix grid(m);
    for (long long i = 1; i < m; ++i) {
        grid.mat[i][i-1] = 1;
    }
    grid.mat[0][m-1] = grid.mat[m-1][m-1] = 1;

    Matrix res = matrix_pow(grid, n - m + 1);
    long long ans = 0;
    for (int i = 0; i < m; ++i) {
        ans = (ans + res.mat[m-1][i]) % MOD;
    }

    std::cout << ans << std::endl;
    return 0;
}
