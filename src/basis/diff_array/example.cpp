
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
        vector<vector<long long>> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        PreFixSumMatrix pfsm(mat);
        assert(pfsm.query(0, 0, 0, 0) == 1);
        assert(pfsm.query(0, 0, 1, 1) == 12);
        assert(pfsm.query(1, 1, 2, 2) == 28);
        assert(pfsm.query(0, 0, 2, 2) == 45);
        cout << "PreFixSumMatrixTest Done" << endl;
    }


    static void DiffArrayTest() {
        // 测试用例
        vector<vector<long long>> shifts = {{1, 3, 2}, {2, 4, 3}, {0, 2, -2}};
        vector<long long> lst = {1, 2, 3, 4, 5};
        long long n = static_cast<long long>(lst.size());
        vector<long long> diff = DiffArray::get_diff_array(n, shifts);
        vector<long long> pre = DiffArray::get_array_prefix_sum(n, diff);

        assert(DiffArray::get_array_range_sum(pre, 0, 3) == 6);
        assert(DiffArray::get_array_range_sum(pre, 1, 2) == 3);
        assert( DiffArray::get_array_range_sum(pre, 0, 4) == 9);


        long long n2 = 3;
        vector<vector<long long>> shifts2 = {{0, 1, 1}, {1, 2, -1}};
        vector<long long> diff2 = DiffArray::get_diff_array(n2, shifts2);
        vector<long long> target2 = {1, 0, -1};
        assert(diff2 == target2);

        long long n3 = 3;
        vector<long long> shifts3 = {1, 2, 3};
        vector<long long> diff3 = DiffArray::get_array_prefix_sum(n3, shifts3);
        vector<long long> target3 = {0, 1, 3, 6};
        assert(diff3 == target3);

        long long left = 1;
        long long right = 2;

        assert(DiffArray::get_array_range_sum(diff3, left, right) == 5);
        cout << "PreFixSumMatrixTest Done" << endl;
    }


    static void DiffMatrixTest() {
        // 测试用例
        vector<vector<long long>> shifts = {{1, 2, 1, 2, 1},
                                      {2, 3, 2, 3, 1},
                                      {2, 2, 2, 2, 2},
                                      {1, 1, 3, 3, 3}};
        vector<vector<long long>> target = {{1, 1, 3},
                                      {1, 4, 1},
                                      {0, 1, 1}};
        // 测试 get_diff_matrix 方法
        vector<vector<long long>> diff = DiffMatrix::get_diff_matrix(3, 3, shifts);
        assert(diff == target);

        // 测试 get_diff_matrix2 方法
        for (auto &shift: shifts) {
            for (long long i = 0; i < 4; i++) {
                shift[i] -= 1;
            }
        }
        vector<vector<long long>> diff2 = DiffMatrix::get_diff_matrix2(3, 3, shifts);
        assert(diff2 == target);

        // 使用随机生成测试
        random_device rd;
        mt19937 gen(rd());

        for (long long t = 0; t < 10; t++) {
            long long m = uniform_long long_distribution<long long>(1, 100)(gen);
            long long n = uniform_long long_distribution<long long>(1, 100)(gen);

            vector<vector<long long>> ans(m, vector<long long>(n, 0));
            vector<vector<long long>> shifts2;
            for (long long i = 0; i < 100; i++) {
                long long xa = uniform_long long_distribution<long long>(1, m)(gen);
                long long xb = uniform_long long_distribution<long long>(xa, m)(gen);

                long long ya = uniform_long long_distribution<long long>(1, n)(gen);
                long long yb = uniform_long long_distribution<long long>(ya, n)(gen);

                long long x = uniform_long long_distribution<long long>(-100, 100)(gen);
                shifts2.push_back({xa, xb, ya, yb, x});

                for (long long a = xa - 1; a < xb; a++) {
                    for (long long b = ya - 1; b < yb; b++) {
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