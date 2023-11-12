from functools import lru_cache
from itertools import accumulate
from math import inf
from typing import List

from src.utils.fast_io import FastIO

MOD = 10 ** 9 + 7

"""
算法：区间DP
功能：前缀和优化区间DP（需要在状态转移的时候更新代价距离）、预处理区间DP（需要预处理一个DP再计算最终DP）
题目：

===================================力扣===================================
375. 猜数字大小 II（https://leetcode.cn/problems/guess-number-higher-or-lower-ii/）经典区间DP
1130. 叶值的最小代价生成树（https://leetcode.cn/problems/minimum-cost-tree-from-leaf-values/）经典单调栈也可以使用区间DP

1039. 多边形三角剖分的最低得分（https://leetcode.cn/problems/minimum-score-triangulation-of-polygon/）经典环形数组区间 DP
2472. 不重叠回文子字符串的最大数目（https://leetcode.cn/problems/maximum-number-of-non-overlapping-palindrome-substrings/）预处理线性回文子串 DP 优化外加结果计算线性 DP 也可以使用马拉车回文串获取回文信息
2430. 对字母串可执行的最大删除数（https://leetcode.cn/problems/maximum-deletions-on-a-string/）最长公共前缀DP加线性DP
1547. 切棍子的最小成本（https://leetcode.cn/problems/minimum-cost-to-cut-a-stick/）区间DP模拟
1278. 分割回文串 III（https://leetcode.cn/problems/palindrome-partitioning-iii/）经典预处理双重区间DP进行计算
1690. 石子游戏 VII（https://leetcode.cn/problems/stone-game-vii/description/）经典区间DP
1312. 让字符串成为回文串的最少插入次数（https://leetcode.cn/problems/minimum-insertion-steps-to-make-a-string-palindrome/）经典区间DP，最长回文子序列

===================================洛谷===================================
P1521 求逆序对（https://www.luogu.com.cn/problem/P1521）使用归并排序计算移动次数，也可以使用倍增的树状数组
P1775 石子合并（弱化版）（https://www.luogu.com.cn/problem/P1775）典型区间DP和前缀和预处理
P2426 删数（https://www.luogu.com.cn/problem/P2426）典型区间DP
P2690 [USACO04NOV]Apple Catching G（https://www.luogu.com.cn/problem/P2690）区间DP记忆化搜索模拟
P1435 [IOI2000] 回文字串（https://www.luogu.com.cn/problem/P1435）典型区间DP求最长不连续回文子序列
P1388 算式（https://www.luogu.com.cn/problem/P1388）回溯枚举符号组合，再使用区间DP进行最大值求解
P1103 书本整理（https://www.luogu.com.cn/problem/P1103）三维DP
P2858 [USACO06FEB]Treats for the Cows G/S（https://www.luogu.com.cn/problem/P2858）典型区间DP
P1880 石子合并（https://www.luogu.com.cn/problem/P1880）将数组复制成两遍进行区间DP
P3205 [HNOI2010]合唱队（https://www.luogu.com.cn/problem/P3205）区间DP使用滚动数组
P1880 [NOI1995] 石子合并（https://www.luogu.com.cn/problem/P1880）环形数组区间DP合并求最大值最小值
P1040 [NOIP2003 提高组] 加分二叉树（https://www.luogu.com.cn/problem/P1040）区间DP与路径还原
P1043 [NOIP2003 普及组] 数字游戏（https://www.luogu.com.cn/problem/P1043）环形区间DP
P1430 序列取数（https://www.luogu.com.cn/problem/P1430）区间DP加前缀数组优化
P2308 添加括号（https://www.luogu.com.cn/problem/P2308）经典区间DP，并使用递归方式反解括号添加方式以及每一步的和
P2734 [USACO3.3]游戏 A Game（https://www.luogu.com.cn/problem/P2734）前缀和加区间DP
P3004 [USACO10DEC]Treasure Chest S（https://www.luogu.com.cn/problem/P3004）简单区间 DP 
P3205 [HNOI2010]合唱队（https://www.luogu.com.cn/problem/P3205）区间 DP 使用滚动数组优化
P4170 [CQOI2007]涂色（https://www.luogu.com.cn/problem/P4170）经典区间 DP 注意转移方程计算

================================CodeForces================================
C. The Sports Festival（https://codeforces.com/problemset/problem/1509/C）转换为区间DP进行求解
B. Zuma（https://codeforces.com/problemset/problem/607/B）区间DP，经典通过消除回文子序列删除整个数组的最少次数

================================AcWing================================
3996. 涂色（https://www.acwing.com/problem/content/3999/）经典区间 DP 最长回文子序列变形

参考：OI WiKi（xx）
"""


class Solution:
    def __init__(self):
        return

    @staticmethod
    def cf_307b(ac=FastIO()):
        #
        n = ac.read_int()
        nums = ac.read_list_ints()

        # 初始化
        dp = [[inf] * n for _ in range(n + 1)]
        for i in range(n):
            for j in range(i):
                dp[i][j] = 0
        dp[n] = [0] * n

        # 状态转移
        for i in range(n - 1, -1, -1):
            dp[i][i] = 1
            if i + 1 < n:
                dp[i][i + 1] = 2 if nums[i] != nums[i + 1] else 1
            for j in range(i + 2, n):

                dp[i][j] = ac.min(dp[i + 1][j], dp[i][j - 1]) + 1
                if nums[i] == nums[i + 1]:
                    dp[i][j] = ac.min(dp[i][j], 1 + dp[i + 2][j])

                for k in range(i + 2, j + 1):
                    dp[i][j] = ac.min(dp[i][j], dp[i][k] + dp[k + 1][j])
                    if nums[k] == nums[i]:
                        dp[i][j] = ac.min(dp[i][j], dp[i + 1][k - 1] + dp[k + 1][j])

        ac.st(dp[0][n - 1])
        return

    @staticmethod
    def cf_1509c(n, nums):
        # 模板：使用数组进行区间DP转移求解
        dp = [[inf] * n for _ in range(n)]
        for i in range(n - 1, -1, -1):
            dp[i][i] = 0
            for j in range(i + 1, n):
                dp[i][j] = nums[j] - nums[i] + min(dp[i + 1][j], dp[i][j - 1])
        return dp[0][n - 1]

    @staticmethod
    def lc_1312(s: str) -> int:
        # 模板：经典区间DP，最长回文子序列
        n = len(s)
        dp = [[0] * n for _ in range(n)]
        for i in range(n - 1, -1, -1):
            dp[i][i] = 1
            if i + 1 < n:
                dp[i][i + 1] = 2 if s[i] == s[i + 1] else 1
            for j in range(i + 2, n):
                a, b = dp[i + 1][j], dp[i][j - 1]
                a = a if a > b else b
                b = dp[i + 1][j - 1] + 2 * int(s[i] == s[j])

                dp[i][j] = a if a > b else b
        return n - dp[0][n - 1]

    @staticmethod
    def lc_1547(n: int, cuts: List[int]) -> int:
        # 模板：区间DP模拟
        cuts.sort()
        cuts.insert(0, 0)
        cuts.append(n)
        m = len(cuts)
        dp = [[0] * (m + 1) for _ in range(m + 1)]
        for i in range(m - 1, -1, -1):
            for j in range(i + 2, m):
                dp[i][j] = cuts[j] - cuts[i] + min(dp[i][k] + dp[k][j] for k in range(i + 1, j))
        return dp[0][m - 1]

    @staticmethod
    def lc_1690(stones: List[int]) -> int:
        # 模板：经典区间DP
        n = len(stones)
        pre = list(accumulate(stones, initial=0))

        @lru_cache(None)
        def dfs(i, j):
            if i == j:
                return 0
            return max(-dfs(i + 1, j) + pre[j + 1] - pre[i + 1], -dfs(i, j - 1) + pre[j] - pre[i])

        ans = dfs(0, n - 1)
        dfs.cache_clear()
        return ans

    @staticmethod
    def lc_2472(s: str, k: int) -> int:
        # 模板：预处理线性回文子串 DP 优化外加结果计算线性 DP 也可以使用马拉车回文串获取回文信息
        n = len(s)
        res = [[0] * (n + 1) for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            res[i][i] = 1
            if i + 1 < n:
                res[i][i + 1] = 1 if s[i] == s[i + 1] else 0
            for j in range(i + 2, n):
                if s[i] == s[j] and res[i + 1][j - 1]:
                    res[i][j] = 1

        dp = [0] * (n + 1)
        for i in range(n):
            dp[i + 1] = dp[i]
            for j in range(0, i - k + 2):
                if i - j + 1 >= k and res[j][i]:
                    dp[i + 1] = max(dp[i + 1], dp[j] + 1)
        return dp[-1]

    @staticmethod
    def lg_p3205(ac=FastIO()):
        # 模板：区间DP滚动数组更新
        n = ac.read_int()
        nums = ac.read_list_ints()
        mod = 19650827
        dp = [[[0, 0] for _ in range(n)] for _ in range(2)]
        pre = 0
        for i in range(n - 1, -1, -1):
            cur = 1 - pre
            dp[cur][i][0] = 1
            for j in range(i + 1, n):
                x = 0
                # 后 j
                if nums[j - 1] < nums[j]:
                    x += dp[cur][j - 1][1]
                if nums[i] < nums[j]:
                    x += dp[cur][j - 1][0]
                dp[cur][j][1] = x % mod
                x = 0
                # 后 i
                if nums[i + 1] > nums[i]:
                    x += dp[pre][j][0]
                if nums[j] > nums[i]:
                    x += dp[pre][j][1]
                dp[cur][j][0] = x % mod
            pre = cur
        ac.st(sum(dp[pre][n - 1]) % mod)
        return

    @staticmethod
    def lg_p1040(ac=FastIO()):
        # 模板：使用区间DP计算最小代价，并使用迭代还原前序遍历路径
        n = ac.read_int()
        nums = ac.read_list_ints()

        dp = [[0] * n for _ in range(n)]
        for i in range(n - 1, -1, -1):
            dp[i][i] = nums[i]
            if i + 1 < n:
                dp[i][i + 1] = nums[i] + nums[i + 1]
            for j in range(i + 2, n):
                dp[i][j] = max(dp[i][k - 1] * dp[k + 1][j] + dp[k][k] for k in range(i + 1, j))

        # 使用栈模拟进行方案还原
        ans = []
        stack = [[0, n - 1]]
        while stack:
            i, j = stack.pop()
            if i == j:
                ans.append(i + 1)
                continue
            if i == j - 1:
                ans.append(i + 1)
                ans.append(j + 1)
                continue
            for k in range(i + 1, j):
                if dp[i][j] == dp[i][k - 1] * dp[k + 1][j] + dp[k][k]:
                    ans.append(k + 1)
                    stack.append([k + 1, j])
                    stack.append([i, k - 1])
                    break
        ac.st(dp[0][n - 1])
        ac.lst(ans)
        return

    @staticmethod
    def lg_p1430(ac=FastIO()):
        # 模板：区间DP加前缀数组优化
        for _ in range(ac.read_int()):
            nums = ac.read_list_ints()
            n = nums.pop(0)
            pre = [0] * (n + 1)
            for i in range(n):
                pre[i + 1] = pre[i] + nums[i]

            dp = [0] * n
            post = [0] * n
            for i in range(n - 1, -1, -1):
                dp[i] = nums[i]
                post[i] = ac.min(nums[i], post[i])
                floor = ac.min(0, nums[i])
                for j in range(i + 1, n):
                    s = pre[j + 1] - pre[i]
                    dp[j] = s
                    dp[j] = ac.max(dp[j], s - post[j])
                    dp[j] = ac.max(dp[j], s - floor)
                    floor = ac.min(floor, dp[j])
                    post[j] = ac.min(post[j], dp[j])
            ac.st(dp[n - 1])
        return

    @staticmethod
    def lg_p2308(ac=FastIO()):
        # 模板：经典区间DP，并使用递归方式反解括号添加方式以及每一步的和
        n = ac.read_int()
        nums = ac.read_list_ints()
        pre = ac.accumulate(nums)
        # 记录转移的中间节点与加和最小值
        dp = [[inf] * n for _ in range(n)]
        mid = [[-1] * n for _ in range(n)]
        for i in range(n - 1, -1, -1):
            dp[i][i] = 0
            for j in range(i + 1, n):
                ind = i
                for k in range(i, j):
                    cur = dp[i][k] + dp[k + 1][j] + pre[j + 1] - pre[i]
                    if cur < dp[i][j]:
                        dp[i][j] = cur
                        ind = k
                mid[i][j] = ind

        # 反推路径
        ans = []
        nums = [str(x) for x in nums]
        stack = [[0, n - 1]]
        while stack:
            i, j = stack.pop()
            if i >= 0:
                stack.append([~i, j])
                if i >= j - 1:
                    continue
                k = mid[i][j]
                # 先左后右
                stack.append([k + 1, j])
                stack.append([i, k])
            else:
                i = ~i
                if i < j:
                    nums[i] = "(" + nums[i]
                    nums[j] = nums[j] + ")"
                    ans.append(pre[j + 1] - pre[i])
        ac.st("+".join(nums))
        ac.st(sum(ans))
        ac.lst(ans)
        return

    @staticmethod
    def lg_p2734(ac=FastIO()):

        # 模板：前缀和加区间 DP

        n = ac.read_int()
        nums = []
        while len(nums) < n:
            nums.extend(ac.read_list_ints())
        pre = ac.accumulate(nums)

        # @lru_cache(None)
        # def dfs(i, j):
        #     if i == j:
        #         return nums[j]
        #     res = nums[i]+pre[j+1]-pre[i+1]-dfs(i+1, j)
        #     res = ac.max(res, nums[j]+pre[j]-pre[i]-dfs(i, j-1))
        #     return res
        # a = dfs(0, n-1)
        # ac.lst([a, pre[-1]-a])

        dp = [[0] * n for _ in range(n)]
        for i in range(n - 1, -1, -1):
            dp[i][i] = nums[i]
            for j in range(i + 1, n):
                dp[i][j] = ac.max(nums[i] + pre[j + 1] - pre[i + 1] - dp[i + 1][j],
                                  nums[j] + pre[j] - pre[i] - dp[i][j - 1])
        a = dp[0][n - 1]
        ac.lst([a, pre[-1] - a])
        return

    @staticmethod
    def lg_p3004(ac=FastIO()):
        # 模板：简单区间 DP
        n = ac.read_int()
        nums = [ac.read_int() for _ in range(n)]
        dp = [[0] * n for _ in range(2)]
        pre = ac.accumulate(nums)
        x = 0
        for i in range(n - 1, -1, -1):
            y = 1 - x
            dp[y][i] = nums[i]
            for j in range(i + 1, n):
                dp[y][j] = ac.max(pre[j + 1] - pre[i + 1] - dp[x][j] + nums[i],
                                  pre[j] - pre[i] - dp[y][j - 1] + nums[j])
            x = y
        ac.st(dp[x][n - 1])
        return

    @staticmethod
    def lg_p4170(ac=FastIO()):
        # 模板：经典区间 DP 注意转移方程计算
        s = ac.read_str()
        n = len(s)
        dp = [[inf] * n for _ in range(n)]
        for i in range(n - 1, -1, -1):
            dp[i][i] = 1
            for j in range(i + 1, n):
                if s[i] == s[j]:
                    dp[i][j] = ac.min(dp[i + 1][j], dp[i][j - 1])
                else:
                    for k in range(i, j):
                        dp[i][j] = ac.min(dp[i][j], dp[i][k] + dp[k + 1][j])
        ac.st(dp[0][n - 1])
        return

    @staticmethod
    def ac_3996(ac=FastIO()):
        # 模板：经典区间 DP 最长回文子序列变形
        ac.read_int()
        nums = ac.read_list_ints()
        pre = []
        for num in nums:
            if pre and pre[-1] == num:
                continue
            pre.append(num)
        nums = pre[:]
        n = len(nums)
        dp = [[0] * n for _ in range(n)]
        for i in range(n - 1, -1, -1):
            for j in range(i + 1, n):
                if nums[i] == nums[j]:
                    dp[i][j] = dp[i + 1][j - 1] + 1
                else:
                    dp[i][j] = ac.min(dp[i + 1][j], dp[i][j - 1]) + 1
        ac.st(dp[0][n - 1])
        return

    @staticmethod
    def lc_1278(s: str, k: int) -> int:
        # 模板：经典预处理双重区间DP进行计算
        n = len(s)

        cost = [[0] * n for _ in range(n)]
        for i in range(n - 1, -1, -1):
            if i + 1 < n:
                j = i + 1
                cost[i][j] = 1 if s[i] != s[j] else 0
            for j in range(i + 2, n):
                cost[i][j] = cost[i + 1][j - 1] + int(s[i] != s[j])

        dp = [[n] * k for _ in range(n + 1)]
        for i in range(n):
            dp[i + 1][0] = cost[0][i]
            for j in range(1, k):
                dp[i + 1][j] = min(dp[x][j - 1] + cost[x][i] for x in range(i + 1))
        return dp[n][k - 1]
