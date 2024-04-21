
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>


class Solution {
public:
    int combinationSum4(std::vector<int> &nums, int target) {
        std::vector<int> dp(target + 1);
        dp[0] = 1;
        for (int i = 1; i <= target; i++) {
            for (int &num: nums) {
                if (num <= i && dp[i - num] < INT_MAX - dp[i])
                {
                    dp[i] += dp[i - num];
                }
            }
        }
        return dp[target];
    }
};