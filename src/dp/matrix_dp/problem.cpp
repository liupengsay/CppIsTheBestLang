#include <iostream>
#include <vector>

const int mod = 1000000;
int a, b, c, d;

int memo[2][39][39][39][5][5];

const std::vector<std::string> name = {"A1", "A2", "B1", "B2", "XX"};

int dfs(int x1, int x2, int x3, int x4) {
    for (int p1 = 0; p1 < 5; ++p1) {
        for (int p2 = 0; p2 < 5; ++p2) {
            memo[0][0][0][0][p1][p2] = 1;
        }
    }

    int order = 0;
    for (int i = 1; i <= x1 + x2 + x3 + x4; ++i) {
        for (int j1 = 0; j1 <= x1; ++j1) {
            for (int j2 = 0; j2 <= x2; ++j2) {
                if (j1 + j2 > i) {
                    continue;
                }
                for (int j3 = 0; j3 <= x3; ++j3) {
                    int j4 = i - j1 - j2 - j3;
                    if (j4 < 0) {
                        continue;
                    }
                    for (int p1 = 0; p1 < 5; ++p1) {
                        for (int p2 = 0; p2 < 5; ++p2) {
                            int cur_val = 0;
                            if (j1 > 0 && (name[p1][0] != 'A' || name[p2][0] != 'A') &&
                                (name[p1][1] != '1' || name[p2][1] != '1')) {
                                cur_val += memo[order][j1 - 1][j2][j3][p2][0];
                                cur_val %= mod;
                            }
                            if (j2 > 0 && (name[p1][0] != 'A' || name[p2][0] != 'A') &&
                                (name[p1][1] != '2' || name[p2][1] != '2')) {
                                cur_val += memo[order][j1][j2 - 1][j3][p2][1];
                                cur_val %= mod;
                            }
                            if (j3 > 0 && (name[p1][0] != 'B' || name[p2][0] != 'B') &&
                                (name[p1][1] != '1' || name[p2][1] != '1')) {
                                cur_val += memo[order][j1][j2][j3 - 1][p2][2];
                                cur_val %= mod;
                            }
                            if (j4 > 0 && (name[p1][0] != 'B' || name[p2][0] != 'B') &&
                                (name[p1][1] != '2' || name[p2][1] != '2')) {
                                cur_val += memo[order][j1][j2][j3][p2][3];
                                cur_val %= mod;
                            }
                            memo[1 - order][j1][j2][j3][p1][p2] = cur_val;
                        }
                    }
                }
            }
        }
        order = 1 - order;
    }
    return memo[order][x1][x2][x3][4][4];
}
// https://www.luogu.com.cn/problem/P3448
int main() {
    std::cin >> a >> b >> c >> d;
    std::cout << dfs(a, b, c, d) << std::endl;
    return 0;
}
