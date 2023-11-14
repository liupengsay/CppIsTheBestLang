#include <vector>
#include <limits>
#include "template.cpp"


class Solution {
public:
    static int lc_1334(int n, std::vector<std::vector<int>>& edges, int distanceThreshold) {
        std::vector<std::vector<std::pair<int, int>>> dct(n);
        for (const auto& edge : edges) {
            int i = edge[0];
            int j = edge[1];
            int w = edge[2];
            dct[i].emplace_back(j, w);
            dct[j].emplace_back(i, w);
        }

        float res = std::numeric_limits<float>::max();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
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
