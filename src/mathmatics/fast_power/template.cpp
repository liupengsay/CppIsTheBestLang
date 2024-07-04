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
