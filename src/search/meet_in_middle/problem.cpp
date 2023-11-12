"""
算法：折半搜索、meet in middle
功能：常见于 1<<n 较大的情况，对半分开进行枚举 
题目：

===================================力扣===================================
1755. 最接近目标值的子序列和（https://leetcode.cn/problems/closest-subsequence-sum/）经典折半搜索
2035. 将数组分成两个数组并最小化数组和的差（https://leetcode.cn/problems/partition-array-into-two-arrays-to-minimize-sum-difference/）经典折半搜索排序加二分或者双指针
956. 最高的广告牌（https://leetcode.cn/problems/tallest-billboard/description/）可使用折半搜索计算

===================================洛谷===================================
P5194 [USACO05DEC]Scales S（https://www.luogu.com.cn/problem/P5194）利用Fibonacci数列的长度特点进行折半搜索枚举，与二分查找确定可行的最大值
Anya and Cubes（https://www.luogu.com.cn/problem/CF525E）折半搜索计算长度
P5691 [NOI2001] 方程的解数（https://www.luogu.com.cn/problem/P5691）折半搜索与有序集合双指针枚举

===================================AcWing======================================
171. 送礼物（https://www.acwing.com/problem/content/173/）经典折半搜索查找最接近目标值的子数组和
F. Xor-Paths（https://codeforces.com/contest/1006/problem/F）前缀和哈希计数，矩阵折半搜索

参考：OI WiKi（xx）
"""

import bisect
from collections import defaultdict
from itertools import combinations
from math import inf
from typing import List

from src.utils.fast_io import FastIO


class Solution:
    def __init__(self):
        return

    @staticmethod
    def lc_956(rods: List[int]) -> int:

        # 模板：可使用折半搜索计算

        def check(tmp):
            dct = dict()
            n = len(tmp)

            def dfs(i):
                nonlocal total, pos
                if i == n:
                    if pos > dct.get(total, -inf):
                        dct[total] = pos
                    return
                for d in [-1, 0, 1]:
                    total += d * tmp[i]
                    pos += tmp[i] if d == 1 else 0
                    dfs(i + 1)
                    total -= d * tmp[i]
                    pos -= tmp[i] if d == 1 else 0
                return

            pos = total = 0
            dfs(0)
            return dct

        m = len(rods)
        pre = check(rods[:m // 2])
        post = check(rods[m // 2:])
        ans = 0
        for k in pre:
            if -k in post:
                cur = pre[k] + post[-k]
                ans = ans if ans > cur else cur
        return ans

    @staticmethod
    def lc_2035(nums: List[int]) -> int:
        # 模板：经典折半搜索排序加二分或者双指针

        def check(lst):
            # 枚举列表元素所有个数的子集和
            m = len(lst)
            total = sum(lst)
            res = [set() for _ in range(m + 1)]
            res[0].add(0)
            res[m].add(total)
            # 类似计算数的因子的思想只需要搜索到一半即可，另一半做差得到
            for k in range(1, m // 2 + 1):
                for item in combinations(lst, k):
                    cur = sum(item)
                    res[k].add(cur)
                    res[m - k].add(total - cur)
            return res

        def find(left, right):
            # 双指针查找最接近target的绝对差值
            a, b = len(left), len(right)
            res = float("inf")
            i = 0
            j = b - 1
            while i < a and j >= 0:
                cur = abs(target - left[i] - right[j])
                res = res if res < cur else cur
                if left[i] + right[j] == target:
                    return 0
                if left[i] + right[j] > target:
                    j -= 1
                elif left[i] + right[j] < target:
                    i += 1
            return res

        # 枚举前一半个数与后一半对应的个数子集和，找到绝对差最小的结果
        n = len(nums) // 2
        pre = check(nums[:n])
        post = check(nums[n:])
        ans = float("inf")
        target = sum(nums) / 2
        for k in range(n + 1):
            cur = find(sorted(list(pre[k])), sorted(list(post[n - k])))
            ans = ans if ans < 2 * cur else 2 * cur
        return int(ans)

    @staticmethod
    def lg_p5194(ac=FastIO()):
        # 模板：折半搜索枚举后使用二分寻找最接近目标值的数
        n, c = ac.read_list_ints()
        val = [ac.read_int() for _ in range(n)]

        def check(lst):
            s = len(lst)
            pre = 0
            res = set()

            def dfs(i):
                nonlocal pre
                if pre > c:
                    return
                if i == s:
                    res.add(pre)
                    return
                pre += lst[i]
                dfs(i + 1)
                pre -= lst[i]
                dfs(i + 1)
                return

            dfs(0)
            return sorted(list(res))

        res1 = check(val[:n // 2])
        res2 = check(val[n // 2:])
        ans = max(max(res1), max(res2))
        for num in res2:
            i = bisect.bisect_right(res1, c - num) - 1
            if i >= 0:
                ans = ans if ans > num + res1[i] else num + res1[i]
        ac.st(ans)
        return

    @staticmethod
    def cf_1006f(ac=FastIO()):
        # 模板：前缀和哈希计数，矩阵折半搜索
        m, n, k = ac.read_list_ints()
        grid = [ac.read_list_ints() for _ in range(m)]
        if m == 1 or n == 1:
            res = 0
            for g in grid:
                for num in g:
                    res ^= num
            ac.st(1 if res == k else 0)
            return

        left = (m + n - 2) // 2
        right = m + n - 2 - left
        pre = [[defaultdict(int) for _ in range(n)] for _ in range(m)]
        for i in range(m):
            for j in range(n):
                if i + j > left:
                    break
                if i == j == 0:
                    cur = defaultdict(int)
                    cur[grid[i][j]] = 1
                else:
                    x = grid[i][j]
                    cur = defaultdict(int)
                    for a, b in [[i - 1, j], [i, j - 1]]:
                        if 0 <= a < m and 0 <= b < n:
                            dct = pre[a][b]
                            for p in dct:
                                cur[p ^ x] += dct[p]
                if i:
                    pre[i - 1][j] = defaultdict(int)
                pre[i][j] = cur

        ans = 0
        post = [[defaultdict(int) for _ in range(n)] for _ in range(m)]
        for i in range(m - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if m - 1 - i + n - 1 - j > right:
                    break
                if i == m - 1 and j == n - 1:
                    cur = defaultdict(int)
                    cur[grid[i][j]] = 1
                else:
                    x = grid[i][j]
                    cur = defaultdict(int)
                    for a, b in [[i + 1, j], [i, j + 1]]:
                        if 0 <= a < m and 0 <= b < n:
                            dct = post[a][b]
                            for p in dct:
                                cur[p ^ x] += dct[p]
                post[i][j] = cur

                if i + 1 < m:
                    post[i + 1][j] = defaultdict(int)

                if m - 1 - i + n - 1 - j == right:
                    for p in cur:
                        ans += pre[i][j][p ^ k ^ grid[i][j]] * cur[p]
        ac.st(ans)
        return

    @staticmethod
    def ac_171(ac=FastIO()):
        # 模板：经典折半搜索查找最接近目标值的子数组和

        w, n = ac.read_list_ints()
        lst = [ac.read_int() for _ in range(n)]
        lst.sort()

        def check(tmp):
            m = len(tmp)
            cur = set()
            stack = [[0, 0]]
            # 使用迭代方式枚举
            while stack:
                x, i = stack.pop()
                if x > w:
                    continue
                if i == m:
                    cur.add(x)
                    continue
                stack.append([x + tmp[i], i + 1])
                stack.append([x, i + 1])
            return cur

        pre = sorted(list(check(lst[:n // 2])))
        post = sorted(list(check(lst[n // 2:])))
        if len(pre) > len(post):
            pre, post = post, pre
        ans = 0
        for num in pre:
            j = bisect.bisect_right(post, w - num) - 1
            ans = max(ans, num)
            if 0 <= j < len(post):
                ans = max(ans, num + post[j])
        ac.st(ans)
        return

    @staticmethod
    def lg_p5691(ac=FastIO()):
        # 模板：折半搜索与枚举
        n = ac.read_int()
        m = ac.read_int()
        nums = [ac.read_list_ints() for _ in range(n)]
        ans = 0
        if n == 1:
            for x1 in range(1, m + 1):
                if nums[0][0] * x1 ** nums[0][1] == 0:
                    ans += 1
            ac.st(ans)
            return
        if n == 2:
            for x1 in range(1, m + 1):
                for x2 in range(1, m + 1):
                    if nums[0][0] * x1 ** nums[0][1] + nums[1][0] * x2 ** nums[1][1] == 0:
                        ans += 1
            ac.st(ans)
            return
        if n == 3:
            for x1 in range(1, m + 1):
                for x2 in range(1, m + 1):
                    for x3 in range(1, m + 1):
                        cur = nums[0][0] * x1 ** nums[0][1] + nums[1][0] * x2 ** nums[1][1] + nums[2][0] * x3 ** \
                              nums[2][1]
                        if cur == 0:
                            ans += 1
            ac.st(ans)
            return

        # 枚举前半部分
        dct = dict()
        for x1 in range(1, m + 1):
            for x2 in range(1, m + 1):
                for x3 in range(1, m + 1):
                    cur = nums[0][0] * x1 ** nums[0][1] + nums[1][0] * x2 ** nums[1][1] + nums[2][0] * x3 ** nums[2][1]
                    dct[cur] = dct.get(cur, 0) + 1

        # 计算后半部分
        nums = nums[3:]
        n = len(nums)
        if n == 1:
            for x1 in range(1, m + 1):
                cur = nums[0][0] * x1 ** nums[0][1]
                ans += dct.get(-cur, 0)
            ac.st(ans)
            return
        if n == 2:
            for x1 in range(1, m + 1):
                for x2 in range(1, m + 1):
                    cur = nums[0][0] * x1 ** nums[0][1] + nums[1][0] * x2 ** nums[1][1]
                    ans += dct.get(-cur, 0)
            ac.st(ans)
            return
        if n == 3:
            for x1 in range(1, m + 1):
                for x2 in range(1, m + 1):
                    for x3 in range(1, m + 1):
                        cur = nums[0][0] * x1 ** nums[0][1] + nums[1][0] * x2 ** nums[1][1] + nums[2][0] * x3 ** \
                              nums[2][1]
                        ans += dct.get(-cur, 0)
            ac.st(ans)
            return
        return
