#include <vector>
#include <limits>
#include "template.cpp"


class Solution {
public:
    static long long lc_1334(long long n, std::vector<std::vector<long long>>& edges, long long distanceThreshold) {
        std::vector<std::vector<std::pair<long long, long long>>> dct(n);
        for (const auto& edge : edges) {
            long long i = edge[0];
            long long j = edge[1];
            long long w = edge[2];
            dct[i].emplace_back(j, w);
            dct[j].emplace_back(i, w);
        }

        float res = std::numeric_limits<float>::max();
        long long ans = 0;
        for (long long i = 0; i < n; ++i) {
            std::vector<float> dis = Dijkstra::get_shortest_path(dct, i);
            float cur = 0;
            for (float distance : dis) {
                if (distance <= distanceThreshold) {
                    cur++;
                }
            }
            if (cur <= res) {
                res = cur;
                ans = i;
            }
        }

        return ans;
    }
};
