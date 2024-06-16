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