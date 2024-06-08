#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>


int bit_length(int num) {
    int length = 0;
    while (num > 0) {
        num >>= 1;
        length++;
    }
    return length;
}

class SparseTable {
public:
    SparseTable(const std::vector<int>& lst, int (*fun)(int, int)) {
        int n = lst.size();
        this->fun = fun;
        this->n = n;

        bit.resize(n + 1);
        int l = 1, r = 2, v = 0;
        while (true) {
            int flag = 0;
            for (int i = l; i < r; ++i) {
                if (i >= n + 1) {
                    flag = 1;
                    break;}
                bit[i] = v;
            }
            if (!flag) {
                l *= 2;
                r *= 2;
                ++v;
                continue;
            }
            break;
        }

        for (int i = 0; i <= n; ++i) {
            assert(bit[i] == ((i == 0) ? 0 : bit_length(i) - 1));
        }

        st.resize(v + 1, std::vector<int>(n));
        st[0] = lst;
        for (int i = 1; i <= v; ++i) {
            for (int j = 0; j <= n - (1 << i); ++j) {
                st[i][j] = fun(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int left, int right) {
        assert(0 <= left && left <= right && right < n);
        int pos = bit[right - left + 1];
        return fun(st[pos][left], st[pos][right - (1 << pos) + 1]);
    }

private:
    std::vector<int> bit;
    std::vector<std::vector<int>> st;
    int n;
    int (*fun)(int, int);
};

int main() {
    std::vector<int> nums = {9, 3, 1, 7, 5, 6, 0, 8};
    SparseTable st(nums, [](int a, int b) { return std::max(a, b); });

    std::vector<std::vector<int>> queries = {{1, 6}, {1, 5}, {2, 7}, {2, 6}, {1, 8}, {4, 8}, {3, 7}, {1, 8}};
    std::vector<int> expected = {9, 9, 7, 7, 9, 8, 7, 9};
    for (size_t i = 0; i < queries.size(); ++i) {
        assert(st.query(queries[i][0] - 1, queries[i][1] - 1) == expected[i]);
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
