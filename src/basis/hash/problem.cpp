import random
from collections import defaultdict, Counter
from itertools import accumulate
from typing import List

from src.utils.fast_io import FastIO

"""
算法：哈希、贡献法、矩阵哈希、字符串哈希、前缀哈希、后缀哈希
功能：前后缀计数、索引、加和
题目：

===================================力扣===================================
2143. 在两个数组的区间中选取数字（https://leetcode.cn/problems/choose-numbers-from-two-arrays-in-range/）前缀和哈希计数转换为求连续子数组和为 0 的个数
面试题 17.05.  字母与数字（https://leetcode.cn/problems/find-longest-subarray-lcci/）和为0的最长连续子数组，使用前缀和哈希求解
1590. 使数组和能被 P 整除（https://leetcode.cn/problems/make-sum-divisible-by-p/）求和模p与整个子数组模p相等的最短子数组，使用前缀和哈希求解
6317. 统计美丽子数组数目（https://leetcode.cn/contest/weekly-contest-336/problems/count-the-number-of-beautiful-subarrays/）前缀和哈希计数
题目-02. 销售出色区间（https://leetcode.cn/contest/hhrc2022/problems/0Wx4Pc/）前缀和哈希，加脑筋急转弯贪心
题目-03. 重复的彩灯树（https://leetcode.cn/contest/hhrc2022/problems/VAc7h3/）二叉树序列化
2031. 1 比 0 多的子数组个数（https://leetcode.cn/problems/count-subarrays-with-more-ones-than-zeros/）经典前缀和哈希计数
2025. 分割数组的最多方案数（https://leetcode.cn/problems/maximum-number-of-ways-to-partition-an-array/description/）厘清边界使用哈希贡献法计数
895. 最大频率栈（https://leetcode.cn/problems/maximum-frequency-stack/description/）经典哈希与栈的结合应用题
1658. 将 x 减到 0 的最小操作数（https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero/description/）前缀和哈希，加脑筋急转弯贪心
2227. 加密解密字符串（https://leetcode.cn/problems/encrypt-and-decrypt-strings/）经典脑筋急转弯逆向思维

===================================洛谷===================================
P2697 宝石串（https://www.luogu.com.cn/problem/P2697）哈希记录前缀和与对应索引
P1114 “非常男女”计划（https://www.luogu.com.cn/record/list?user=739032&status=12&page=13）哈希记录前缀和与对应索引
P4889 kls与flag（https://www.luogu.com.cn/problem/P4889）经典公式变换使用哈希计数
P6273 [eJOI2017] 魔法（https://www.luogu.com.cn/problem/P6273）经典哈希前缀计数
P8630 [蓝桥杯 2015 国 B] 密文搜索（https://www.luogu.com.cn/problem/P8630）哈希计数与排列枚举

===================================AtCoder===================================
D - Snuke's Coloring（https://atcoder.jp/contests/abc045/tasks/arc061_b）经典哈希容斥计数
C. Train and QueriesC. Train and Queries（https://codeforces.com/contest/1702/problem/C）卡哈希，需要用异或进行变换

===================================AcWing===================================
137. 雪花雪花雪花（https://www.acwing.com/problem/content/139/）哈希找相同雪花

参考：OI WiKi（xx）
"""


class Solution:
    def __init__(self):
        return

    @staticmethod
    def lc_2143(nums1: List[int], nums2: List[int]) -> int:
        # 模板：经典使用哈希计数模拟线性 DP 转移
        n = len(nums1)
        mod = 10**9 + 7
        pre = defaultdict(int)
        pre[-nums1[0]] += 1
        pre[nums2[0]] += 1
        ans = pre[0]
        for i in range(1, n):
            cur = defaultdict(int)
            cur[-nums1[i]] += 1
            cur[nums2[i]] += 1
            for p in pre:
                cur[p - nums1[i]] += pre[p]
                cur[p + nums2[i]] += pre[p]
            ans += cur[0]
            ans %= mod
            pre = cur
        return ans

    @staticmethod
    def lc_1658(nums: List[int], x: int) -> int:
        # 模板：前缀和哈希，加脑筋急转弯贪心
        pre = {0: -1}
        cur = 0
        n = len(nums)
        s = sum(nums)  # 先求和为 s-x 的最长子数组
        ans = -1 if s != x else 0
        for i, w in enumerate(nums):
            cur += w
            if cur - (s-x) in pre and i - pre[cur - (s-x)] > ans:  # 要求非空
                ans = i - pre[cur - (s-x)]
            if cur not in pre:
                pre[cur] = i
        return n-ans if ans > -1 else ans

    @staticmethod
    def lc_2025(nums: List[int], k: int) -> int:

        # 模板：厘清边界使用哈希贡献法计数
        n = len(nums)
        ans = 0
        pre = list(accumulate(nums, initial=0))
        for i in range(1, n):
            if pre[i] == pre[-1] - pre[i]:
                ans += 1

        # 左-右
        cnt = [0] * n
        post = defaultdict(int)
        for i in range(n - 2, -1, -1):
            b = pre[-1] - pre[i + 1]
            a = pre[i + 1]
            post[a - b] += 1
            # 作为左边
            cnt[i] += post[nums[i] - k]

        # 右-左
        dct = defaultdict(int)
        for i in range(1, n):
            b = pre[-1] - pre[i]
            a = pre[i]
            dct[a - b] += 1
            # 作为右边
            cnt[i] += dct[k - nums[i]]

        return max(ans, max(cnt))

    @staticmethod
    def abc_45d(ac=FastIO()):
        # 模板：经典哈希容斥计数
        h, w, n = ac.read_list_ints()
        cnt = [0]*10
        dct = defaultdict(int)
        for _ in range(n):
            a, b = ac.read_list_ints()
            for x in range(3):
                for y in range(3):
                    if 3 <= x+a <= h and 3 <= y+b <= w:
                        dct[(x+a, y+b)] += 1
        for k in dct:
            cnt[dct[k]] += 1

        cnt[0] = (h-2)*(w-2) - sum(cnt[1:])
        for a in cnt:
            ac.st(a)
        return

    @staticmethod
    def ac_137(ac=FastIO()):

        p1 = random.randint(26, 100)
        p2 = random.randint(26, 100)
        mod1 = random.randint(10 ** 9 + 7, 2 ** 31 - 1)
        mod2 = random.randint(10 ** 9 + 7, 2 ** 31 - 1)

        def compute(ls):
            res1 = 0
            for num in ls:
                res1 *= p1
                res1 += num
                res1 %= mod1
            res2 = 0
            for num in ls:
                res2 *= p2
                res2 += num
                res2 %= mod2
            return res1, res2

        def check():
            res = []
            for ii in range(6):
                cu = tuple(lst[ii:]+lst[:ii])
                res.append(compute(cu))
                cu = tuple(lst[:ii+1][::-1]+lst[ii+1:][::-1])
                res.append(compute(cu))
            return res

        n = ac.read_int()
        pre = set()
        ans = False
        for _ in range(n):
            if ans:
                break
            lst = ac.read_list_ints()
            now = check()
            if any(cur in pre for cur in now):
                ans = True
                break
            for cur in now:
                pre.add(cur)

        if ans:
            ac.st("Twin snowflakes found.")
        else:
            ac.st("No two snowflakes are alike.")
        return

    @staticmethod
    def lg_p4889(ac=FastIO()):
        # 模板：枚举计数
        n, m = ac.read_list_ints()
        height = ac.read_list_ints()
        cnt = defaultdict(int)
        ans = 0
        for i in range(n):
            # hj - hi = j - i
            ans += cnt[height[i] - i]
            cnt[height[i] - i] += 1

        cnt = defaultdict(int)
        for i in range(n):
            # hi - hj = j - i
            ans += cnt[height[i] + i]
            # hj + hi = j - i
            ans += cnt[i - height[i]]
            cnt[height[i] + i] += 1
        ac.st(ans)
        return

    @staticmethod
    def lg_p6273(ac=FastIO()):
        # 模板：经典哈希前缀计数
        ac.read_int()
        s = ac.read_str()
        # 选择最少出现的字符作为减数
        ct = Counter(s)
        st = list(ct.keys())
        ind = {w: i for i, w in enumerate(st)}
        m = len(ind)
        x = 0
        for i in range(1, m):
            if ct[st[i]] < ct[st[x]]:
                x = i
        # 记录状态
        cnt = [0] * m
        pre = defaultdict(int)
        pre[tuple(cnt)] = 1
        ans = 0
        mod = 10**9 + 7
        for w in s:
            if w == st[x]:
                # 其余所有字符减 1
                for i in range(m):
                    if i != ind[w]:
                        cnt[i] -= 1
            else:
                # 减数字符加 1
                cnt[ind[w]] += 1
            tp = tuple(cnt)
            # sa-ta = sb-tb 则有 sa-sb = ta-tb 因此这样计数
            ans += pre[tp]
            pre[tp] += 1
            ans %= mod
        ac.st(ans)
        return


class LC895:
    # 模板：经典哈希与栈的结合应用题
    def __init__(self):
        self.freq = defaultdict(list)
        self.dct = defaultdict(int)
        self.ceil = 0

    def push(self, val: int) -> None:
        self.dct[val] += 1
        self.freq[self.dct[val]].append(val)
        if self.dct[val] > self.ceil:
            self.ceil = self.dct[val]
        return

    def pop(self) -> int:
        val = self.freq[self.ceil].pop()
        self.dct[val] -= 1
        if not self.freq[self.ceil]:
            self.ceil -= 1
        return val
