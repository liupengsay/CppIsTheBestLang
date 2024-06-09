#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
#include <unordered_map>
#include <cmath>

using namespace std;


long long bit_length(long long x) {
    long long res = 0;
    while (x) {
        res += 1;
        x /= 2;
    }
    return res;
}

class BinaryTrieXor {
public:
    BinaryTrieXor(long long max_num, long long num_cnt) {
        if (max_num <= 0) {
            max_num = 1;
        }
        if (num_cnt <= 0) {
            num_cnt = 1;
        }
        binary_state = 2;
        max_bit = bit_length(max_num) - 1;
        cnt_bit = bit_length(num_cnt);
        node_cnt = (max_bit + 1) * num_cnt * binary_state;
        son_and_cnt.resize(node_cnt + 1, 0);
        ind = 1;
        mask = (1 << cnt_bit) - 1;
    }

    void initial() {
        fill(son_and_cnt.begin(), son_and_cnt.end(), 0);
        ind = 1;
    }

    bool add(long long num, long long c = 1) {
        long long cur = 0;
        son_and_cnt[cur] += c;
        for (long long k = max_bit; k >= 0; --k) {
            long long bit = (num >> k) & 1;
            if (!(son_and_cnt[(cur << 1) | bit] >> cnt_bit)) {
                son_and_cnt[(cur << 1) | bit] |= (ind << cnt_bit);
                ++ind;
            }
            cur = son_and_cnt[(cur << 1) | bit] >> cnt_bit;
            son_and_cnt[cur] += c;
        }
        return true;
    }

    bool remove(long long num, long long c = 1) {
        if ((son_and_cnt[0] & mask) < c) {
            return false;
        }
        long long cur = 0;
        son_and_cnt[0] -= c;
        for (long long k = max_bit; k >= 0; --k) {
            long long bit = (num >> k) & 1;
            cur = son_and_cnt[(cur << 1) | bit] >> cnt_bit;
            if (cur == 0 || (son_and_cnt[cur] & mask) < c) {
                return false;
            }
            son_and_cnt[cur] -= c;
        }
        return true;
    }

    long long count(long long num) {
        long long cur = 0;
        for (long long k = max_bit; k >= 0; --k) {
            long long bit = (num >> k) & 1;
            cur = son_and_cnt[(cur << 1) | bit] >> cnt_bit;
            if (cur == 0 || !(son_and_cnt[cur] & mask)) {
                return 0;
            }
        }
        return son_and_cnt[cur] & mask;
    }

    long long get_maximum_xor(long long x) {
        if (!(son_and_cnt[0] & mask)) {
            return -INT_MAX;
        }
        long long res = 0;
        long long cur = 0;
        for (long long k = max_bit; k >= 0; --k) {
            long long bit = (x >> k) & 1;
            long long nxt = son_and_cnt[(cur << 1) | (bit ^ 1)] >> cnt_bit;
            if (nxt == 0 || !(son_and_cnt[nxt] & mask)) {
                cur = son_and_cnt[(cur << 1) | bit] >> cnt_bit;
            } else {
                res |= 1 << k;
                cur = nxt;
            }
        }
        return res;
    }

    long long get_minimum_xor(long long x) {
        if (!(son_and_cnt[0] & mask)) {
            return INT_MAX;
        }
        long long res = 0;
        long long cur = 0;
        for (long long k = max_bit; k >= 0; --k) {
            long long bit = (x >> k) & 1;
            long long nxt = son_and_cnt[(cur << 1) | bit] >> cnt_bit;
            if (nxt == 0 || !(son_and_cnt[nxt] & mask)) {
                res |= 1 << k;
                cur = son_and_cnt[(cur << 1) | (bit ^ 1)] >> cnt_bit;
            } else {
                cur = nxt;
            }
        }
        return res;
    }

    long long get_kth_maximum_xor(long long x, long long rk) {
        assert(rk >= 1);
        if ((son_and_cnt[0] & mask) < rk) {
            return -INT_MAX;
        }
        long long res = 0;
        long long cur = 0;
        for (long long k = max_bit; k >= 0; --k) {
            long long bit = (x >> k) & 1;
            long long nxt = son_and_cnt[(cur << 1) | (bit ^ 1)] >> cnt_bit;
            if (nxt == 0 || (son_and_cnt[nxt] & mask) < rk) {
                if (nxt) {
                    rk -= son_and_cnt[nxt] & mask;
                }
                cur = son_and_cnt[(cur << 1) | bit] >> cnt_bit;
            } else {
                res |= 1 << k;
                cur = nxt;
            }
        }
        return res;
    }

    long long get_cnt_smaller_xor(long long x, long long y) {
        if (!(son_and_cnt[0] & mask)) {
            return 0;
        }
        long long res = 0;
        long long cur = 0;
        for (long long k = max_bit; k >= 0; --k) {
            long long bit = (x >> k) & 1;
            if (!((y >> k) & 1)) {
                long long nxt = son_and_cnt[(cur << 1) | bit] >> cnt_bit;
                if (nxt == 0 || !(son_and_cnt[nxt] & mask)) {
                    return res;
                }
                cur = nxt;
            } else {
                long long nxt = son_and_cnt[(cur << 1) | bit] >> cnt_bit;
                if (nxt) {
                    res += son_and_cnt[nxt] & mask;
                }
                nxt = son_and_cnt[(cur << 1) | (bit ^ 1)] >> cnt_bit;
                if (nxt == 0 || !(son_and_cnt[nxt] & mask)) {
                    return res;
                }
                cur = nxt;
            }
        }
        res += son_and_cnt[cur] & mask;
        return res;
    }

public:
    long long binary_state;
    long long max_bit;
    long long cnt_bit;
    long long node_cnt;
    vector<long long> son_and_cnt;
    long long ind;
    long long mask;
};


int main() {
    // https://codeforces.com/contest/1980/problem/G
    long long T;
    cin >> T;
    while (T--) {
        long long n, m;
        cin >> n >> m;
        vector<vector<pair<long long, long long>>> dct(n);
        for (long long i = 0; i < n - 1; ++i) {
            long long u, v, w;
            cin >> u >> v >> w;
            dct[u - 1].push_back({v - 1, w});
            dct[v - 1].push_back({u - 1, w});
        }

        vector<long long> dis(n, -1);
        vector<long long> path(n, 0);
        vector<long long> stack = {0};
        dis[0] = 0;
        while (!stack.empty()) {
            vector<long long> nex;
            for (long long x: stack) {
                for (auto [y, w]: dct[x]) {
                    if (dis[y] == -1) {
                        dis[y] = dis[x] + 1;
                        nex.push_back(y);
                        path[y] = path[x] ^ w;
                    }
                }
            }
            stack = nex;
        }

        BinaryTrieXor odd_trie(INT_MAX, n + 1);
        BinaryTrieXor even_trie(INT_MAX, n + 1);
        long long tot = 0;
        for (long long i = 0; i < n; ++i) {
            if (dis[i] % 2) {
                odd_trie.add(path[i], 1);
            } else {
                even_trie.add(path[i], 1);
            }
        }

        vector<long long> res;
        while (m--) {
            string op;
            cin >> op;
            if (op == "^") {
                long long x;
                cin >> x;
                tot ^= x;
            } else {
                long long v, x;
                cin >> v >> x;
                v--;
                long long cur = path[v] ^ x;
                if (dis[v] % 2) {
                    cur ^= tot;
                }
                long long ans = numeric_limits<long long>::min();
                if (dis[v] % 2) {
                    odd_trie.remove(path[v], 1);
                }
                ans = max(ans, odd_trie.get_maximum_xor(cur ^ tot));
                if (dis[v] % 2) {
                    odd_trie.add(path[v], 1);
                }
                if (dis[v] % 2 == 0) {
                    even_trie.remove(path[v], 1);
                }
                ans = max(ans, even_trie.get_maximum_xor(cur));
                if (dis[v] % 2 == 0) {
                    even_trie.add(path[v], 1);
                }
                res.push_back(ans);
            }
        }
        for (long long i = 0; i < res.size(); ++i) {
            if (i > 0) cout << " ";
            cout << res[i];
        }
        cout << endl;
    }
    return 0;
}