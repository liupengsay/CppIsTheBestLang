#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <climits>
#include <tuple>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;

class SuffixArray {
public:
    SuffixArray() {}

    static tuple<vector<long long>, vector<long long>, vector<long long>>
    build(const vector<long long> &s, long long sig) {
        long long n = s.size();
        vector<long long> sa(n), rk(n), tmp(n), height(n);
        for (long long i = 0; i < n; ++i) sa[i] = i, rk[i] = s[i];
        long long ll = 0;
        while (true) {
            vector<long long> p;
            for (long long i = n - ll; i < n; ++i) p.push_back(i);
            for (long long i = 0; i < n; ++i) if (sa[i] >= ll) p.push_back(sa[i] - ll);
            vector<long long> cnt(sig, 0);
            for (long long i = 0; i < n; ++i) cnt[rk[i]]++;
            for (long long i = 1; i < sig; ++i) cnt[i] += cnt[i - 1];
            for (long long i = n - 1; i >= 0; --i) sa[--cnt[rk[p[i]]]] = p[i];
            auto equal = [&rk, n](long long i, long long j, long long l) {
                if (rk[i] != rk[j]) return false;
                if (i + l >= n && j + l >= n) return true;
                if (i + l < n && j + l < n) return rk[i + l] == rk[j + l];
                return false;
            };
            sig = 0;
            for (long long i = 0; i < n; ++i) tmp[i] = 0;
            tmp[sa[0]] = 0;
            for (long long i = 1; i < n; ++i) tmp[sa[i]] = equal(sa[i], sa[i - 1], ll) ? sig : ++sig;

            for (long long i = 0; i < n; ++i) rk[i] = tmp[i];
            if (++sig == n) break;
            ll = ll > 0 ? (ll << 1) : 1;
        }
        long long k = 0;
        for (long long i = 0; i < n; ++i) {
            if (rk[i] == 0) continue;
            long long j = sa[rk[i] - 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            height[rk[i]] = k;
            k = k - 1 < 0 ? 0 : k - 1;
        }
        return make_tuple(sa, rk, height);
    }
};

class SparseTable {
public:
    SparseTable(const std::vector<long long> &lst, long long (*fun)(long long, long long)) {
        long long n = lst.size();
        this->fun = fun;
        this->n = n;

        bit.resize(n + 1);
        long long l = 1, r = 2, v = 0;
        while (true) {
            long long flag = 0;
            for (long long i = l; i < r; ++i) {
                if (i >= n + 1) {
                    flag = 1;
                    break;
                }
                bit[i] = v;
            }
            if (!flag) {
                l *= 2;
                r *= 2;
                ++v;
                continue;
            }
            break;
        }


        st.resize(v + 1, std::vector<long long>(n));
        st[0] = lst;
        for (long long i = 1; i <= v; ++i) {
            for (long long j = 0; j <= n - (1 << i); ++j) {
                st[i][j] = fun(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    long long query(long long left, long long right) {
        assert(0 <= left && left <= right && right < n);
        long long pos = bit[right - left + 1];
        return fun(st[pos][left], st[pos][right - (1 << pos) + 1]);
    }

private:
    std::vector<long long> bit;
    std::vector<std::vector<long long>> st;
    long long n;

    long long (*fun)(long long, long long);
};

int main() {
    long long cases;
    std::cin >> cases;
    for (long long _ = 0; _ < cases; ++_) {
        long long n;
        std::cin >> n;
        std::vector<long long> s(n);
        for (long long i = 0; i < n; ++i) {
            char w;
            cin >> w;
            s[i] = w - 'a';
        }
        auto [sa, rk, nums] = SuffixArray::build(s, 26);


        SparseTable st(nums, [](long long a, long long b) { return std::min(a, b); });
        // Function to compute LCP between two suffixes
        auto lcp = [&](long long ii, long long jj) {
            long long ri, rj;
            ri = rk[ii];
            rj = rk[jj];
            if (ri > rj) {
                swap(ri, rj);
            }
            if (ri == rj) {
                return n - sa[ri];
            }
            return st.query(ri + 1, rj);
        };


        // Function to compare two suffixes
        auto compare = [&](std::pair<long long, long long> a, std::pair<long long, long long> b) {
            long long i1 = a.first;
            long long j1 = a.second;

            long long i2 = b.first;
            long long j2 = b.second;
            long long x = lcp(i1, i2);
            x = std::min(x, j1 - i1 + 1);
            x = std::min(x, j2 - i2 + 1);
            if (x == j1 - i1 + 1) {
                if (x == j2 - i2 + 1) {
                    return i1 < i2 ? -1 : 1;
                }
                return -1;
            }


            if (x == j2 - i2 + 1) {
                return 1;
            }
            return s[i1 + x] < s[i2 + x] ? -1 : 1;
        };
        std::vector<long long> stack = {n};
        for (long long i = n - 1; i >= 0; --i) {
            while (stack.size() >= 2 &&
                   compare({stack.back(), stack[stack.size() - 2] - 1}, {i, stack[stack.size() - 2] - 1}) == -1) {
                stack.pop_back();
            }
            stack.push_back(i);
        }
        string ans;
        long long right = n;
        for (size_t i = 1; i < stack.size(); ++i) {
            for (long long j = stack[i]; j < right; j++) {
                ans += static_cast<char>('a' + s[j]);;
            }
            right = stack[i];
        }
        cout << ans << endl;
    }
    return 0;
}