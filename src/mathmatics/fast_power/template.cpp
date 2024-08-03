#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const long long MOD = 998244353;

// 快速幂计算 a^b % mod
long long power(long long a, long long b, long long mod) {
    long long result = 1;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return result;
}

// 计算逆元
long long mod_inverse(long long a, long long mod) {
    return power(a, mod - 2, mod);
}


long long mod_inverse_mod_not_prime(long long a, long long mod) {
    long long m0 = mod, t, q;
    long long x0 = 0, x1 = 1;

    if (mod == 1) return 0;

    while (a > 1) {
        // q 是商
        q = a / mod;
        t = mod;

        // m 是余数，现在是模
        mod = a % mod, a = t;

        t = x0;

        x0 = x1 - q * x0;

        x1 = t;
    }

    if (x1 < 0) x1 += m0;

    return x1;
}
