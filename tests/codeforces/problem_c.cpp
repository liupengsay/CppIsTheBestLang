#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>

using namespace std;


string make_tuple(int a, int b, int c) {
    string st = to_string(a) + "," + to_string(b) + "," + to_string(c);
    return st;
};

int main() {
    int t;
    cin >> t;


    while (t--) {
        int n;
        cin >> n;
        vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            cin >> nums[i];
        }

        unordered_map<string, int> dct;
        long long ans = 0;
        for (int i = 0; i < n - 2; ++i) {
            int a = nums[i];
            int b = nums[i + 1];
            int c = nums[i + 2];

            ans += dct[make_tuple(-1, b, c)];
            ans += dct[make_tuple(a, -1, c)];
            ans += dct[make_tuple(a, b, -1)];
            ans -= dct[make_tuple(a, b, c)] * 3;

            dct[make_tuple(a, b, c)]++;
            dct[make_tuple(-1, b, c)]++;
            dct[make_tuple(a, -1, c)]++;
            dct[make_tuple(a, b, -1)]++;
        }

        cout << ans << endl;
    }

    return 0;
}
