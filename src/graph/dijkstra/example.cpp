
#include <vector>
#include <cassert>
#include <random>
#include "problem.cpp"


class TestGeneral {
public:
    static void DijkstraTest() {
        std::vector<std::vector<std::pair<int, int>>> dct = {{{1, 1}, {2, 4}},
                                                             {{2, 2}},
                                                             {},
                                                             {}};
        std::vector<float> result = Dijkstra::get_shortest_path(dct, 0);
        std::vector<float> expected = {0, 1, 3, std::numeric_limits<float>::infinity()};
        assert(result == expected);
    }
};


int main() {
    TestGeneral::DijkstraTest();
    return 0;
}