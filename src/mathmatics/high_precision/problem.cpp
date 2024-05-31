class Solution {
public:
    int minCostToEqualizeArray(std::vector<int>& nums, int cost1, int cost2) {
        __int128_t n = nums.size();
        __int128_t mod = 1e9 + 7;
        __int128_t ceil = *std::max_element(nums.begin(), nums.end());
        __int128_t floor = *std::min_element(nums.begin(), nums.end());

        if (cost2 >= 2 * cost1) {
            __int128_t ans = 0;
            for (__int128_t num : nums) {
                ans += (ceil - num)*cost1;
                ans %= mod;
            }
            return ans;
        }
        __int128_t c1 = static_cast<__int128_t>(cost1);
        __int128_t c2 = static_cast<__int128_t>(cost2);
        __int128_t ans = -1;
        __int128_t tot = 0;
        for (__int128_t num : nums) {
            tot += num;
            ans %= mod;
        }
        for (__int128_t x = ceil; x <= ceil * 2; x++) {
            __int128_t s = x * n - tot;
            __int128_t mx = x - floor;
            __int128_t m = std::min(mx, s - mx);
            __int128_t cur = (s - 2 * m) * c1 + m * c2;
            if (mx * 2 <= s) {
                cur = std::min(cur, (s / 2) * c2 + (s % 2) * c1);
            }
            if (cur<ans || ans==-1){
                ans = cur;
            }
            else{
                break;
            }
        }
        __int128_t res = ans % mod;
        return res;
    }
};