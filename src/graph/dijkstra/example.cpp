
#include <vector>
#include <cassert>
#include <random>
#include "problem.cpp"


class TestGeneral {
public:
    static void DijkstraTest() {
        std::vector<std::vector<std::pair<long long, long long>>> dct = {{{1, 1}, {2, 4}},
                                                             {{2, 2}},
                                                             {},
                                                             {}};
        std::vector<float> result = Dijkstra::get_shortest_path(dct, 0);
        std::vector<float> expected = {0, 1, 3, std::numeric_limits<float>::infinity()};
        assert(result == expected);
    }

    static void SolutionTest() {

        long long n = 4;
        std::vector<std::vector<long long>> dct = {{0,1,3},{1,2,1},{1,3,4},{2,3,1}};
        long long result = Solution::lc_1334(n, dct, 4);
        assert(result == 3);

    }
};


int main() {
    TestGeneral::DijkstraTest();
    TestGeneral::SolutionTest();
    return 0;
}