#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

class PrimeFactor {
public:
    PrimeFactor(long long max_n) {
        sieve(max_n);
    }

    vector<pair<long long, long long>> prime_factor(long long num) {
        vector<pair<long long, long long>> factors;
        while (num > 1) {
            long long prime = spf[num];
            long long count = 0;
            while (num % prime == 0) {
                num /= prime;
                count++;
            }
            factors.emplace_back(prime, count);
        }
        return factors;
    }

private:
    vector<long long> spf; // smallest prime factor

    void sieve(long long max_n) {
        spf.resize(max_n + 1);
        for (long long i = 2; i <= max_n; i++) spf[i] = i;
        for (long long i = 2; i * i <= max_n; i++) {
            if (spf[i] == i) {
                for (long long j = i * i; j <= max_n; j += i) {
                    if (spf[j] == j) {
                        spf[j] = i;
                    }
                }
            }
        }
    }
};

class UnionFind {
public:
    UnionFind(long long size) : parent(size), rank(size, 0), part(size) {
        for (long long i = 0; i < size; ++i) parent[i] = i;
    }

    long long find(long long u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void union_sets(long long u, long long v) {
        long long root_u = find(u);
        long long root_v = find(v);
        if (root_u != root_v) {
            if (rank[root_u] > rank[root_v]) {
                parent[root_v] = root_u;
            } else if (rank[root_u] < rank[root_v]) {
                parent[root_u] = root_v;
            } else {
                parent[root_v] = root_u;
                rank[root_u]++;
            }
            part--;
        }
    }

    long long get_part() const {
        return part;
    }

private:
    vector<long long> parent;
    vector<long long> rank;
    long long part;
};

int main() {
    PrimeFactor pf(1000000);

    long long t;
    cin >> t;
    while (t--) {
        long long n, k;
        cin >> n >> k;
        vector<long long> nums(n);
        for (long long i = 0; i < n; ++i) {
            cin >> nums[i];
        }

        unordered_map<long long, long long> dct;
        UnionFind uf(2 * n - 1);
        for (long long i = 1; i < 2 * n; ++i) {
            long long num = nums[i % n];
            auto factors = pf.prime_factor(num);
            for (const auto &p: factors) {
                long long prime = p.first;
                if (prime > 1 && dct.count(prime) && i - dct[prime] <= k) {
                    uf.union_sets(dct[prime] - 1, i - 1);
                }
                dct[prime] = i;
            }
        }

        long long ans = uf.get_part();
        for (long long i = 0; i < n; ++i) {
            if (nums[i] == 1) {
                ans += i > 0 ? n - 2 : n - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
