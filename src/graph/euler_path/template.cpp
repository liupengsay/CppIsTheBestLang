#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <algorithm>
#include <set>

class UnDirectedEulerPath {
public:
    UnDirectedEulerPath(int n, const std::vector<std::pair<int, int>>& pairs) : n(n), pairs(pairs) {
        get_euler_path();
    }

    bool has_euler_path() const {
        return exist;
    }

private:
    int n;
    std::vector<std::pair<int, int>> pairs;
    std::vector<int> paths;
    std::vector<int> nodes;
    bool exist = false;

    void get_euler_path() {
        std::vector<int> degree(n, 0);
        std::vector<std::unordered_map<int, int>> edge(n);
        for (const auto& p : pairs) {
            int i = p.first, j = p.second;
            degree[i]++;
            degree[j]++;
            edge[i][j]++;
            edge[j][i]++;
        }

        std::vector<std::deque<int>> edge_dct(n);
        for (int i = 0; i < n; ++i) {
            for (const auto& e : edge[i]) {
                edge_dct[i].push_back(e.first);
            }
            std::sort(edge_dct[i].begin(), edge_dct[i].end());
        }

        std::vector<int> starts;
        int zero = 0;
        for (int i = 0; i < n; ++i) {
            if (degree[i] % 2 == 1) {
                starts.push_back(i);
            } else {
                zero++;
            }
        }

        if (starts.size() != 2) {
            if (zero != n) {
                return;
            }
            starts = {0};
        }

        std::vector<int> stack = {starts[0]};
        while (!stack.empty()) {
            int current = stack.back();
            int next_node = -1;
            while (!edge_dct[current].empty()) {
                int nex = edge_dct[current].front();
                if (edge[current][nex] == 0) {
                    edge_dct[current].pop_front();
                    continue;
                }
                if (edge[current][nex] > 0) {
                    edge[current][nex]--;
                    edge[nex][current]--;
                    next_node = nex;
                    stack.push_back(next_node);
                    break;
                }
            }
            if (next_node == -1) {
                nodes.push_back(current);
                if (stack.size() > 1) {
                    int pre = stack[stack.size() - 2];
                    paths.push_back(current);
                }
                stack.pop_back();
            }
        }
        std::reverse(paths.begin(), paths.end());
        std::reverse(nodes.begin(), nodes.end());

        if (nodes.size() == pairs.size() + 1) {
            exist = true;
        }
    }
};

char a[12],b[12];

class Solution {
public:
    static void main() {
        std::vector<std::string> pairs;
        while(scanf("%s%s",a,b)!=EOF){
            pairs.push_back(static_cast<std::string>(a));
            pairs.push_back(static_cast<std::string>(b));
        }

        std::set<std::string> nodes_set(pairs.begin(), pairs.end());
        std::unordered_map<std::string, int> ind;
        int idx = 0;
        for (const auto& node : nodes_set) {
            ind[node] = idx++;
        }

        std::vector<std::pair<int, int>> pairs_idx;
        for (size_t i = 0; i < pairs.size(); i += 2) {
            pairs_idx.emplace_back(ind[pairs[i]], ind[pairs[i + 1]]);
        }

        UnDirectedEulerPath euler(static_cast<int>(ind.size()), pairs_idx);
        std::cout << (euler.has_euler_path() ? "Possible" : "Impossible") << std::endl;
    }
};

int main() {
    Solution::main();
    return 0;
}
