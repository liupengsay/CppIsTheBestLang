
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;  // Read number of test cases

    unordered_map<char, int> dct = {{'N', 1}, {'S', -1}, {'E', 1}, {'W', -1}};

    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        int y = 0, x = 0;
        for (char w : s) {
            if (w == 'N' || w == 'S') {
                y += dct[w];
            } else if (w == 'E' || w == 'W') {
                x += dct[w];
            }
        }

        if (x % 2 != 0 || y % 2 != 0) {
            cout << "NO" << endl;
            continue;
        }
        if (x == 0 && y == 0 && n <= 2) {
            cout << "NO" << endl;
            continue;
        }

        vector<char> ans;
        int x0 = 0, y0 = 0;

        if (x == 0 && y == 0) {
            ans.push_back('R');

            if (s[0] == 'E' || s[0] == 'W') {
                x0 += dct[s[0]];
            } else {
                y0 += dct[s[0]];
            }
            s = s.substr(1);
        }

        for (char w : s) {
            if (w == 'N' || w == 'S') {
                if ((w == 'N' && y0 < y / 2) || (w == 'S' && y0 > y / 2)) {
                    ans.push_back('R');
                    y0 += (w == 'N' ? 1 : -1);
                } else {
                    ans.push_back('H');
                }
            } else if (w == 'E' || w == 'W') {
                if ((w == 'E' && x0 < x / 2) || (w == 'W' && x0 > x / 2)) {
                    ans.push_back('R');
                    x0 += (w == 'E' ? 1 : -1);
                } else {
                    ans.push_back('H');
                }
            }
        }

        if (find(ans.begin(), ans.end(), 'R') != ans.end() && find(ans.begin(), ans.end(), 'H') != ans.end()) {
            for (char c : ans) {
                cout << c;
            }
            cout << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
