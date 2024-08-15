#include <iostream>
template <typename T>


inline void read(T &x)//快读
{
    char c;
    x = 0;
    int fu = 1;
    c = getchar();
    while(c > 57 || c < 48)
    {
        if(c == 45)
        {
            fu = -1;
        }
        c = getchar();
    }
    while(c <= 57 && c >= 48)
    {
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}


long long mod_exp(long long base, long long exp, long long mod) {
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


long long a[5000010];
long long post[5000010];

int main() {
    std::ios::sync_with_stdio(false); // https://www.luogu.com.cn/problem/P5431
    std::cin.tie(nullptr);

    long long n, p, k;
    read(n);
    read(p);
    read(k);

    for (long long i = 0; i < n; ++i) {
        read(a[i]);
    }

    post[n] = 1;
    for (long long i = n - 1; i >= 0; --i) {
        post[i] = (post[i + 1] * a[i]) % p;

    }

    long long kk = k;
    long long pre = 1;
    long long ans = 0;
    for (long long i = 0; i < n; ++i) {
        ans = (ans + ((kk * pre) % p) * post[i + 1] % p) % p;
        kk = (kk * k) % p;
        pre = (pre * a[i]) % p;
    }

    long long pre_inv = mod_exp(pre, p - 2, p);
    ans = (ans * pre_inv) % p;

    std::cout << ans << "\n";
    return 0;
}
