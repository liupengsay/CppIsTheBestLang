#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

        vector<int> ans;
        int val = 0;
        int cnt = 0;
        for (int num: nums){
            if (num==val){
                cnt+=1;
            }
            if (num>val){
                val= num;
                cnt =1;
            }
        }
        for (int _=0;_<cnt;_++){
            ans.push_back(val);
        }
        vector<int> rest;
        for (int num: nums){
            if (num!=val){
                rest.push_back(num);
            }
        }
        while (!rest.empty()) {
            int v = 0;
            int pre = ans.back();
            vector<int> nex;
            for (int num : rest) {
                v = max(v, num & pre);
            }
            for (int num : rest) {
                if ((num & pre) == v){
                    ans.push_back(v);
                }
                else{
                    nex.push_back(num);
                }
            }
            rest.swap(nex);
        }

        for (int v : ans) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}
