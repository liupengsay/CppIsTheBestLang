#include <iostream>
#include <cmath>

// 快速幂取模函数，用于计算 base^exp % mod
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// 求模逆元，使用费马小定理
long long mod_inverse(long long a, long long mod) {
    return mod_pow(a, mod - 2, mod);
}

int main() {
    long long n;
    const long long mod = 998244353;

    // 读取整数 n
    std::cin >> n;

    // 计算 m 为 n 的位数
    long long m = std::to_string(n).length();

    // 计算 q = 10^m % mod
    long long q = mod_pow(10, m, mod);

    // 计算 q-1 的模逆元
    long long inv_q_minus_1 = mod_inverse(q - 1, mod);

    // 计算 10^(m*n) % mod
    long long pow_10_mn = mod_pow(mod_pow(10, m, mod), n, mod);

    // 计算结果 ans
    long long ans = ((n % mod) * inv_q_minus_1 % mod) * (pow_10_mn - 1 + mod) % mod;

    // 输出结果

    std::cout << ans % mod << std::endl;

    return 0;
}
