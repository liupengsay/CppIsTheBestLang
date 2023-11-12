import unittest
from functools import lru_cache

from src.dp.digital_dp.template import DigitalDP
from src.utils.fast_io import FastIO

"""
算法：数位DP
功能：统计满足一定条件的自然数个数，也可以根据字典序大小特点统计一些特定字符串的个数，是一种计数常用的DP思想

题目：

===================================力扣===================================
233. 数字 1 的个数（https://leetcode.cn/problems/number-of-digit-one/）数字 1 的个数
357. 统计各位数字都不同的数字个数（https://leetcode.cn/problems/count-numbers-with-unique-digits/）排列组合也可用数位 DP 求解
600. 不含连续 1 的非负整数（https://leetcode.cn/problems/non-negative-integers-without-consecutive-ones/）不含连续 1 的非负整数
902. 最大为 N 的数字组合（https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/）限定字符情况下小于等于 n 的个数
1012. 至少有 1 位重复的数字（https://leetcode.cn/problems/numbers-with-repeated-digits/）容斥原理计算没有重复数字的个数
1067. 范围内的数字计数（https://leetcode.cn/problems/digit-count-in-range/）计算区间计数，使用右端点减去左端点，数位DP容斥模板题
1397. 找到所有好字符串（https://leetcode.cn/problems/find-all-good-strings/）使用数位DP思想进行模拟
2376. 统计特殊整数（https://leetcode.cn/problems/count-special-integers/）计算小于 n 的特殊正整数个数
2719. 统计整数数目（https://leetcode.cn/problems/count-of-integers/）数位DP容斥模板题
2801. 统计范围内的步进数字数目（https://leetcode.cn/problems/count-stepping-numbers-in-range/）数位DP容斥模板题
2827. 范围中美丽整数的数目（https://leetcode.cn/problems/number-of-beautiful-integers-in-the-range/）数位DP容斥模板题


面试题 17.06. 2出现的次数（https://leetcode.cn/problems/number-of-2s-in-range-lcci/）所有数位出现 2 的次数

===================================AtCoder===================================
D - XOR World（https://atcoder.jp/contests/abc121/tasks/abc121_d）正解为(2*n)^(2*n+1)=1的性质，可使用数位DP计算 1^2^...^num的值
E - Digit Products（https://atcoder.jp/contests/abc208/tasks/abc208_e）脑筋急转弯，有技巧地处理数位DP结果计算

===================================洛谷===================================
P1590 失踪的7（https://www.luogu.com.cn/problem/P1590）计算 n 以内不含7的个数
P1239 计数器（https://www.luogu.com.cn/problem/P1239）计算 n 以内每个数字0-9的个数
P3908 数列之异或（https://www.luogu.com.cn/problem/P3908）计算 1^2..^n的异或和，可以使用数位DP计数也可以用相邻的奇偶数计算
P1836 数页码（https://www.luogu.com.cn/problem/P1836）数位DP计算1~n内所有数字的数位和


神奇数（https://www.lanqiao.cn/problems/5891/learning/?contest_id=145）容斥原理与数位DP

参考：OI WiKi（xx）
"""


class Solution:
    def __init__(self):
        return

    @staticmethod
    def abc_121d(ac=FastIO()):
        # 模板：正解为 n^(n+1) == 1 (n%2==0) 的性质
        def count(num):
            # 模板：使用数位DP计算 1^2^...^num的值
            @lru_cache(None)
            def dfs(i, cnt, is_limit, is_num):
                if i == n:
                    if is_num:
                        return cnt
                    return 0
                res = 0
                if not is_num:
                    res += dfs(i + 1, 0, False, False)

                floor = 0 if is_num else 1
                ceil = int(s[i]) if is_limit else 9
                for x in range(floor, ceil + 1):
                    res += dfs(i + 1, cnt + int(i == d and x == 1),
                               is_limit and ceil == x, True)
                return res

            if num <= 0:
                return 0
            s = bin(num)[2:]
            n = len(s)
            ans = 0
            for d in range(n):
                c = dfs(0, 0, True, False)
                dfs.cache_clear()
                if c % 2:
                    ans += 1 << (n - d - 1)
            return ans

        a, b = ac.read_list_ints()
        ac.st(count(b) ^ count(a - 1))
        return

    @staticmethod
    def abc_208e(ac=FastIO()):
        # 模板：有技巧地处理数位DP结果计算

        @lru_cache(None)
        def dfs(i, is_limit, is_num, pre):
            if i == m:
                return int(is_num) and pre <= k
            res = 0
            if not is_num:
                res += dfs(i + 1, False, False, 0)
            low = 0 if is_num else 1
            high = int(st[i]) if is_limit else 9
            for x in range(low, high + 1):
                y = pre * x if is_num else x
                if y > k:
                    y = k + 1
                res += dfs(i + 1, is_limit and high == x, True, y)
            return res

        n, k = ac.read_list_ints()
        st = str(n)
        m = len(st)
        ans = dfs(0, True, False, 0)
        ac.st(ans)
        return

    @staticmethod
    def lc_233(n: int) -> int:
        # 模板：计算 0 到 n 有数位 1 的出现次数
        if not n:
            return 0
        return DigitalDP().count_digit(n, 1)

    @staticmethod
    def lc_2719(num1: str, num2: str, min_sum: int, max_sum: int) -> int:
        # 模板：数位DP容斥模板题

        def check(num):
            @lru_cache(None)
            def dfs(i, cnt, is_limit, is_num):
                if i == n:
                    if is_num:
                        return 1 if min_sum <= cnt <= max_sum else 0
                    return 0

                res = 0
                if not is_num:
                    res += dfs(i + 1, 0, False, False)
                floor = 0 if is_num else 1
                ceil = int(s[i]) if is_limit else 9
                for x in range(floor, ceil + 1):
                    if cnt + x <= max_sum:
                        res += dfs(i + 1, cnt + x, is_limit and ceil == x, True)
                    res %= mod
                return res

            s = str(num)
            n = len(s)
            ans = dfs(0, 0, True, False)
            dfs.cache_clear()
            return ans

        mod = 10 ** 9 + 7
        num2 = int(num2)
        num1 = int(num1)
        return (check(num2) - check(num1 - 1)) % mod

    @staticmethod
    def lc_2801(low: str, high: str) -> int:
        # 模板：数位DP容斥模板题

        def check(num):
            @lru_cache(None)
            def dfs(i, is_limit, is_num, pre):
                if i == n:
                    return is_num
                res = 0
                if not is_num:
                    res += dfs(i + 1, False, 0, -1)

                floor = 0 if is_num else 1
                ceil = int(s[i]) if is_limit else 9
                for x in range(floor, ceil + 1):
                    if pre == -1 or abs(x - pre) == 1:
                        res += dfs(i + 1, is_limit and ceil == x, 1, x)
                return res

            s = str(num)
            n = len(s)
            return dfs(0, True, 0, -1)

        mod = 10 ** 9 + 7
        return (check(int(high)) - check(int(low) - 1)) % mod

    @staticmethod
    def lc_2827(low: int, high: int, k: int) -> int:
        # 模板：数位DP容斥模板题

        def check(num):
            @lru_cache(None)
            def dfs(i, is_limit, is_num, odd, rest):
                if i == n:
                    return 1 if is_num and not odd and not rest else 0
                res = 0
                if not is_num:
                    res += dfs(i + 1, False, 0, 0, 0)

                floor = 0 if is_num else 1
                ceil = int(s[i]) if is_limit else 9
                for x in range(floor, ceil + 1):
                    res += dfs(i + 1, is_limit and ceil == x, 1, odd + 1 if x % 2 == 0 else odd - 1,
                               (rest * 10 + x) % k)
                return res

            s = str(num)
            n = len(s)
            return dfs(0, True, 0, 0, 0)

        return check(high) - check(low - 1)

    @staticmethod
    def lg_p1836(ac=FastIO()):
        # 模板：数位DP计算1~n内所有数字的数位和
        n = ac.read_int()
        ans = 0
        for d in range(1, 10):
            ans += d * DigitalDP().count_digit_iteration(n, d)
        ac.st(ans)
        return

    @staticmethod
    def lc_1067(d: int, low: int, high: int) -> int:
        # 模板：计算区间计数，使用右端点减去左端点，数位DP容斥模板题
        dd = DigitalDP()
        return dd.count_digit(high, d) - dd.count_digit(low - 1, d)
