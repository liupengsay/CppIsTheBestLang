
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>




class SnapshotArray {
public:
    SnapshotArray(long long length) {
        snap_cnt = 0;
        lst = std::vector<std::vector<long long>> (length, {0});
        snap_ids = std::vector<std::vector<long long>> (length, {0});

    }

    void set(long long index, long long val) {
        lst[index].push_back(val);
        snap_ids[index].push_back(val);
    }

    long long snap() {
        snap_cnt++;
        return snap_cnt - 1;
    }

    long long get(long long index, long long snap_id) {
        long long i = std::upper_bound(snap_ids[index].begin(), snap_ids[index].end(), snap_id) - snap_ids[index].begin();
        long long ans = lst[index][i-1];
        return ans;
    }
private:
    long long snap_cnt=0;
    std::vector<std::vector<long long>> lst;
    std::vector<std::vector<long long>> snap_ids;
};