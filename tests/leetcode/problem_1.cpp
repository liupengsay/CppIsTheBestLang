
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>




class SnapshotArray {
public:
    SnapshotArray(int length) {
        snap_cnt = 0;
        lst = std::vector<std::vector<int>> (length, {0});
        snap_ids = std::vector<std::vector<int>> (length, {0});

    }

    void set(int index, int val) {
        lst[index].push_back(val);
        snap_ids[index].push_back(val);
    }

    int snap() {
        snap_cnt++;
        return snap_cnt - 1;
    }

    int get(int index, int snap_id) {
        int i = std::upper_bound(snap_ids[index].begin(), snap_ids[index].end(), snap_id) - snap_ids[index].begin();
        int ans = lst[index][i-1];
        return ans;
    }
private:
    int snap_cnt=0;
    std::vector<std::vector<int>> lst;
    std::vector<std::vector<int>> snap_ids;
};