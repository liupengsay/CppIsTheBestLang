#include <iostream>
#include <vector>
#include <set>
#define int128 __int128_t

std::vector<long long> read_list_ints_minus_one(long long n) {
    std::vector<long long> res(n);
    for (long long i = 0; i < n; ++i) {
        std::cin >> res[i];
        --res[i];
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n;
    std::cin >> n;

    std::vector<std::vector<std::pair<long long, long long>>> dct(n);
    for (long long _ = 0; _ < n - 1; ++_) {
        std::vector<long long> vals = read_list_ints_minus_one(3);
        long long i = vals[0], j = vals[1];
        long long ll = vals[2] + 1;
        dct[i].emplace_back(ll, j);
        dct[j].emplace_back(ll, i);
    }

    std::vector<long long> dis(n, 0);
    std::vector<long long> parent(n, -1);
    std::vector<long long> stack(1, 0);
    std::vector<long long> visit(n, 0);

    while (!stack.empty()) {
        long long x = stack.back();
        stack.pop_back();
        for (const auto& p : dct[x]) {
            long long y = p.second;
            long long w = p.first;
            if (y != parent[x]) {
                parent[y] = x;
                stack.push_back(y);
                dis[y] = dis[x] + w;
            }
        }
    }

    std::set<std::pair<long long, long long>> lst;
    for (long long x = 1; x < n; ++x) {
        lst.emplace(dis[x], x);
    }

    long long ans = 0;

    for (long long i = 0; i < n; ++i) {
        if (lst.empty()) {
            std::cout << ans << "\n";
            continue;
        }

        auto va2l = *lst.rbegin();
        lst.erase(va2l);
        long long dd = va2l.first;
        long long ii = va2l.second;
        ans += dd * 2;

        stack.clear();
        visit[ii] = 1;
        while (parent[ii] != -1 && !visit[parent[ii]]) {
            long long j = parent[ii];
            if (dis[j]) {
                lst.erase({dis[j], j});
            }
            visit[j] = 1;
            stack.push_back(j);
            ii = j;
        }

        for (long long w: stack) {
            dis[w] = 0;
        }

        while (!stack.empty()) {
            long long x = stack.back();
            stack.pop_back();
            for (const auto& p : dct[x]) {
                long long y = p.second;
                long long ww = p.first;
                if (!visit[y] && y != parent[x]) {
                    if (dis[y]) {
                        lst.erase({dis[y], y});
                    }
                    dis[y] = dis[x] + ww;
                    stack.push_back(y);
                    if (dis[y]) {
                        lst.emplace(dis[y], y);
                    }
                }
            }
        }
        std::cout << ans << "\n";
    }

    return 0;
}
