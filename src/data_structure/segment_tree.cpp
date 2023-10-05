#include <iostream>
#include <vector>

using namespace std;

class SegmentTreeRangeUpdateXORSum {
private:
    int n;
    vector<int> cover;
    vector<int> lazy;

public:
    SegmentTreeRangeUpdateXORSum(int n) : n(n), cover(4 * n), lazy(4 * n) {}

    void build(vector<int>& nums) {
        buildTree(nums, 0, n - 1, 1);
    }

    void buildTree(vector<int>& nums, int s, int t, int i) {
        if (s == t) {
            cover[i] = nums[s];
            return;
        }

        int m = s + (t - s) / 2;
        buildTree(nums, s, m, 2 * i);
        buildTree(nums, m + 1, t, 2 * i + 1);

        cover[i] = cover[2 * i] + cover[2 * i + 1];
    }

    void pushDown(int i, int s, int m, int t) {
        if (lazy[i] != 0) {
            cover[2 * i] = m - s + 1 - cover[2 * i];
            cover[2 * i + 1] = t - m - cover[2 * i + 1];

            lazy[2 * i] ^= lazy[i];
            lazy[2 * i + 1] ^= lazy[i];

            lazy[i] = 0;
        }
    }

    void update(int left, int right, int s, int t, int val, int i) {
        if (left <= s && t <= right) {
            cover[i] = t - s + 1 - cover[i];
            lazy[i] ^= val;
            return;
        }

        int m = s + (t - s) / 2;
        pushDown(i, s, m, t);

        if (left <= m) {
            update(left, right, s, m, val, 2 * i);
        }
        if (right > m) {
            update(left, right, m + 1, t, val, 2 * i + 1);
        }

        cover[i] = cover[2 * i] + cover[2 * i + 1];
    }

    int querySum(int left, int right, int s, int t, int i) {
        if (left <= s && t <= right) {
            return cover[i];
        }

        int m = s + (t - s) / 2;
        pushDown(i, s, m, t);

        int sum = 0;
        if (left <= m) {
            sum += querySum(left, right, s, m, 2 * i);
        }
        if (right > m) {
            sum += querySum(left, right, m + 1, t, 2 * i + 1);
        }

        return sum;
    }
};

class SegBitSet {
private:
    int val;

public:
    SegBitSet() : val(0) {}

    void update(int b, int c) {
        int p = ((1 << (c + 1)) - (1 << b));
        val ^= p;
    }

    int query(int b, int c) {
        int p = ((1 << (c + 1)) - (1 << b));
        int count = 0;
        int temp = val & p;
        while (temp) {
            count += temp & 1;
            temp >>= 1;
        }
        return count;
    }
};

class Solution {
public:
    void main() {
        int n;
        cin >> n;

        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }

        vector<SegmentTreeRangeUpdateXORSum> tree(22, SegmentTreeRangeUpdateXORSum(n));
        for (int j = 0; j < 22; j++) {
            vector<int> lst(n);
            for (int i = 0; i < n; i++) {
                lst[i] = (nums[i] & (1 << j)) ? 1 : 0;
            }
            tree[j].build(lst);
        }

        int q;
        cin >> q;
        for (int k = 0; k < q; k++) {
            int type;
            cin >> type;
            if (type == 1) {
                int ll, rr;
                cin >> ll >> rr;
                ll--;
                rr--;

                int ans = 0;
                for (int j = 0; j < 22; j++)```cpp
                {
                    int cnt = tree[j].querySum(ll, rr, 0, n - 1, 1);
                    ans += cnt * (1 << j);
                }

                cout << ans << endl;
            } else {
                int p, b, c;
                cin >> p >> b >> c;
                p--;

                for (int j = 0; j < 22; j++) {
                    if ((nums[p] & (1 << j)) != 0) {
                        tree[j].update(p, p, 0, n - 1, 1, b);
                    }
                }

                nums[p] = c;
                for (int j = 0; j < 22; j++) {
                    if ((nums[p] & (1 << j)) != 0) {
                        tree[j].update(p, p, 0, n - 1, 1, b);
                    } else {
                        tree[j].update(p, p, 0, n - 1, 0, b);
                    }
                }
            }
        }
    }
};

int main() {
    Solution solution;
    solution.main();
    return 0;
}