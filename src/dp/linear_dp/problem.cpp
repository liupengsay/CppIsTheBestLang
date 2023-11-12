
"""
算法：线性DP
功能：遍历数组，根据前序或者后序结果进行更新，最大非空连续子序列和
题目：

===================================力扣===================================
87. 扰乱字符串（https://leetcode.cn/problems/scramble-string/）经典线性DP记忆化深搜
2361. 乘坐火车路线的最少费用（https://leetcode.cn/problems/minimum-costs-using-the-train-line/）当前状态只跟前一个状态有关
2318. 不同骰子序列的数目（https://leetcode.cn/problems/number-of-distinct-roll-sequences/）当前状态只跟前一个状态有关使用枚举计数
2263. 数组变为有序的最小操作次数（https://leetcode.cn/problems/make-array-non-decreasing-or-non-increasing/）当前状态只跟前一个状态有关
2209. 用地毯覆盖后的最少白色砖块（https://leetcode.cn/problems/minimum-white-tiles-after-covering-with-carpets/）前缀优化与处理进行转移
2188. 完成比赛的最少时间（https://leetcode.cn/problems/minimum-time-to-finish-the-race/）预处理DP
2167. 移除所有载有违禁货物车厢所需的最少时间（https://leetcode.cn/problems/minimum-time-to-remove-all-cars-containing-illegal-goods/）使用前缀后缀DP预处理后进行枚举
2431. 最大限度地提高购买水果的口味（https://leetcode.cn/problems/maximize-total-tastiness-of-purchased-fruits/）线性DP进行模拟计算
6355. 质数减法运算（https://leetcode.cn/contest/weekly-contest-338/problems/collect-coins-in-a-tree/）线性DP
2547. 拆分数组的最小代价（https://leetcode.cn/problems/minimum-cost-to-split-an-array/）线性DP并使用一个变量维护计数
2638. 统计 K-Free 子集的总数（https://leetcode.cn/problems/count-the-number-of-k-free-subsets/）经典线性DP计数
2597. 美丽子集的数目（https://leetcode.cn/problems/the-number-of-beautiful-subsets/）·
2713. 矩阵中严格递增的单元格数（https://leetcode.cn/problems/maximum-strictly-increasing-cells-in-a-matrix/）按照值域分层线性 DP
1526. 形成目标数组的子数组最少增加次数（https://leetcode.cn/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/）经典线性 DP 与贪心
1553. 吃掉 N 个橘子的最少天数（https://leetcode.cn/problems/minimum-number-of-days-to-eat-n-oranges/）脑筋急转弯贪心记忆化搜索线性DP
1872. 石子游戏 VIII（https://leetcode.cn/problems/stone-game-viii/）前缀和倒序DP
1770. 执行乘法运算的最大分数（https://leetcode.cn/problems/maximum-score-from-performing-multiplication-operations/）经典数组匹配线性DP
823. 带因子的二叉树（https://leetcode.cn/problems/binary-trees-with-factors/description/）经典线性DP计数
2289. 使数组按非递减顺序排列（https://leetcode.cn/problems/steps-to-make-array-non-decreasing/description/）经典单调栈优化的线性DP，也可用BFS加链表求解
2746. 字符串连接删减字母（https://leetcode.cn/problems/decremental-string-concatenation/）经典哈希线性DP模拟实现
1911. 最大子序列交替和（https://leetcode.cn/problems/maximum-alternating-subsequence-sum/）经典线性DP
2321. 拼接数组的最大分数（https://leetcode.cn/problems/maximum-score-of-spliced-array/description/）最大连续子数组和变种
2320. 统计放置房子的方式数（https://leetcode.cn/problems/count-number-of-ways-to-place-houses/）经典线性DP
1824. 最少侧跳次数（https://leetcode.cn/problems/minimum-sideway-jumps/description/）经典线性DP滚动数组
978. 最长湍流子数组（https://leetcode.cn/problems/longest-turbulent-subarray/description/）经典线性DP滚动变量
1027. 最长等差数列（https://leetcode.cn/problems/longest-arithmetic-subsequence/）经典线性DP计算最长等差子序列
1987. 不同的好子序列数目（https://leetcode.cn/problems/number-of-unique-good-subsequences/description/）经典线性计数DP
2355. 你能拿走的最大图书数量（https://leetcode.cn/problems/maximum-number-of-books-you-can-take/）经典单调栈加线性DP，使用下标使用巧妙地转换，计算严格递增子序列的和
100048. 美丽塔 II（https://leetcode.cn/problems/beautiful-towers-ii/）经典单调栈加线性DP，计算山脉子序列的和，前后缀单调栈优化线性DP
2327. 知道秘密的人数（https://leetcode.cn/problems/number-of-people-aware-of-a-secret/description/）经典前缀和或者差分数组优化线性DP
2572. 无平方子集计数（https://leetcode.cn/problems/count-the-number-of-square-free-subsets/description/）经典线性DP计数

===================================洛谷===================================
P1970 [NOIP2013 提高组] 花匠（https://www.luogu.com.cn/problem/P1970）使用贪心与动态规划计算最长的山脉子数组
P1564 膜拜（https://www.luogu.com.cn/problem/P1564）线性DP
P1481 魔族密码（https://www.luogu.com.cn/problem/P1481）线性DP
P2029 跳舞（https://www.luogu.com.cn/problem/P2029）线性DP
P2031 脑力达人之分割字串（https://www.luogu.com.cn/problem/P2031）线性DP
P2062 分队问题（https://www.luogu.com.cn/problem/P2062）线性DP+前缀最大值DP剪枝优化
P2072 宗教问题（https://www.luogu.com.cn/problem/P2072）两个线性DP
P2096 最佳旅游线路（https://www.luogu.com.cn/problem/P2096）最大连续子序列和变种
P5761 [NOI1997] 最佳游览（https://www.luogu.com.cn/problem/P5761）最大连续子序列和变种
P2285 [HNOI2004]打鼹鼠（https://www.luogu.com.cn/problem/P2285）线性DP+前缀最大值DP剪枝优化
P2642 双子序列最大和（https://www.luogu.com.cn/problem/P2642）枚举前后两个非空的最大子序列和
P1470 [USACO2.3]最长前缀 Longest Prefix（https://www.luogu.com.cn/problem/P1470）线性DP
P1096 [NOIP2007 普及组] Hanoi 双塔问题（https://www.luogu.com.cn/problem/P1096）经典线性DP
P2896 [USACO08FEB]Eating Together S（https://www.luogu.com.cn/problem/P2896）前后缀动态规划
P2904 [USACO08MAR]River Crossing S（https://www.luogu.com.cn/problem/P2904）前缀和预处理加线性DP
P3062 [USACO12DEC]Wifi Setup S（https://www.luogu.com.cn/problem/P3062）线性DP枚举
P3842 [TJOI2007]线段（https://www.luogu.com.cn/problem/P3842）线性DP进行模拟
P3903 导弹拦截III（https://www.luogu.com.cn/problem/P3903）线性DP枚举当前元素作为谷底与山峰的子序列长度
P5414 [YNOI2019] 排序（https://www.luogu.com.cn/problem/P5414）贪心，使用线性DP计算最大不降子序列和
P6191 [USACO09FEB]Bulls And Cows S（https://www.luogu.com.cn/problem/P6191）线性DP枚举计数
P6208 [USACO06OCT] Cow Pie Treasures G（https://www.luogu.com.cn/problem/P6208）线性DP模拟
P7404 [JOI 2021 Final] とてもたのしい家庭菜園 4（https://www.luogu.com.cn/problem/P7404）动态规划枚举，计算变成山脉数组的最少操作次数
P7541 [COCI2009-2010#1] DOBRA（https://www.luogu.com.cn/problem/P7541）线性DP记忆化搜索，类似数位DP
P7767 [COCI 2011/2012 #5] DNA（https://www.luogu.com.cn/problem/P7767）线性DP，计算前缀变成全部相同字符的最少操作次数
P2246 SAC#1 - Hello World（升级版）（https://www.luogu.com.cn/problem/P2246）字符串计数线性DP
P4933 大师（https://www.luogu.com.cn/problem/P4933）线性DP使用等差数列计数
P1874 快速求和（https://www.luogu.com.cn/problem/P1874）线性DP
P2513 [HAOI2009]逆序对数列（https://www.luogu.com.cn/problem/P2513）前缀和优化DP
P1280 尼克的任务（https://www.luogu.com.cn/problem/P1280）经典逆序线性 DP
P1282 多米诺骨牌（https://www.luogu.com.cn/problem/P1282）典型线性DP，使用哈希实现
P1356 数列的整除性（https://www.luogu.com.cn/problem/P1356）典型线性取模DP
P1385 密令（https://www.luogu.com.cn/problem/P1385）线性DP与前缀和优化，脑筋急转弯字符串字典序总和不变
P1809 过河问题（https://www.luogu.com.cn/problem/P1809）思维题线性DP，经典贪心
P1868 饥饿的奶牛（https://www.luogu.com.cn/problem/P1868）线性DP加二分查找优化
P1978 集合（https://www.luogu.com.cn/problem/P1978）经典线性DP，乘积互斥
P2432 zxbsmk爱查错（https://www.luogu.com.cn/problem/P2432）线性DP加指针
P2439 [SDOI2005]阶梯教室设备利用（https://www.luogu.com.cn/problem/P2439）线性DP加二分
P2476 [SCOI2008]着色方案（https://www.luogu.com.cn/problem/P2476）计数分组线性 DP 记忆化搜索
P2849 [USACO14DEC]Marathon S（https://www.luogu.com.cn/problem/P2849）矩阵二维 DP 线性遍历
P3448 [POI2006]MIS-Teddies（https://www.luogu.com.cn/problem/P3448）经典线性DP计数
P3558 [POI2013]BAJ-Bytecomputer（https://www.luogu.com.cn/problem/P3558）线性 DP 模拟
B3734 [信息与未来 2017] 加强版密码锁（https://www.luogu.com.cn/problem/B3734）
P3901 数列找不同（https://www.luogu.com.cn/problem/P3901）经典指针加线性 DP 记录前一个相同数的指针
P4401 [IOI2007]Miners 矿工配餐（https://www.luogu.com.cn/problem/P4401）
P4933 大师（https://www.luogu.com.cn/problem/P4933）经典等差数列线性 DP 计数
P5095 [USACO12OPEN]Bookshelf S（https://www.luogu.com.cn/problem/P5095）典型线性 DP
P5810 [SCOI2004]文本的输入（https://www.luogu.com.cn/problem/P5810）经典线性 DP
P6040 「ACOI2020」课后期末考试滑溜滑溜补习班（https://www.luogu.com.cn/problem/P6040）单调队列优化的线性 DP
P6120 [USACO17JAN]Hoof, Paper, Scissor S（https://www.luogu.com.cn/problem/P6120）线性 DP 模拟
P6146 [USACO20FEB]Help Yourself G（https://www.luogu.com.cn/problem/P6146）线性 DP 枚举计数
P7994 [USACO21DEC] Air Cownditioning B（https://www.luogu.com.cn/problem/P7994）经典线性 DP 修改连续区间值加一减一的最少操作次数
P8656 [蓝桥杯 2017 国 B] 对局匹配（https://www.luogu.com.cn/problem/P8656）经典分组线性 DP
P8725 [蓝桥杯 2020 省 AB3] 画中漂流（https://www.luogu.com.cn/problem/P8725）典型矩阵 DP 使用指针关系减少维度
P8784 [蓝桥杯 2022 省 B] 积木画（https://www.luogu.com.cn/problem/P8784）线性 DP 可以使用矩阵幂优化
P8786 [蓝桥杯 2022 省 B] 李白打酒加强版（https://www.luogu.com.cn/problem/P8786）线性 DP 记忆化搜索模拟
P8816 [CSP-J 2022] 上升点列（https://www.luogu.com.cn/problem/P8816）典型线性矩阵 DP 模拟

================================CodeForces================================
https://codeforces.com/problemset/problem/75/D（经典压缩数组，最大子段和升级）
https://codeforces.com/problemset/problem/1084/C（线性DP加前缀和优化）
https://codeforces.com/problemset/problem/166/E（经典线性DP计数）
https://codeforces.com/problemset/problem/1221/D（线性DP模拟）
C. Chef Monocarp（https://codeforces.com/problemset/problem/1437/C）二维线性DP，两个数组线性移动进行匹配计算最大或者最小值
D. Armchairs（https://codeforces.com/problemset/problem/1525/D）二维线性DP，两个数组线性移动进行匹配计算最大或者最小值
A. Garland（https://codeforces.com/problemset/problem/1286/A）线性经典dp
D. Make The Fence Great Again（https://codeforces.com/problemset/problem/1221/D）线性DP，最多变化为增加0、1、2
E. Funny Game（https://codeforces.com/contest/731/problem/E）前缀和倒序DP

================================AtCoder====================================
E - Sum Equals Xor（https://atcoder.jp/contests/abc129/tasks/abc129_e）思维题，类似数位DP

================================AcWing====================================
96. 奇怪的汉诺塔（https://www.acwing.com/problem/content/98/）经典的汉诺塔问题，可推广到n个盘子与m个柱子
4414. 子序列（https://www.acwing.com/problem/content/description/4417/）经典线性子序列DP

参考：OI WiKi（xx）
"""
import bisect
from collections import defaultdict, Counter, deque
from functools import lru_cache
from math import inf
from typing import List

from src.mathmatics.number_theory.template import NumberTheory
from src.utils.fast_io import FastIO


class Solution:
    def __init__(self):
        return

    @staticmethod
    def lc_1770(nums: List[int], multipliers: List[int]) -> int:
        # 模板：经典数组匹配线性DP

        @lru_cache(None)
        def dfs(i, j):
            ind = i + (n - 1 - j)
            if ind == m:
                return 0
            a, b = dfs(i + 1, j) + nums[i] * multipliers[ind], dfs(i, j - 1) + nums[j] * multipliers[ind]
            return a if a > b else b

        n = len(nums)
        m = len(multipliers)
        return dfs(0, n - 1)

    @staticmethod
    def lc_823(arr: List[int]) -> int:
        # 模板：经典线性DP计数
        mod = 10 ** 9 + 7
        n = len(arr)
        arr.sort()
        dct = {num: i for i, num in enumerate(arr)}

        dp = [0] * n
        dp[0] = 1
        for i in range(1, n):
            dp[i] = 1
            x = arr[i]
            for j in range(i):
                y = arr[j]
                if y*y > x:
                    break
                if x % y == 0 and x // y in dct:
                    if y == x // y:
                        dp[i] += dp[j] * dp[j]
                    else:
                        dp[i] += dp[j] * dp[dct[x // y]] * 2
                    dp[i] %= mod
        return sum(dp) % mod

    @staticmethod
    def lc_2289(nums: List[int]) -> int:
        # 模板：经典单调栈优化的线性DP，也可用BFS加链表求解
        n = len(nums)
        stack = []
        for i in range(n - 1, -1, -1):
            cnt = 0
            while stack and stack[-1][0] < nums[i]:
                _, x = stack.pop()
                cnt = cnt + 1 if cnt + 1 > x else x
            stack.append([nums[i], cnt])
        return max(ls[1] for ls in stack)

    @staticmethod
    def lc_2361(
            regular: List[int],
            express: List[int],
            express_cost: int) -> List[int]:
        # 模板：线性 DP 转移
        n = len(regular)
        cost = [[0, 0] for _ in range(n + 1)]
        cost[0][1] = express_cost
        for i in range(1, n + 1):
            cost[i][0] = min(cost[i - 1][0] + regular[i - 1],
                             cost[i - 1][1] + express[i - 1])
            cost[i][1] = min(cost[i][0] + express_cost,
                             cost[i - 1][1] + express[i - 1])
        return [min(c) for c in cost[1:]]

    @staticmethod
    def cf_1286a(ac=FastIO()):

        n = ac.read_int()
        nums = ac.read_list_ints()
        ex = set(nums)
        cnt = Counter([i % 2 for i in range(1, n + 1) if i not in ex])

        # 模板：经典记忆化搜索的模拟线性DP写法
        @ac.bootstrap
        def dfs(i, single, double, pre):
            if (i, single, double, pre) in dct:
                yield
            if i == n:
                dct[(i, single, double, pre)] = 0
                yield
            res = inf
            if nums[i] != 0:
                v = nums[i] % 2
                yield dfs(i + 1, single, double, v)
                cur = dct[(i + 1, single, double, v)]
                if pre != -1 and pre != v:
                    cur += 1
                res = ac.min(res, cur)
            else:
                if single:
                    yield dfs(i + 1, single - 1, double, 1)
                    cur = dct[(i + 1, single - 1, double, 1)]
                    if pre != -1 and pre != 1:
                        cur += 1
                    res = ac.min(res, cur)
                if double:
                    yield dfs(i + 1, single, double - 1, 0)
                    cur = dct[(i + 1, single, double - 1, 0)]
                    if pre != -1 and pre != 0:
                        cur += 1
                    res = ac.min(res, cur)
            dct[(i, single, double, pre)] = res
            yield

        dct = dict()
        dfs(0, cnt[1], cnt[0], -1)
        ac.st(dct[(0, cnt[1], cnt[0], -1)])
        return

    @staticmethod
    def lc_2638(nums: List[int], k: int) -> int:
        # 模板：经典线性DP计数
        n = len(nums)
        dp = [1] * (n + 1)
        dp[1] = 2
        for i in range(2, 51):
            dp[i] = dp[i - 1] + dp[i - 2]
        dct = set(nums)
        ans = 1
        for num in nums:
            if num - k not in dct:
                cnt = 0
                while num in dct:
                    cnt += 1
                    num += k
                ans *= dp[cnt]
        return ans

    @staticmethod
    def lc_2597(nums: List[int], k: int) -> int:
        # 模板：经典线性DP计数
        power = [1 << i for i in range(21)]

        def check(tmp):
            m = len(tmp)
            dp = [1] * (m + 1)
            dp[1] = power[tmp[0]] - 1 + dp[0]
            for i in range(1, m):
                dp[i + 1] = dp[i - 1] * (power[tmp[i]] - 1) + dp[i]
            return dp[-1]

        cnt = Counter(nums)
        ans = 1
        for num in cnt:
            if num - k not in cnt:
                lst = []
                while num in cnt:
                    lst.append(cnt[num])
                    num += k
                ans *= check(lst)
        return ans - 1

    @staticmethod
    def cf_1525d(ac=FastIO()):
        n = ac.read_int()
        nums = ac.read_list_ints()
        busy = [i for i in range(n) if nums[i]]
        free = [i for i in range(n) if not nums[i]]
        if not busy:
            ac.st(0)
            return
        a, b = len(busy), len(free)
        dp = [[inf] * (b + 1) for _ in range(a + 1)]
        dp[0] = [0] * (b + 1)
        for i in range(a):
            for j in range(b):
                dp[i + 1][j + 1] = ac.min(dp[i + 1][j], dp[i][j] + abs(busy[i] - free[j]))
        ac.st(dp[-1][-1])
        return

    @staticmethod
    def cf_1437c(n, nums):
        # 模板：两个数组线性移动进行匹配计算最大或者最小值
        nums.sort()
        m = 2 * n
        dp = [[inf] * (n + 1) for _ in range(m + 1)]
        dp[0][0] = 0
        for i in range(m):
            dp[i + 1][0] = 0
            for j in range(n):
                dp[i + 1][j + 1] = min(dp[i][j + 1],
                                       dp[i][j] + abs(nums[j] - i - 1))
        return dp[m][n]

    @staticmethod
    def lg_p4933(ac=FastIO()):
        # 模板：不同等差子序列的个数
        n = ac.read_int()
        nums = ac.read_list_ints()
        mod = 998244353
        ans = n
        dp = [defaultdict(int) for _ in range(n)]
        for i in range(n):
            for j in range(i):
                dp[i][nums[i] - nums[j]] += dp[j][nums[i] - nums[j]] + 1
                dp[i][nums[i] - nums[j]] %= mod
            for j in dp[i]:
                ans += dp[i][j]
                ans %= mod
        ac.st(ans)
        return

    @staticmethod
    def ac_96(ac=FastIO()):
        # 模板：两层线性DP，经典汉诺塔问题
        n = 12
        dp3 = [inf] * (n + 1)  # 三个柱子
        dp3[0] = 0
        dp3[1] = 1
        for i in range(2, n + 1):
            dp3[i] = 2 * dp3[i - 1] + 1

        dp4 = [inf] * (n + 1)  # 四个柱子
        dp4[0] = 0
        dp4[1] = 1
        for i in range(2, n + 1):
            dp4[i] = min(2 * dp4[j] + dp3[i - j] for j in range(1, i))

        for x in range(1, n + 1):
            ac.st(dp4[x])
        return

    @staticmethod
    def lg_p1280(ac=FastIO()):
        # 模板：线性DP倒序模拟优化
        n, k = ac.read_list_ints()
        dct = [[] for _ in range(n + 1)]
        for _ in range(k):
            p, t = ac.read_list_ints()
            dct[p].append(p + t)
        dp = [0] * (n + 2)
        for i in range(n, 0, -1):
            if not dct[i]:
                dp[i] = dp[i + 1] + 1
            else:
                for end in dct[i]:
                    dp[i] = ac.max(dp[i], dp[end])
        ac.st(dp[1])
        return

    @staticmethod
    def lg_p1282(ac=FastIO()):
        # 模板：典型线性DP使用哈希滚动
        n = ac.read_int()
        nums = [ac.read_list_ints() for _ in range(n)]
        pre = defaultdict(lambda: inf)
        pre[0] = 0
        for i in range(n):
            # 枚举当前是否进行翻转
            a, b = nums[i]
            cur = defaultdict(lambda: inf)
            for p in pre:
                cur[p + a - b] = ac.min(cur[p + a - b], pre[p])
                cur[p + b - a] = ac.min(cur[p + b - a], pre[p] + 1)
            # 哈希记录差值为 x 时的最小翻转次数
            pre = cur.copy()
        x = min(abs(v) for v in pre.keys())
        ans = inf
        for v in pre:
            if abs(v) == x:
                ans = ac.min(ans, pre[v])
        ac.st(ans)
        return

    @staticmethod
    def lg_p1356(ac=FastIO()):
        # 模板：线性DP
        m = ac.read_int()
        for _ in range(m):
            n, k = ac.read_list_ints()
            nums = ac.read_list_ints()
            pre = [0] * k
            pre[nums[0] % k] = 1
            for num in nums[1:]:
                cur = [0] * k
                for a in [num, -num]:
                    for i in range(k):
                        if pre[i]:
                            cur[(i + a) % k] = 1
                pre = cur[:]
            ac.st("Divisible" if pre[0] else "Not divisible")
        return

    @staticmethod
    def lg_p1385(ac=FastIO()):
        # 模板：线性DP与前缀和优化
        mod = 10**9 + 7
        for _ in range(ac.read_int()):
            s = ac.read_str()
            n = len(s)
            t = sum(ord(w) - ord("a") + 1 for w in s)
            pre = [0] * (t + 1)
            pre[0] = 1
            # dp[i][j] 表长为 i+1 字典序和为 j 的方案数
            for _ in range(n):
                cur = [0] * (t + 1)
                x = 0  # 前缀和优化
                for i in range(t + 1):
                    cur[i] = x
                    x += pre[i]
                    x %= mod
                    if i >= 26:
                        x -= pre[i - 26]
                        x %= mod
                pre = cur[:]
            ac.st((pre[-1] - 1) % mod)
        return

    @staticmethod
    def lg_p1809(ac=FastIO()):
        # 模板：思维题线性DP
        n = ac.read_int()
        nums = [ac.read_int() for _ in range(n)]
        if n == 1:
            ac.st(nums[0])
            return
        nums.sort()
        dp = [inf] * (n + 1)
        dp[0] = 0
        dp[1] = nums[0]
        dp[2] = ac.max(nums[0], nums[1])
        for i in range(2, n):
            # 两种可选方案，最小的来回，以及最小与次小的来回
            dp[i + 1] = ac.min(dp[i] + nums[0] + nums[i],
                               dp[i - 1] + nums[0] + 2 * nums[1] + nums[i])
        ac.st(dp[-1])
        return

    @staticmethod
    def lg_p1868(ac=FastIO()):
        # 模板：线性DP加二分查找优化
        n = ac.read_int()
        nums = [ac.read_list_ints() for _ in range(n)]
        dp = [0] * (n + 1)
        nums.sort(key=lambda it: it[1])
        pre = []
        for i in range(n):
            x, y = nums[i]
            dp[i + 1] = dp[i]
            j = bisect.bisect_right(pre, x - 1) - 1
            dp[i + 1] = ac.max(dp[i + 1], dp[j + 1] + y - x + 1)
            pre.append(y)
        ac.st(dp[-1])
        return

    @staticmethod
    def lg_p1978(ac=FastIO()):
        # 模板：经典线性DP，乘积互斥
        n, k = ac.read_list_ints()
        nums = ac.read_list_ints()
        dct = set(nums)
        ans = 0
        for num in nums:
            if num % k == 0 and num // k in dct:
                continue
            # 找出x..kx..k^2x..
            x = 0
            while num in dct:
                x += 1
                num *= k
            ans += (x + 1) // 2
        ac.st(ans)
        return

    @staticmethod
    def lg_p2246(ac=FastIO()):
        # 模板：字符串计数线性DP
        s = ""
        while True:
            cur = ac.read_str()
            if not cur or cur == "eof":
                break
            s += cur.lower()
        t = list("HelloWorld".lower())
        dct = set(t)
        ind = defaultdict(list)
        for i, w in enumerate(t):
            ind[w].append(i)
        m = len(t)
        pre = [0] * m
        mod = 10 ** 9 + 7
        for w in s:
            if w not in dct:
                continue
            cur = pre[:]
            for i in ind[w]:
                if i:
                    cur[i] += pre[i - 1]
                else:
                    cur[i] += 1
            pre = [num % mod for num in cur]
        ac.st(pre[-1])
        return

    @staticmethod
    def lg_p2359(ac=FastIO()):
        # 模板：预处理素数加线性DP
        primes = NumberTheory().sieve_of_eratosthenes(10000)
        primes = [str(num) for num in primes if 1000 >
                  num >= 100 and "0" not in str(num)]
        cnt = defaultdict(list)
        for num in primes:
            cnt[num[:-1]].append(num)
        pre = defaultdict(int)
        for num in primes:
            pre[num[1:]] += 1
        # 转移计算
        mod = 10**9 + 9
        n = ac.read_int()
        for _ in range(n - 3):
            cur = defaultdict(int)
            for num in pre:
                for nex in cnt[num]:
                    cur[nex[1:]] += pre[num]
            pre = defaultdict(int)
            for num in cur:
                pre[num] = cur[num] % mod
        ans = sum(pre.values()) % mod
        ac.st(ans)
        return

    @staticmethod
    def lg_p2432(ac=FastIO()):

        # 模板：线性DP加指针
        w, n = ac.read_list_ints()
        sentence = ac.read_str()
        words = [ac.read_str()[::-1] for _ in range(w)]

        dp = [inf] * (n + 1)
        dp[0] = 0
        for x in range(n):
            ind = [0] * w
            for j in range(x, -1, -1):
                cur = x - j + 1
                # 比对每个单词的匹配长度
                for i in range(w):
                    m = len(words[i])
                    if ind[i] < m and sentence[j] == words[i][ind[i]]:
                        ind[i] += 1
                    if ind[i] == m:
                        cur = ac.min(cur, x - j + 1 - m)
                dp[x + 1] = ac.min(dp[x + 1], dp[j] + cur)
        ac.st(dp[-1])
        return

    @staticmethod
    def lg_p2439(ac=FastIO()):
        # 模板：线性DP加二分
        n = ac.read_int()
        nums = [ac.read_list_ints() for _ in range(n)]
        nums.sort(key=lambda it: it[1])
        dp = [0] * (n + 1)
        pre = []
        for i in range(n):
            a, b = nums[i]
            j = bisect.bisect_right(pre, a)
            dp[i + 1] = ac.max(dp[i], dp[j] + b - a)
            pre.append(b)
        ac.st(dp[-1])
        return

    @staticmethod
    def lg_p2476(ac=FastIO()):

        # 模板：计数分组线性 DP 记忆化搜索

        @lru_cache(None)
        def dfs(a, b, c, d, e, pre):
            if a + b + c + d + e == 0:
                return 1
            res = 0
            if a:
                res += (a - int(pre == 2)) * dfs(a - 1, b, c, d, e, 1)
            if b:
                res += (b - int(pre == 3)) * dfs(a + 1, b - 1, c, d, e, 2)
            if c:
                res += (c - int(pre == 4)) * dfs(a, b + 1, c - 1, d, e, 3)
            if d:
                res += (d - int(pre == 5)) * dfs(a, b, c + 1, d - 1, e, 4)
            if e:
                res += e * dfs(a, b, c, d + 1, e - 1, 5)
            res %= mod
            return res

        ac.read_int()
        color = ac.read_list_ints()
        mod = 10**9 + 7
        cnt = Counter(color)
        ac.st(dfs(cnt[1], cnt[2], cnt[3], cnt[4], cnt[5], -1))
        return

    @staticmethod
    def lg_p2849(ac=FastIO()):
        # 模板：矩阵二维 DP 线性遍历
        n, k = ac.read_list_ints()
        nums = [ac.read_list_ints() for _ in range(n)]
        dis = [[0] * n for _ in range(n)]
        for i in range(n):
            x1, y1 = nums[i]
            for j in range(i + 1, n):
                x2, y2 = nums[j]
                dis[i][j] = abs(x1 - x2) + abs(y1 - y2)

        dp = [[inf] * (k + 1) for _ in range(n)]
        dp[0][0] = 0
        for i in range(1, n):
            dp[i][0] = dp[i - 1][0] + dis[i - 1][i]
            for j in range(1, k + 1):
                for x in range(i - 1, -1, -1):
                    skip = i - x - 1
                    if j - skip < 0:
                        break
                    dp[i][j] = ac.min(dp[i][j], dp[x][j - skip] + dis[x][i])
        ac.st(dp[-1][-1])
        return

    @staticmethod
    def lg_p3558(ac=FastIO()):
        # 模板：线性 DP 模拟
        ac.read_int()
        nums = ac.read_list_ints()
        pre = [inf, inf, inf]
        pre[nums[0]] = 0
        for num in nums[1:]:
            cur = [inf, inf, inf]
            for x in [-1, 0, 1]:
                for k in range(3):
                    y = num + k * x
                    if x <= y and -1 <= y <= 1:
                        cur[y] = ac.min(cur[y], pre[x] + k)
            pre = cur[:]
        ans = min(pre)
        ac.st(ans if ans < inf else "BRAK")
        return

    @staticmethod
    def lc_2746(words: List[str]) -> int:
        # 模板：经典哈希线性DP模拟实现
        pre = defaultdict(int)
        pre[words[0][0] + words[0][-1]] = len(words[0])

        for a in words[1:]:
            cur = defaultdict(lambda: inf)
            for b in pre:
                # a+b
                if a[-1] == b[0]:
                    x = len(a) - 1 + pre[b]
                else:
                    x = len(a) + pre[b]
                cur[a[0] + b[-1]] = min(cur[a[0] + b[-1]], x)

                # b+a
                if b[-1] == a[0]:
                    x = len(a) - 1 + pre[b]
                else:
                    x = len(a) + pre[b]
                cur[b[0] + a[-1]] = min(cur[b[0] + a[-1]], x)
            pre = cur

        return min(pre.values())

    @staticmethod
    def lg_b3734(ac=FastIO()):
        # 模板：线性矩阵 DP 模拟
        n, r1 = ac.read_list_ints()
        nums = [r1]
        while len(nums) < n:
            nums.append((nums[-1] * 6807 + 2831) % 201701)
        nums = [num % 100 for num in nums]

        # 使用滚动数组优化
        dp = [[inf] * 100 for _ in range(2)]
        # 初始化
        pre = 0
        for x in range(100):
            y = abs(x - nums[0])
            dp[pre][x] = ac.min(y * y, (100 - y) * (100 - y))
        for i in range(1, n):
            cur = 1 - pre
            for j in range(100):
                y = abs(j - nums[i])
                res = inf
                a = ac.min(y * y, (100 - y) * (100 - y))
                for k in range(j):
                    res = ac.min(res, a + dp[pre][k])
                dp[cur][j] = res
            pre = cur
        ac.st(min(dp[pre]))
        return

    @staticmethod
    def lg_p3901(ac=FastIO()):
        # 模板：经典指针加线性 DP 记录前一个相同数的指针
        n, q = ac.read_list_ints()
        nums = ac.read_list_ints()
        ind = dict()
        for i in range(n):
            x = nums[i]
            if x in ind:
                nums[i] = ind[x]
            else:
                nums[i] = -1
            ind[x] = i
            if i:
                nums[i] = ac.max(nums[i], nums[i - 1])
        for _ in range(q):
            left, right = ac.read_list_ints_minus_one()
            ac.st("Yes" if nums[right] < left else "No")
        return

    @staticmethod
    def lg_p4401(ac=FastIO()):
        # 模板：线性 DP
        ac.read_int()
        s = ac.read_str()
        pre = defaultdict(int)
        pre[("", "")] = 0
        for w in s:
            cur = defaultdict(int)
            for p1, p2 in pre:
                # 装第一个车
                st = p1 + w
                cur[(st[-2:], p2)] = ac.max(cur[(st[-2:], p2)],
                                            pre[(p1, p2)] + len(set(st)))
                # 装第二个车
                st = p2 + w
                cur[(p1, st[-2:])] = ac.max(cur[(p1, st[-2:])],
                                            pre[(p1, p2)] + len(set(st)))
            pre = cur
        ac.st(max(pre.values()))
        return

    @staticmethod
    def lg_p5095(ac=FastIO()):
        # 模板：典型线性 DP
        n, length = ac.read_list_ints()
        nums = [ac.read_list_ints() for _ in range(n)]
        dp = [inf] * (n + 1)
        dp[0] = 0
        for i in range(n):
            w = h = 0
            for j in range(i, -1, -1):
                w += nums[j][1]
                h = ac.max(h, nums[j][0])
                if w > length:
                    break
                if dp[j] + h < dp[i + 1]:
                    dp[i + 1] = dp[j] + h
        ac.st(dp[-1])
        return

    @staticmethod
    def lg_p5810(ac=FastIO()):
        # 模板：经典线性 DP 枚举
        n = ac.read_int()
        dp = [0]
        while dp[-1] < n:
            m = len(dp)
            cur = dp[-1] + 1
            x = 1
            while x * 2 + 5 <= m:
                cur = ac.max(dp[-x * 2 - 5] * (x + 1), cur)
                x += 1
            dp.append(cur)
        ac.st(len(dp) - 1)
        return

    @staticmethod
    def lg_p6040(ac=FastIO()):
        # 模板：单调队列优化的线性 DP
        n, k, d, x, tp = ac.read_list_ints()
        mod = 10**9
        nums = []
        seed = 0
        xx = int("0x66CCFF", 16)
        if tp == 0:
            nums = ac.read_list_ints()
        else:
            seed = ac.read_int()
            seed = (seed * xx % mod + 20120712) % mod
        # 使用公式变换确定要计算的单调队列值
        pre = nums[0] if not tp else seed
        stack = deque([[0, pre - d]])
        for i in range(1, n):
            seed = nums[i] if not tp else (seed * xx % mod + 20120712) % mod
            # 出队
            while stack and stack[0][0] < i - x:
                stack.popleft()
            cur = pre + seed + k
            if stack:
                # 当前最小值计算
                cur = ac.min(cur, stack[0][1] + i * d + seed + k)
            # 进队
            while stack and stack[-1][1] >= cur - i * d - d:
                stack.pop()
            stack.append([i, cur - i * d - d])
            pre = cur
        ac.st(pre)
        return

    @staticmethod
    def lg_p6120(ac=FastIO()):
        # 模板：典型线性规划
        n = ac.read_int()
        ind = {w: i for i, w in enumerate("HSP")}
        # 滚动数组更新
        dp = [[[0, -inf], [0, -inf], [0, -inf]] for _ in range(2)]
        pre = 0
        for _ in range(n):
            cur = 1 - pre
            i = ind[ac.read_str()]
            w = (i - 1) % 3
            for j in range(3):
                dp[cur][j][0] = dp[pre][j][0]  # 当前出 j 且未作改变的最大值
                # 当前出 j 且作出改变的最大值
                dp[cur][j][1] = max(
                    dp[pre][j][1], max(
                        dp[pre][k][0] for k in range(3) if k != j))
                if j == w:  # 当前局为胜手
                    dp[cur][j][0] += 1
                    dp[cur][j][1] += 1
            pre = cur
        ac.st(max(max(d) for d in dp[pre]))
        return

    @staticmethod
    def lg_p6146(ac=FastIO()):
        # 模板：经典区间排序与所有子集连通块个数计算
        n = ac.read_int()
        nums = [ac.read_list_ints() for _ in range(n)]
        nums.sort(key=lambda it: it[0])
        mod = 10**9 + 7
        pp = [1] * (n + 1)
        for i in range(1, n + 1):
            pp[i] = (pp[i - 1] * 2) % mod
        # dp[i]表示前 i 个区间的结果
        dp = [0] * n
        dp[0] = 1
        lst = [nums[0][1]]
        for i in range(1, n):
            a, b = nums[i]
            j = bisect.bisect_left(lst, a)  # 作为 i 单独连通块新增的计数即与前面区间无交集
            # 选当前 i 与不选当前 i 区间的连通块数量
            dp[i] = 2 * dp[i - 1] + pp[j]
            dp[i] %= mod
            bisect.insort_left(lst, b)
        ac.st(dp[-1])
        return

    @staticmethod
    def lc_2713(mat: List[List[int]]) -> int:
        # 模板：按照值域分层线性 DP
        m, n = len(mat), len(mat[0])
        dct = defaultdict(list)
        for i in range(m):
            for j in range(n):
                dct[mat[i][j]].append([i, j])
        row = [0] * m
        col = [0] * n
        for val in sorted(dct):
            lst = []
            for i, j in dct[val]:
                x = row[i] if row[i] > col[j] else col[j]
                lst.append([i, j, x + 1])
            for i, j, w in lst:
                if col[j] < w:
                    col[j] = w
                if row[i] < w:
                    row[i] = w
        return max(max(row), max(col))

    @staticmethod
    def lg_p7994(ac=FastIO()):
        # 模板：经典线性 DP 修改连续区间值加一减一的最少操作次数
        n = ac.read_int()
        a = ac.read_list_ints()
        b = ac.read_list_ints()

        nums = [a[i] - b[i] for i in range(n)]
        ans = abs(nums[0])
        for i in range(1, n):
            x, y = nums[i - 1], nums[i]
            if x == 0:
                ans += abs(y)
            elif y == 0:
                continue
            else:
                if x * y < 0:
                    ans += abs(y)
                else:
                    if x > 0:
                        ans += ac.max(0, y - x)
                    else:
                        ans += ac.max(0, x - y)
        ac.st(ans)
        return

    @staticmethod
    def lg_p8816(ac=FastIO()):
        # 模板：典型线性矩阵 DP 模拟
        n, k = ac.read_list_ints()
        nums = sorted([ac.read_list_ints() for _ in range(n)])
        dp = [list(range(1, k + 2)) for _ in range(n)]
        for i in range(n - 1, -1, -1):
            x, y = nums[i]
            for j in range(i + 1, n):
                a, b = nums[j]
                if a >= x and b >= y:
                    dis = a - x + b - y - 1
                    for r in range(k + 1):
                        if r + dis <= k:
                            dp[i][r + dis] = ac.max(dp[i]
                                                    [r + dis], dp[j][r] + dis + 1)
                        else:
                            break
        ac.st(max(max(d) for d in dp))
        return

    @staticmethod
    def ac_4414(ac=FastIO()):
        # 模板：经典线性子序列DP
        ac.read_int()
        nums = ac.read_list_ints()
        ans = -inf
        pre = [-inf, -inf]
        for num in nums:
            cur = pre[:]
            # 枚举所有子序列加和
            for i in range(2):
                j = (i + num) % 2
                cur[j] = ac.max(cur[j], pre[i] + num)
                j = num % 2
                cur[j] = ac.max(cur[j], num)
            pre = cur[:]
            ans = ac.max(ans, pre[1])
        ac.st(ans)
        return

    @staticmethod
    def lc_1824(obstacles: List[int]) -> int:
        # 模板：经典线性DP滚动数组
        n = len(obstacles)
        dp = [1, 0, 1]
        for i in range(n):
            x = obstacles[i]
            if x:
                dp[x - 1] = inf
            low = min(dp)
            for j in range(3):
                if j != x - 1:
                    dp[j] = dp[j] if dp[j] < low + 1 else low + 1
        return min(dp)

    @staticmethod
    def lc_978(arr: List[int]) -> int:
        # 模板：经典线性DP滚动变量
        n = len(arr)
        ans = dp0 = dp1 = 1
        for i in range(1, n):
            if arr[i] > arr[i - 1]:
                dp1 = dp0 + 1
                dp0 = 1
            elif arr[i] < arr[i - 1]:
                dp0 = dp1 + 1
                dp1 = 1
            else:
                dp0 = dp1 = 1
            ans = ans if ans > dp0 else dp0
            ans = ans if ans > dp1 else dp1
        return ans

    @staticmethod
    def lc_1027(nums: List[int]) -> int:
        # 模板：经典线性DP计算最长等差子序列
        seen = set()
        count = dict()
        for num in nums:
            for pre in seen:
                d = num - pre
                count[(num, d)] = count.get((pre, d), 1) + 1
            seen.add(num)
        return max(count.values())

    @staticmethod
    def lc_1553(n: int) -> int:

        # 模板：脑筋急转弯贪心记忆化搜索线性DP

        @lru_cache(None)
        def dfs(num):
            if num <= 1:
                return num
            a = num % 2 + 1 + dfs(num // 2)
            b = num % 3 + 1 + dfs(num // 3)
            return a if a < b else b

        return dfs(n)
