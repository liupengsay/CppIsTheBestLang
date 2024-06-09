#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>
#include <algorithm>


class Combinatorics {
public:

    long long n;
    long long mod;
    std::vector<long long> perm, rev;

    Combinatorics(long long n, long long mod) : n(n + 10), mod(mod) {
        build_perm();
        build_rev();
    }

    long long comb(long long a, long long b) {
        if (a < b) {
            return 0;
        }
        long long res = (1LL * perm[a] * rev[b] % mod) * rev[a - b] % mod;
        return res;
    }

    long long factorial(long long a) {
        return perm[a];
    }

    long long inverse(long long n) {
        return (1LL * perm[n - 1] * rev[n]) % mod;
    }

    long long catalan(long long n) {
        long long res = (comb(2 * n, n) - comb(2 * n, n - 1)) % mod;
        return res;
    }


    void build_perm() {
        perm.resize(n + 1);
        perm[0] = 1;
        for (long long i = 1; i <= n; ++i) {
            perm[i] = (1LL * perm[i - 1] * i) % mod;
        }
    }

    void build_rev() {
        rev.resize(n + 1);
        rev[n] = mod_inverse(perm[n], mod);
        for (long long i = n - 1; i >= 0; --i) {
            rev[i] = (1LL * rev[i + 1] * (i + 1)) % mod;
        }
    }

// 计算模意义下的逆元
    long long mod_inverse(long long a, long long m) {
        long long m0 = m, t, q;
        long long x0 = 0, x1 = 1;

        if (m == 1)
            return 0;

        // 使用扩展欧几里得算法来计算逆元
        while (a > 1) {
            // q 是 a/m 的商
            q = a / m;

            t = m;

            // m 是 a%m
            m = a % m, a = t;

            t = x0;

            // 更新 x0 为上一次 x1 - q * x0
            x0 = x1 - q * x0;

            x1 = t;
        }

        // 保证 x1 是正数
        if (x1 < 0)
            x1 += m0;

        return x1;
    }
};


// 计算 a 的 b 次幂模 m 的值
long long fast_power_mod(long long a, long long b, long long m) {
    long long result = 1;
    a = a % m; // 对底数取模，避免整数溢出

    while (b > 0) {
        // 如果 b 是奇数，将当前的底数乘到结果中
        if (b & 1) {
            result = (result * a) % m;
        }
        // 将底数自乘，指数减半
        a = (a * a) % m;
        b >>= 1; // 等价于 b /= 2
    }

    return result;
}

const int mod = 1000000007;
Combinatorics cb(2000, mod);


class Solution {
public:
    int valueAfterKSeconds(int n, int k) {
        return static_cast<int>(cb.comb(n+k-1, k));
    }
};
