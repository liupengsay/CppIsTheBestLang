"""

算法：最长上升（或不降）子序列 Longest Increasing Subsequence（LIS）Longest Decreasing Subsequence（LDS）统称 Longest Monotonic Subsequence（LMS）
最长单调递增子序列（严格上升）：<
最长单调不减子序列（不降）：<=
最长单调递减子序列（严格下降）：>
最长单调不增子序列（不升）：>=
对于数组来说，正数反可以将后两个问题3和4转换为前两个问题1和2进行解决，可以算全局的最长单调子序列，也可以计算前后缀的最长单调子序列
dilworth定理：
分成不下降子序列最小组数等于最大上升子序列的长度，分成不上升子序列最小组数等于最大下降子序列的长度；
反过来，分成上升子序列最小组数等于最大不上升的长度，分成下降子序列最小组数等于最大不下降子序列的长度。

参考题目：
===================================力扣===================================
354. 俄罗斯套娃信封问题（https://leetcode.cn/problems/russian-doll-envelopes/）经典二维偏序最长递增子序列问题
673. 最长递增子序列的个数（https://leetcode.cn/problems/number-of-longest-increasing-subsequence/）经典O(n^2)与O(nlogn)的LIS计数问题做法模板题
1092. 最短公共超序列（https://leetcode.cn/problems/shortest-common-supersequence/）经典利用LIS求LCS的最短公共超序列
1671. 得到山形数组的最少删除次数（https://leetcode.cn/problems/minimum-number-of-removals-to-make-mountain-array/）经典山脉数组LIS变形问题
2111. 使数组 K 递增的最少操作次数（https://leetcode.cn/problems/minimum-operations-to-make-the-array-k-increasing/）分成 K 组计算每组的最长递增子序列
面试题 17.08. 马戏团人塔（https://leetcode.cn/problems/circus-tower-lcci/）按照两个维度贪心排序后，计算最长递增子序列
最长递增子序列（https://www.nowcoder.com/questionTerminal/30fb9b3cab9742ecae9acda1c75bf927?orderByHotValue=1&questionTypes=000100&difficulty=11111&mutiTagIds=593&page=10&onlyReference=false）最长且字典序最小的递增子序列
1691. 堆叠长方体的最大高度（https://leetcode.cn/problems/maximum-height-by-stacking-cuboids/submissions/）经典三维偏序LIS问题
1713. 得到子序列的最少操作次数（https://leetcode.cn/problems/minimum-operations-to-make-a-subsequence/）经典LCS问题转换为LIS
1940. 排序数组之间的最长公共子序列（https://leetcode.cn/problems/longest-common-subsequence-between-sorted-arrays/）经典LCS问题转为LIS问题
3662. 最大上升子序列和（https://www.acwing.com/problem/content/description/3665/）所有长度的严格上升子序列的最大子序列和，使用离散化树状数组与线性DP计算，也可使用线段树
2826. 将三个组排序（https://leetcode.cn/problems/sorting-three-groups/）转换为求最长不降子序列
1964. 找出到每个位置为止最长的有效障碍赛跑路线（https://leetcode.cn/problems/find-the-longest-valid-obstacle-course-at-each-position/）经典LIS求以每个位置结尾的最长不降子序列长度

===================================洛谷===================================
P1020 导弹拦截（https://www.luogu.com.cn/problem/P1020）使用贪心加二分计算最长单调不减和单调不增子序列的长度
P1439 【模板】最长公共子序列（https://www.luogu.com.cn/problem/P1439）使用贪心加二分计算最长单调递增子序列的长度
P1091 合唱队形（https://www.luogu.com.cn/problem/P1091）可以往前以及往后计算最长单调子序列
P1233 木棍加工（https://www.luogu.com.cn/problem/P1233）按照一个维度排序后计算另一个维度的，最长严格递增子序列的长度
P2782 友好城市（https://www.luogu.com.cn/problem/P2782）按照一个维度排序后计算另一个维度的，最长严格递增子序列的长度（也可以考虑使用线段树求区间最大值）
P3902 递增（https://www.luogu.com.cn/problem/P3902）最长严格上升子序列
P6403 [COCI2014-2015#2] STUDENTSKO（https://www.luogu.com.cn/problem/P6403）问题转化为最长不降子序列
P5939 [POI1998]折线（https://www.luogu.com.cn/problem/P5939）旋转后转换为 LIS 问题
P5978 [CEOI2018] Global warming（https://www.luogu.com.cn/problem/P5978）经典 LIS 变形问题，贪心枚举前半部分
P7957 [COCI2014-2015#6] KRATKI（https://www.luogu.com.cn/problem/P7957）经典 LMS 逆问题构造
P1410 子序列（https://www.luogu.com.cn/problem/P1410）使用dilworth定理求最长不上升子序列长度小于等于2

===================================AcWing===================================
3549. 最长非递减子序列（https://www.acwing.com/problem/content/3552/）经典线性DP动态规划贪心
2694. 最长公共子序列（https://www.acwing.com/problem/content/description/2696/）使用LIS求解LCS的长度与个数

===================================AtCoder===================================
E - Sequence Decomposing（https://atcoder.jp/contests/abc134/tasks/abc134_e）分成最少组数的上升子序列，等于最长不上升的子序列长度

"""

import bisect
from typing import List

from src.data_structure.segment_tree.template import RangeAscendRangeMax
from src.data_structure.tree_array.template import PointAscendPreMax
from src.greedy.length_of_lis.template import LongestIncreasingSubsequence, LcsComputeByLis
from src.utils.fast_io import FastIO


class Solution:
    def __init__(self):
        return

    @staticmethod
    def abc_134e(ac=FastIO()):
        # 模板：分成最少组数的上升子序列，等于最长不上升的子序列长度
        n = ac.read_int()
        nums = [ac.read_int() for _ in range(n)]
        ans = LongestIncreasingSubsequence().definitely_not_increase(nums)
        ac.st(ans)
        return

    @staticmethod
    def lc_1713(target: List[int], arr: List[int]) -> int:
        # 模板：最长递增子序列模板题
        ind = {num: i for i, num in enumerate(target)}
        lst = [ind[num] for num in arr if num in ind]
        return len(target) - LongestIncreasingSubsequence().definitely_increase(lst)

    @staticmethod
    def lc_1964(obstacles: List[int]) -> List[int]:
        # 模板：经典LIS求以每个位置结尾的最长不降子序列长度
        pre = []
        dp = []
        for num in obstacles:
            i = bisect.bisect_right(dp, num)
            if 0 <= i < len(dp):
                dp[i] = num
                pre.append(i + 1)
            else:
                dp.append(num)
                pre.append(len(dp))
        return pre

    @staticmethod
    def lc_2111(arr: List[int], k: int) -> int:
        # 模板：最长不降子序列
        ans = 0
        for i in range(k):
            lst = arr[i::k]
            ans += len(lst) - LongestIncreasingSubsequence().definitely_not_reduce(lst)
        return ans

    @staticmethod
    def lc_2826(nums: List[int]) -> int:
        # 模板：转换为求最长不降子序列
        n = len(nums)
        return n - LongestIncreasingSubsequence().definitely_not_reduce(nums)

    @staticmethod
    def lc_p1020(ac=FastIO()):
        # 模板：根据 dilworth 最长不升子序列的长度与分成不降子序列的最小组数（最长上升子序列的长度）
        nums = ac.read_list_ints()
        lis = LongestIncreasingSubsequence()
        ac.st(lis.definitely_not_increase(nums))
        ac.st(lis.definitely_increase(nums))
        return

    @staticmethod
    def lg_1439(ac=FastIO()):
        # 模板：最长公共子序列求解使用哈希映射转换为最长上升子序列
        n = ac.read_int()
        nums = ac.read_list_ints()
        ind = [0] * (n + 1)
        for i, num in enumerate(nums):
            ind[num] = i
        nums = [ind[x] for x in ac.read_list_ints()]
        ac.st(LongestIncreasingSubsequence().definitely_increase(nums))
        return

    @staticmethod
    def lg_p5939(ac=FastIO()):
        # 模板：旋转后转换为 LIS 问题
        n = ac.read_int()
        nums = [ac.read_list_ints() for _ in range(n)]
        nums = [[x + y, y - x] for x, y in nums]
        nums.sort(key=lambda it: [it[0], -it[1]])
        dp = []
        for _, y in nums:
            i = bisect.bisect_left(dp, y)
            if 0 <= i < len(dp):
                dp[i] = y
            else:
                dp.append(y)
        ac.st(len(dp))
        return

    @staticmethod
    def lg_p5978(ac=FastIO()):
        # 模板：经典 LIS 变形问题，贪心枚举前半部分
        n, x = ac.read_list_ints()
        nums = ac.read_list_ints()
        # 预处理后缀部分的最长 LIS 序列
        post = [0] * (n + 1)
        dp = []
        for i in range(n - 1, -1, -1):
            j = bisect.bisect_left(dp, -nums[i])
            post[i] = j + 1
            if 0 <= j < len(dp):
                dp[j] = -nums[i]
            else:
                dp.append(-nums[i])

        # 贪心减少前缀值并维护最长子序列
        ans = max(post)
        dp = []
        for i in range(n):
            j = bisect.bisect_left(dp, nums[i])
            ans = ac.max(ans, j + post[i])
            j = bisect.bisect_left(dp, nums[i] - x)
            if 0 <= j < len(dp):
                dp[j] = nums[i] - x
            else:
                dp.append(nums[i] - x)
        ac.st(ans)
        return

    @staticmethod
    def lg_p7957(ac=FastIO()):
        # 模板：经典 LMS 逆问题构造
        n, k = ac.read_list_ints()
        if k * k < n:
            ac.st(-1)
            return
        ans = []
        x = 1
        while len(ans) < n:
            rest = ac.min(n - len(ans), k)
            for y in range(x + rest - 1, x - 1, -1):
                ans.append(y)
            x = x + rest
        ac.lst(ans)
        return

    @staticmethod
    def lc_673(nums: List[int]) -> int:
        return LcsComputeByLis().length_and_cnt_of_lis(nums)

    @staticmethod
    def lc_1092(str1: str, str2: str) -> str:
        # 模板：经典利用LIS求LCS的最短公共超序列
        if len(str1) > len(str2):
            str1, str2 = str2, str1
        lcs_lis = LcsComputeByLis().index_of_lcs(str1, str2)
        i = j = 0
        ans = ""
        for ind in lcs_lis:
            w = str2[ind]
            while str1[i] != w:
                ans += str1[i]
                i += 1
            while str2[j] != w:
                ans += str2[j]
                j += 1
            ans += w
            i += 1
            j += 1
        ans += str1[i:] + str2[j:]
        return ans

    @staticmethod
    def lg_p1410(ac=FastIO()):
        # 模板：最长不上升子序列
        while True:
            lst = ac.read_list_ints()
            if not lst:
                break
            lst = lst[1:]
            dp = []
            for num in lst:
                i = bisect.bisect_right(dp, -num)
                if i < len(dp):
                    dp[i] = -num
                else:
                    dp.append(-num)
            ac.st("Yes!" if len(dp) <= 2 else "No!")
        return

    @staticmethod
    def ac_3549(ac=FastIO()):
        # 模板：经典翻转连续子数组获得最长不降子序列
        ac.read_int()
        nums = ac.read_list_ints()
        s1 = s12 = s121 = s1212 = 0
        for num in nums:
            if num == 1:
                s1 += 1
                s121 = ac.max(s12 + 1, s121 + 1)
            else:
                s12 = ac.max(s1 + 1, s12 + 1)
                s1212 = ac.max(s121 + 1, s1212 + 1)
        ac.st(max(s1212, s1, s12, s121))
        return

    @staticmethod
    def ac_3662_1(ac=FastIO()):
        # 模板：所有长度的严格上升子序列的最大子序列和，使用离散化树状数组与线性DP计算，也可使用线段树
        ac.read_int()
        nums = ac.read_list_ints()
        ind = {num: i for i, num in enumerate(sorted(list(set(nums))))}
        n = len(ind)
        tree = PointAscendPreMax(n)

        for num in nums:
            if ind[num] == 0:
                tree.point_ascend(1, num)
            else:
                tree.point_ascend(ind[num] + 1, tree.pre_max(ind[num]) + num)
        ac.st(tree.pre_max(n))
        return

    @staticmethod
    def ac_3662_2(ac=FastIO()):
        # 模板：所有长度的严格上升子序列的最大子序列和，使用离散化树状数组与线性DP计算，也可使用线段树
        ac.read_int()
        nums = ac.read_list_ints()
        ind = {num: i for i, num in enumerate(sorted(list(set(nums))))}
        n = len(ind)
        tree = RangeAscendRangeMax(n)
        for num in nums:
            if ind[num] == 0:
                tree.range_ascend(0, 0, num)
            else:
                pre = tree.range_max(0, ind[num] - 1)
                tree.range_ascend(ind[num], ind[num], pre + num)
        ac.st(tree.range_max(0, n - 1))
        return

    @staticmethod
    def ac_2694(ac=FastIO()):
        # 模板：使用LIS的方法求解LCS的长度与个数
        mod = 10 ** 8
        s1 = ac.read_str()[:-1]
        s2 = ac.read_str()[:-1]
        length, cnt = LcsComputeByLis().length_and_cnt_of_lcs(s1, s2, mod)
        ac.st(length)
        ac.st(cnt % mod)
        return
