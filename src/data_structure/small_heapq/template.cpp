class FindMedian {
private:
    priority_queue<int, vector<int>, greater<int>>  small; // Max heap
    priority_queue<int, vector<int>, greater<int>> big; // Min heap
    unordered_map<int, int> big_dct;
    unordered_map<int, int> small_dct;
    int big_cnt = 0;
    int small_cnt = 0;

    void deleteNum() {
        while (!small.empty() && small_dct[-small.top()] == 0) {
            small.pop();
        }
        while (!big.empty() && big_dct[big.top()] == 0) {
            big.pop();
        }
    }

    void change() {
        deleteNum();
        while (!small.empty() && !big.empty() && -small.top() > big.top()) {
            small_dct[-small.top()]--;
            big_dct[-small.top()]++;
            small_cnt--;
            big_cnt++;
            big.push(-small.top());
            small.pop();
            deleteNum();
        }
    }

    void balance() {
        deleteNum();
        while (small_cnt > big_cnt) {
            small_dct[-small.top()]--;
            big_dct[-small.top()]++;
            big.push(-small.top());
            small.pop();
            small_cnt--;
            big_cnt++;
            deleteNum();
        }

        while (small_cnt < big_cnt - 1) {
            big_dct[big.top()]--;
            small_dct[big.top()]++;
            small.push(-big.top());
            big.pop();
            big_cnt--;
            small_cnt++;
            deleteNum();
        }
    }

public:
    void add(int num) {
        if (big.empty() || big.top() < num) {
            big_dct[num]++;
            big.push(num);
            big_cnt++;
        } else {
            small_dct[num]++;
            small.push(-num);
            small_cnt++;
        }
        change();
        balance();
    }

    void remove(int num) {
        change();
        balance();
        if (big_dct[num] > 0) {
            big_cnt--;
            big_dct[num]--;
        } else {
            small_cnt--;
            small_dct[num]--;
        }
        change();
        balance();
    }

    int findMedian() {
        change();
        balance();
        if (big_cnt == small_cnt) {
            return (-small.top() + big.top()) / 2;
        }
        return big.top();
    }
};
