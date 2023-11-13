
#include <vector>
#include <iostream>
#include <cassert>
#include <random>
#include "template.cpp"

using namespace std;

class TestGeneral {
public:
    static void PreFixSumMatrixTest() {
        // 测试用例
        vector<vector<int>> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        PreFixSumMatrix pfsm(mat);
        assert(pfsm.query(0, 0, 0, 0) == 1);
        assert(pfsm.query(0, 0, 1, 1) == 12);
        assert(pfsm.query(1, 1, 2, 2) == 28);
        assert(pfsm.query(0, 0, 2, 2) == 45);
        cout << "PreFixSumMatrixTest Done" << endl;
    }


    static void DiffArrayTest() {
        // 测试用例
        vector<vector<int>> shifts = {{1, 3, 2}, {2, 4, 3}, {0, 2, -2}};
        vector<int> lst = {1, 2, 3, 4, 5};
        int n = static_cast<int>(lst.size());
        vector<int> diff = DiffArray::get_diff_array(n, shifts);
        vector<int> pre = DiffArray::get_array_prefix_sum(n, diff);

        assert(DiffArray::get_array_range_sum(pre, 0, 3) == 6);
        assert(DiffArray::get_array_range_sum(pre, 1, 2) == 3);
        assert( DiffArray::get_array_range_sum(pre, 0, 4) == 9);


        int n2 = 3;
        vector<vector<int>> shifts2 = {{0, 1, 1}, {1, 2, -1}};
        vector<int> diff2 = DiffArray::get_diff_array(n2, shifts2);
        vector<int> target2 = {1, 0, -1};
        assert(diff2 == target2);

        int n3 = 3;
        vector<int> shifts3 = {1, 2, 3};
        vector<int> diff3 = DiffArray::get_array_prefix_sum(n3, shifts3);
        vector<int> target3 = {0, 1, 3, 6};
        assert(diff3 == target3);

        int left = 1;
        int right = 2;

        assert(DiffArray::get_array_range_sum(diff3, left, right) == 5);
        cout << "PreFixSumMatrixTest Done" << endl;
    }


    static void DiffMatrixTest() {
        // 测试用例
        vector<vector<int>> shifts = {{1, 2, 1, 2, 1},
                                      {2, 3, 2, 3, 1},
                                      {2, 2, 2, 2, 2},
                                      {1, 1, 3, 3, 3}};
        vector<vector<int>> target = {{1, 1, 3},
                                      {1, 4, 1},
                                      {0, 1, 1}};
        // 测试 get_diff_matrix 方法
        vector<vector<int>> diff = DiffMatrix::get_diff_matrix(3, 3, shifts);
        assert(diff == target);

        // 测试 get_diff_matrix2 方法
        for (auto &shift: shifts) {
            for (int i = 0; i < 4; i++) {
                shift[i] -= 1;
            }
        }
        vector<vector<int>> diff2 = DiffMatrix::get_diff_matrix2(3, 3, shifts);
        assert(diff2 == target);

        // 使用随机生成测试
        random_device rd;
        mt19937 gen(rd());

        for (int t = 0; t < 10; t++) {
            int m = uniform_int_distribution<int>(1, 100)(gen);
            int n = uniform_int_distribution<int>(1, 100)(gen);

            vector<vector<int>> ans(m, vector<int>(n, 0));
            vector<vector<int>> shifts2;
            for (int i = 0; i < 100; i++) {
                int xa = uniform_int_distribution<int>(1, m)(gen);
                int xb = uniform_int_distribution<int>(xa, m)(gen);

                int ya = uniform_int_distribution<int>(1, n)(gen);
                int yb = uniform_int_distribution<int>(ya, n)(gen);

                int x = uniform_int_distribution<int>(-100, 100)(gen);
                shifts2.push_back({xa, xb, ya, yb, x});

                for (int a = xa - 1; a < xb; a++) {
                    for (int b = ya - 1; b < yb; b++) {
                        ans[a][b] += x;
                    }
                }
                assert(DiffMatrix::get_diff_matrix(m, n, shifts2) == ans);
            }
        }
        cout << "DiffMatrixTest Done" << endl;
    }

};


int main() {
    TestGeneral::PreFixSumMatrixTest();
    TestGeneral::DiffArrayTest();
    TestGeneral::DiffMatrixTest();
    return 0;
};