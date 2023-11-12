"""
算法：区间合并、区间覆盖、区间计数
功能：涉及到区间的一些合并查询和操作，也可以使用差分数组与树状数组、线段树进行解决
用法：合并为不相交的区间、最少区间覆盖问题、最多不相交的区间、最小点覆盖（每条线段至少一个点需要多少点覆盖）、将区间分为不相交的最少组数
最多点匹配覆盖（每条线段选一个点匹配，最多匹配数有点类似二分图）
题目：

===================================力扣===================================
45. 跳跃游戏 II（https://leetcode.cn/problems/jump-game-ii/）转换为最少区间覆盖问题
452. 用最少数量的箭引爆气球（https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/）贪心等价为最多不想交的区间
1326. 灌溉花园的最少水龙头数目（https://leetcode.cn/problems/minimum-number-of-taps-to-open-to-water-a-garden/）转换为最少区间覆盖问题
1024. 视频拼接（https://leetcode.cn/problems/video-stitching/）转换为最少区间覆盖问题
1520. 最多的不重叠子字符串（https://leetcode.cn/problems/maximum-number-of-non-overlapping-substrings/）转化为最多不相交区间进行处理
1353. 最多可以参加的会议数目（https://leetcode.cn/problems/maximum-number-of-events-that-can-be-attended/）贪心选取最多的点，使得每个点一一对应一个区间
2406. 将区间分为最少组数（https://leetcode.cn/problems/divide-intervals-into-minimum-number-of-groups/）将区间分为不相交的最少组数使用贪心与差分数组计数解决
435. 无重叠区间（https://leetcode.cn/problems/non-overlapping-intervals/）最多不相交的区间，使用贪心或者二分DP
763. 划分字母区间（https://leetcode.cn/problems/partition-labels/）经典将区间合并为不相交的区间
6313. 统计将重叠区间合并成组的方案数（https://leetcode.cn/contest/biweekly-contest-99/problems/count-ways-to-group-overlapping-ranges/）经典将区间合并为不相交的区间，再使用快速幂计数
2345. 寻找可见山的数量（https://leetcode.cn/problems/finding-the-number-of-visible-mountains/）二维偏序，转换为区间包含问题
757. 设置交集大小至少为2（https://leetcode.cn/problems/set-intersection-size-at-least-two/）贪心选取最少的点集合，使得每个区间包含其中至少两个点
2589. 完成所有任务的最少时间（https://leetcode.cn/problems/minimum-time-to-complete-all-tasks/）贪心选取最少的点集合，使得每个区间包含其中要求的k个点
LCP 32. 批量处理任务（https://leetcode.cn/problems/t3fKg1/）贪心选取最少的点集合，使得每个区间包含其中要求的k个点

===================================洛谷===================================
P2082 区间覆盖（加强版）（https://www.luogu.com.cn/problem/P2082）经典区间合并确定覆盖范围
P2434 [SDOI2005]区间（https://www.luogu.com.cn/problem/P2434）经典区间合并为不相交的区间
P2970 [USACO09DEC]Selfish Grazing S（https://www.luogu.com.cn/problem/P2970）最多不相交的区间，使用贪心或者二分DP
P6123 [NEERC2016]Hard Refactoring（https://www.luogu.com.cn/problem/P6123）区间合并变形问题
P2684 搞清洁（https://www.luogu.com.cn/problem/P2684）最小区间覆盖，选取最少的区间来进行覆盖
P1233 木棍加工（https://www.luogu.com.cn/problem/P1233）按照一个维度排序后计算另一个维度的最长严格递增子序列的长度，二位偏序，转换为区间包含问题
P1496 火烧赤壁（https://www.luogu.com.cn/problem/P1496）经典区间合并确定覆盖范围
P1668 [USACO04DEC] Cleaning Shifts S（https://www.luogu.com.cn/problem/P1668）转换为最少区间覆盖问题
P2887 [USACO07NOV] Sunscreen G（https://www.luogu.com.cn/problem/P2887）最多点匹配覆盖，每条线段选一个点匹配，最多匹配数有点类似二分图
P3661 [USACO17FEB]Why Did the Cow Cross the Road I S（https://www.luogu.com.cn/problem/P3661）经典区间与点集贪心匹配
P3737 [HAOI2014]遥感监测（https://www.luogu.com.cn/problem/P3737）经典区间点覆盖贪心
P5199 [USACO19JAN]Mountain View S（https://www.luogu.com.cn/problem/P5199）经典区间包含贪心计算最多互不包含的区间个数
P1868 饥饿的奶牛（https://www.luogu.com.cn/problem/P1868）线性DP加二分查找优化，选取并集最大且不想交的区间
P2439 [SDOI2005] 阶梯教室设备利用（https://www.luogu.com.cn/problem/P2439）线性DP加二分查找优化，选取并集最大且不想交的区间

================================CodeForces================================
A. String Reconstruction（https://codeforces.com/problemset/problem/827/A）区间合并为不相交的区间，再贪心赋值
D. Nested Segments（https://codeforces.com/problemset/problem/652/D）二位偏序，转换为区间包含问题
D. Non-zero Segments（https://codeforces.com/problemset/problem/1426/D）贪心选取最少的点集合，使得每个区间包含其中至少一个点
E. Monotonic Renumeration（https://codeforces.com/contest/1102/problem/E）区间合并为不相交的区间
F2. Same Sum Blocks (Hard)（https://codeforces.com/contest/1141/problem/F2）利用前缀和枚举，转化为最多不相交的区间问题

================================AcWing================================
112. 雷达设备（https://www.acwing.com/problem/content/114/）作用范围进行区间贪心
4421. 信号（https://www.acwing.com/problem/content/4424/）经典最少区间覆盖范围问题，相邻可以不相交


参考：OI WiKi（xx）
"""
import bisect
from collections import defaultdict, deque
from math import inf
from typing import List

from src.basis.range.template import Range
from src.data_structure.sorted_list.template import LocalSortedList
from src.utils.fast_io import FastIO


class Solution:
    def __init__(self):
        return

    @staticmethod
    def lg_p1496(ac=FastIO()):
        # 模板：经典区间合并确定覆盖范围
        n = ac.read_int()
        lst = []
        for _ in range(n):
            a, b = [int(w) for w in input().strip().split() if w]
            lst.append([a, b])
        ans = sum(b - a for a, b in Range().merge(lst))
        ac.st(ans)
        return

    @staticmethod
    def lc_45(nums):
        n = len(nums)
        lst = [[i, min(n - 1, i + nums[i])] for i in range(n)]
        if n == 1:  # 注意特判
            return 0
        return Range().cover_less(0, n - 1, lst)

    @staticmethod
    def lc_1326_1(n, ranges):
        # 模板：最少区间覆盖模板题
        m = n + 1
        lst = []
        for i in range(m):
            lst.append([max(i - ranges[i], 0), i + ranges[i]])
        return Range().cover_less(0, n, lst, True)

    @staticmethod
    def lc_1326_2(n: int, ranges: List[int]) -> int:
        # 模板：最少区间覆盖模板题
        lst = []
        for i, r in enumerate(ranges):
            a, b = i - r, i + r
            a = a if a > 0 else 0
            b = b if b < n else n
            lst.append([a, b])
        return Range().minimum_interval_coverage(lst, n, True)

    @staticmethod
    def lc_1024_1(clips, time) -> int:
        # 模板：最少区间覆盖模板题
        return Range().cover_less(0, time, clips)

    @staticmethod
    def lc_1024_2(clips: List[List[int]], time: int) -> int:
        # 模板：最少区间覆盖模板题
        return Range().minimum_interval_coverage(clips, time, True)

    @staticmethod
    def lg_p2684(ac=FastIO()):
        n, t = ac.read_list_ints()
        nums = [ac.read_list_ints() for _ in range(n)]
        ac.st(Range().cover_less(1, t, nums))
        return

    @staticmethod
    def lc_435(intervals):
        # 模板：合并区间
        n = len(intervals)
        return n - Range().disjoint_most(intervals)

    @staticmethod
    def lc_763(s: str) -> List[int]:
        # 模板：合并区间
        dct = defaultdict(list)
        for i, w in enumerate(s):
            if len(dct[w]) >= 2:
                dct[w].pop()
            dct[w].append(i)
        lst = []
        for w in dct:
            lst.append([dct[w][0], dct[w][-1]])
        ans = Range().merge(lst)
        return [y - x + 1 for x, y in ans]

    @staticmethod
    def lc_6313(ranges: List[List[int]]) -> int:
        # 模板：合并为不相交的区间
        cnt = len(Range().merge(ranges))
        mod = 10 ** 9 + 7
        return pow(2, cnt, mod)

    @staticmethod
    def cf_1102e(ac=FastIO()):
        # 模板：区间合并为不相交的区间
        mod = 998244353
        n = ac.read_int()
        nums = ac.read_list_ints()
        dct = defaultdict(list)
        for i in range(n):
            dct[nums[i]].append(i)
        lst = [[dct[num][0], dct[num][-1]] for num in dct]
        ans = len(Range().merge(lst))
        ac.st(pow(2, ans-1, mod))
        return

    @staticmethod
    def cf_1426d(ac=FastIO()):
        # 模板：选取最少的点集合，使得每个区间包含其中至少一个点
        n = ac.read_int()
        nums = ac.read_list_ints()
        pre = 0
        dct = dict()
        dct[pre] = -1
        lst = []
        for i in range(n):
            pre += nums[i]
            if pre in dct:
                lst.append([dct[pre], i])
            dct[pre] = i
        if not lst:
            ac.st(0)
            return
        lst.sort(key=lambda it: [it[1], it[0]])
        ans = 1
        a, b = lst[0]
        for c, d in lst[1:]:
            if b > c + 1:
                continue
            else:
                ans += 1
                b = d
        ac.st(ans)
        return

    @staticmethod
    def ac_112(ac=FastIO()):
        # 模板：区间类型的贪心
        n, d = ac.read_list_ints()
        lst = [ac.read_list_ints() for _ in range(n)]
        if any(abs(y) > d for _, y in lst):
            ac.st(-1)
            return
        for i in range(n):
            x, y = lst[i]
            r = (d * d - y * y)**0.5
            lst[i] = [x - r, x + r]
        lst.sort(key=lambda it: it[0])
        ans = 0
        pre = -inf
        for a, b in lst:
            if a > pre:
                ans += 1
                pre = b
            else:
                pre = ac.min(pre, b)
        ac.st(ans)
        return

    @staticmethod
    def lg_p1668(ac=FastIO()):
        # 模板：最少区间覆盖问题
        n, t = ac.read_list_ints()
        lst = [ac.read_list_ints() for _ in range(n)]
        ans = Range().cover_less(1, t, lst, False)
        ac.st(ans)
        return

    @staticmethod
    def lg_p1668_2(ac=FastIO()):
        # 模板：最少区间覆盖问题
        n, t = ac.read_list_ints()
        t -= 1
        lst = [ac.read_list_ints_minus_one() for _ in range(n)]
        ans = Range().cover_less(0, t, lst, False)
        ac.st(ans)
        return

    @staticmethod
    def lg_p2887(ac=FastIO()):
        # 模板：最多点匹配覆盖，每条线段选一个点匹配，最多匹配数有点类似二分图
        n, m = ac.read_list_ints()
        nums = [ac.read_list_ints() for _ in range(n)]
        nums.sort(key=lambda it: it[1])
        pos = [ac.read_list_ints() for _ in range(m)]
        pos.sort(key=lambda it: it[0])
        ans = 0
        for floor, ceil in nums:
            for i in range(m):
                if pos[i][1] and floor <= pos[i][0] <= ceil:
                    ans += 1
                    pos[i][1] -= 1
                    break
        ac.st(ans)
        return

    @staticmethod
    def lg_p3661(ac=FastIO()):
        # 模板：区间与点集贪心匹配
        n, m = ac.read_list_ints()
        lst = LocalSortedList([ac.read_int() for _ in range(n)])
        nums = [ac.read_list_ints() for _ in range(m)]
        # 按照右边端点排序
        nums.sort(key=lambda it: it[1])
        ans = 0
        for a, b in nums:
            i = lst.bisect_left(a)
            # 选择当前符合条件且最小的
            if 0 <= i < len(lst) and a <= lst[i] <= b:
                ans += 1
                lst.pop(i)
        ac.st(ans)
        return

    @staticmethod
    def lg_p3737(ac=FastIO()):
        # 模板：区间点覆盖贪心
        n, r = ac.read_list_ints()
        lst = []
        while len(lst) < 2*n:
            lst.extend(ac.read_list_ints())
        nums = []
        for i in range(n):
            x, y = lst[2*i], lst[2*i+1]
            if r*r < y*y:
                ac.st(-1)
                return
            d = (r*r-y*y)**0.5
            nums.append([x-d, x+d])
        nums.sort(key=lambda it: it[1])
        ans = 1
        a, b = nums[0]
        for c, d in nums[1:]:
            if b >= c:
                continue
            else:
                ans += 1
                b = d
        ac.st(ans)
        return

    @staticmethod
    def lg_p5199(ac=FastIO()):
        # 模板：经典区间包含贪心计算最多互不包含的区间个数
        n = ac.read_int()
        nums = []
        for _ in range(n):
            x, y = ac.read_list_ints()
            nums.append([x - y, x + y])
        # 左端点升序右端点降序
        nums.sort(key=lambda it: [it[0], -it[1]])
        ans = 0
        pre = -inf
        for a, b in nums:
            # 右端点超出范围则形成新的一个
            if b > pre:
                ans += 1
                pre = b
        ac.st(ans)
        return

    @staticmethod
    def lc_1520(s: str) -> List[str]:

        # 模板：转化为最多不相交的区间进行求解

        ind = defaultdict(deque)
        for i, w in enumerate(s):  # 枚举每种字符的起终点索引
            ind[w].append(i)

        # 将每种字符两端中间部分的字符也扩展到包含所有对应的字符范围
        lst = []
        for w in ind:
            x, y = ind[w][0], ind[w][-1]
            while True:
                x_pre, y_pre = x, y
                for v in ind:
                    i = bisect.bisect_right(ind[v], x)
                    j = bisect.bisect_left(ind[v], y) - 1
                    if 0 <= i <= j < len(ind[v]):
                        if ind[v][0] < x:
                            x = ind[v][0]
                        if ind[v][-1] > y:
                            y = ind[v][-1]
                if x == x_pre and y == y_pre:
                    break
            ind[w].appendleft(x)
            ind[w].append(y)
            lst.append([x, y])

        # 贪心取最多且最短距离的区间覆盖
        lst.sort(key=lambda ls: ls[1])
        ans = []
        for x, y in lst:
            if not ans or x > ans[-1][1]:
                ans.append([x, y])
        return [s[i: j + 1] for i, j in ans]

    @staticmethod
    def ac_4421_1(ac=FastIO()):
        # 模板：经典最少区间覆盖范围问题，相邻可以不相交
        n, r = ac.read_list_ints()
        nums = ac.read_list_ints()
        lst = []
        for i in range(n):
            if nums[i]:
                a, b = i-r+1, i+r-1
                a = ac.max(a, 0)
                lst.append([a, b])
        ans = Range().cover_less(0, n-1, lst, False)
        ac.st(ans)
        return
