#include <iostream>
#include <vector>
#include <queue>
#include <limits>


class Dijkstra {
public:
    static std::vector<float> get_shortest_path(const std::vector<std::vector<std::pair<long long, long long>>> &dct, long long src) {
        long long n = dct.size();
        std::vector<float> dis(n, std::numeric_limits<float>::infinity());
        std::priority_queue<std::pair<float, long long>, std::vector<std::pair<float, long long>>, std::greater<>> pq;
        pq.emplace(0, src);
        dis[src] = 0;

        while (!pq.empty()) {
            float d = pq.top().first;
            long long i = pq.top().second;
            pq.pop();

            if (dis[i] < d) {
                continue;
            }

            for (const auto &edge: dct[i]) {
                long long j = edge.first;
                long long w = edge.second;
                float dj = w + d;
                if (dj < dis[j]) {
                    dis[j] = dj;
                    pq.emplace(dj, j);
                }
            }
        }

        return dis;
    }
};