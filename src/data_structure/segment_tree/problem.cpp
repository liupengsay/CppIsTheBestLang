#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>

class RangeAddRangeSumMinMax {
private:
    long long n;
    std::vector<long long> cover;
    std::vector<long long> lazy;
    std::vector<long long> floor;
    std::vector<long long> ceil;

    void pushUp(long long i) {
        cover[i] = cover[2 * i] + cover[2 * i + 1];
        ceil[i] = std::max(ceil[2 * i], ceil[2 * i + 1]);
        floor[i] = std::min(floor[2 * i], floor[2 * i + 1]);
    }

    void makeTag(long long i, long long s, long long t, long long val) {
        cover[i] += val * (t - s + 1);
        floor[i] += val;
        ceil[i] += val;
        lazy[i] += val;
    }

    void pushDown(long long i, long long s, long long m, long long t) {
        if (lazy[i] != 0) {
            cover[2 * i] += lazy[i] * (m - s + 1);
            cover[2 * i + 1] += lazy[i] * (t - m);

            floor[2 * i] += lazy[i];
            floor[2 * i + 1] += lazy[i];

            ceil[2 * i] += lazy[i];
            ceil[2 * i + 1] += lazy[i];

            lazy[2 * i] += lazy[i];
            lazy[2 * i + 1] += lazy[i];

            lazy[i] = 0;
        }

    }

public:
    explicit RangeAddRangeSumMinMax(long long n) : n(n), cover(4 * n, 0), lazy(4 * n, 0), floor(4 * n, 0),
                                                   ceil(4 * n, 0) {}

    void build(const std::vector<long long> &nums) {
        std::vector<std::vector<long long>> stack;
        stack.push_back({0, n - 1, 1});
        while (!stack.empty()) {
            std::vector<long long> last = stack.back();
            stack.pop_back();
            long long s = last[0];
            long long t = last[1];
            long long ind = last[2];
            if (ind >= 0) {
                if (s == t) {
                    makeTag(ind, s, t, nums[s]);
                } else {
                    stack.push_back({s, t, ~ind});
                    long long m = s + (t - s) / 2;
                    stack.push_back({s, m, 2 * ind});
                    stack.push_back({m + 1, t, 2 * ind + 1});
                }
            } else {
                ind = ~ind;
                pushUp(ind);
            }
        }
    }

    long long rangeAdd(long long left, long long right, long long val) {
        std::vector<std::vector<long long>> stack;
        stack.push_back({0, n - 1, 1});
        long long ans = 0;
        while (!stack.empty()) {
            std::vector<long long> last = stack.back();
            stack.pop_back();
            long long s = last[0];
            long long t = last[1];
            long long i = last[2];
            if (i > 0) {
                if (left <= s && t <= right) {
                    makeTag(i, s, t, val);
                    continue;
                }
                long long m = s + (t - s) / 2;
                pushDown(i, s, m, t);
                stack.push_back({s, t, ~i});
                if (left <= m) {
                    stack.push_back({s, m, 2 * i});
                }
                if (right > m) {
                    stack.push_back({m + 1, t, 2 * i + 1});
                }
            } else {
                i = ~i;
                pushUp(i);
            }

        }
        return ans;
    }

    long long rangeSum(long long left, long long right) {
        std::vector<std::vector<long long>> stack;
        stack.push_back({0, n - 1, 1});
        long long ans = 0;
        while (!stack.empty()) {
            std::vector<long long> last = stack.back();
            stack.pop_back();
            long long s = last[0];
            long long t = last[1];
            long long i = last[2];
            if (left <= s && t <= right) {
                ans += cover[i];
                continue;
            }
            long long m = s + (t - s) / 2;
            pushDown(i, s, m, t);
            if (left <= m) {
                stack.push_back({s, m, 2 * i});
            }
            if (right > m) {
                stack.push_back({m + 1, t, 2 * i + 1});
            }
        }
        return ans;
    }

    long long rangeMin(long long left, long long right) {
        std::vector<std::vector<long long>> stack;
        stack.push_back({0, n - 1, 1});
        long long lowest = std::numeric_limits<long long>::max();
        while (!stack.empty()) {
            std::vector<long long> last = stack.back();
            stack.pop_back();
            long long s = last[0];
            long long t = last[1];
            long long i = last[2];
            if (left <= s && t <= right) {
                lowest = std::min(lowest, floor[i]);
                continue;
            }
            long long m = s + (t - s) / 2;
            pushDown(i, s, m, t);
            if (left <= m) {
                stack.push_back({s, m, 2 * i});
            }
            if (right > m) {
                stack.push_back({m + 1, t, 2 * i + 1});
            }
        }
        return lowest;
    }

    long long rangeMax(long long left, long long right) {
        std::vector<std::vector<long long>> stack;
        stack.push_back({0, n - 1, 1});
        long long highest = std::numeric_limits<long long>::min();
        while (!stack.empty()) {
            std::vector<long long> last = stack.back();
            stack.pop_back();
            long long s = last[0];
            long long t = last[1];
            long long i = last[2];
            if (left <= s && t <= right) {
                highest = std::max(highest, ceil[i]);
                continue;
            }
            long long m = s + (t - s) / 2;
            pushDown(i, s, m, t);
            if (left <= m) {
                stack.push_back({s, m, 2 * i});
            }
            if (right > m) {
                stack.push_back({m + 1, t, 2 * i + 1});
            }
        }
        return highest;
    }

    std::vector<long long> get() {
        std::vector<std::vector<long long>> stack;
        stack.push_back({0, n - 1, 1});
        std::vector<long long> nums(n);
        while (!stack.empty()) {
            std::vector<long long> last = stack.back();
            stack.pop_back();
            long long s = last[0];
            long long t = last[1];
            long long i = last[2];
            if (s == t) {
                nums[s] = cover[i];
                continue;
            }
            long long m = s + (t - s) / 2;
            pushDown(i, s, m, t);
            stack.push_back({s, m, 2 * i});
            stack.push_back({m + 1, t, 2 * i + 1});
        }
        return nums;
    }


};


int main() {
    long long t;
    std::cin >> t;
    // https://www.codechef.com/problems/SPR?tab=statement
    while (t--) {
        long long n, k;
        std::cin >> n >> k;
        std::vector<long long> a(n), h(n);
        for (long long i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        for (long long i = 0; i < n; ++i) {
            std::cin >> h[i];
        }

        std::vector<long long> pre(n + 1, 0);
        long long cur = 0;
        pre[0] = 1;
        for (long long i = 0; i < n; ++i) {
            cur += h[i];
            if (cur <= a[i]) {
                pre[i + 1] = 1;
            } else {
                break;
            }
        }

        if (pre[n]) {
            std::cout << "YES" << std::endl;
            continue;
        }
        int res = 0;
        for (long long i = 0; i < n; ++i) {
            if (pre[i] && a[n - 1] - a[i] <= 2 * k) {
                std::cout << "YES" << std::endl;
                res = 1;
                break;
            }
        }
        if (res) {
            continue;
        }
        RangeAddRangeSumMinMax tree(n);
        tree.build(a);
        tree.rangeAdd(n - 1, n - 1, -h[n - 1]);

        std::vector<long long> pre_sum(n+1);

        for (long long i = 0; i < n; ++i) {
            pre_sum[i+1] = pre_sum[i]+h[i];
        }
        long long j = n - 1;
        for (long long i = n - 2; i >= 0; --i) {
            while (j >= 0 && a[i] - a[j] <= 2 * k) {
                --j;
            }
            if (pre[j + 1] && tree.rangeMin(i + 1, n - 1) - pre_sum[j + 1] >= 0) {
                std::cout << "YES" << std::endl;
                res = 1;
                break;
            }
            tree.rangeAdd(i, n - 1, -h[i]);
        }
        if (!res) {
            std::cout << "NO" << std::endl;
        }
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

const long long MAXN = 100005;
const long long INF = LLONG_MAX;
class RangeSetRangeOr {
public:
    RangeSetRangeOr(long long n) : n(n), lazy_tag(4 * n, INF), cover(4 * n, 0) {}

    void build(const vector<long long>& nums) {
        build(1, 0, n - 1, nums);
    }

    vector<long long> get() {
        vector<long long> nums(n);
        get(1, 0, n - 1, nums);
        return nums;
    }

    void range_set(long long left, long long right, long long val) {
        range_set(1, 0, n - 1, left, right, val);
    }

    long long range_or(long long left, long long right) {
        return range_or(1, 0, n - 1, left, right);
    }

private:
    long long n;
    vector<long long> lazy_tag;
    vector<long long> cover;

    void make_tag(long long val, long long i) {
        cover[i] = val;
        lazy_tag[i] = val;
    }

    void push_down(long long i) {
        if (lazy_tag[i] != INF) {
            make_tag(lazy_tag[i], i * 2);
            make_tag(lazy_tag[i], i * 2 + 1);
            lazy_tag[i] = INF;
        }
    }

    void push_up(long long i) {
        cover[i] = cover[i * 2] | cover[i * 2 + 1];
    }

    void build(long long i, long long s, long long t, const vector<long long>& nums) {
        if (s == t) {
            make_tag(nums[s], i);
        } else {
            long long m = (s + t) / 2;
            build(i * 2, s, m, nums);
            build(i * 2 + 1, m + 1, t, nums);
            push_up(i);
        }
    }

    void get(long long i, long long s, long long t, vector<long long>& nums) {
        if (s == t) {
            nums[s] = cover[i];
        } else {
            long long m = (s + t) / 2;
            push_down(i);
            get(i * 2, s, m, nums);
            get(i * 2 + 1, m + 1, t, nums);
        }
    }

    void range_set(long long i, long long s, long long t, long long left, long long right, long long val) {
        if (left <= s && t <= right) {
            make_tag(val, i);
        } else {
            long long m = (s + t) / 2;
            push_down(i);
            if (left <= m) range_set(i * 2, s, m, left, right, val);
            if (right > m) range_set(i * 2 + 1, m + 1, t, left, right, val);
            push_up(i);
        }
    }

    long long range_or(long long i, long long s, long long t, long long left, long long right) {
        if (left <= s && t <= right) {
            return cover[i];
        } else {
            long long m = (s + t) / 2;
            push_down(i);
            long long res = 0;
            if (left <= m) res |= range_or(i * 2, s, m, left, right);
            if (right > m) res |= range_or(i * 2 + 1, m + 1, t, left, right);
            return res;
        }
    }
};
struct DFS {
    vector<long long> start, end, order;
    long long timer;

    void dfs(long long v, const vector<vector<long long>> &adj, vector<bool> &visited) {
        visited[v] = true;
        start[v] = timer++;
        order.push_back(v);
        for (long long u: adj[v]) {
            if (!visited[u]) {
                dfs(u, adj, visited);
            }
        }
        end[v] = timer - 1;
    }

    void gen_bfs_order_iteration(const vector<vector<long long>> &adj, long long root) {
        long long n = adj.size();
        start.resize(n);
        end.resize(n);
        order.clear();
        timer = 0;
        vector<bool> visited(n, false);
        dfs(root, adj, visited);
    }
};

int mai2n() {
    // https://codeforces.com/problemset/problem/620/E
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long n, q;
    cin >> n >> q;
    vector<long long> c(n);
    for (long long i = 0; i < n; ++i) {
        cin >> c[i];
    }

    vector<vector<long long>> dct(n);
    for (long long i = 0; i < n - 1; ++i) {
        long long u, v;
        cin >> u >> v;
        --u;
        --v;
        dct[u].push_back(v);
        dct[v].push_back(u);
    }

    DFS dfs;
    dfs.gen_bfs_order_iteration(dct, 0);
    vector<long long> dfn(n);
    for (long long i = 0; i < n; ++i) {
        dfn[dfs.start[i]] = i;
    }

    RangeSetRangeOr tree(n);
    vector<long long> init_values(n);
    for (long long i = 0; i < n; ++i) {
        init_values[i] = 1LL << c[dfn[i]];
    }
    tree.build(init_values);

    for (long long i = 0; i < q; ++i) {
        long long t;
        cin >> t;
        if (t == 1) {
            long long v, new_c;
            cin >> v >> new_c;
            --v;
            tree.range_set(dfs.start[v], dfs.end[v], 1LL << new_c);
        } else {
            long long v;
            cin >> v;
            --v;
            long long ans = tree.range_or(dfs.start[v], dfs.end[v]);
            cout << bitset<64>(ans).count() << endl;
        }
    }

    return 0;
}
