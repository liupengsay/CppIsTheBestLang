"""

算法：使用数组作为链表维护前驱后驱
功能：

题目：xx（xx）

===================================力扣===================================
2617. 网格图中最少访问的格子数（https://leetcode.cn/problems/minimum-number-of-visited-cells-in-a-grid/）经典BFS加链表，使用数组维护链表的前后节点信息
2612. 最少翻转操作数（https://leetcode.cn/problems/minimum-reverse-operations/）经典BFS加链表，使用数组维护链表的前后节点信息
1562. 查找大小为 M 的最新分组（https://leetcode.cn/problems/find-latest-group-of-size-m/）使用类似并查集的前后缀链表求解
2382. 删除操作后的最大子段和（https://leetcode.cn/problems/maximum-segment-sum-after-removals/）逆向进行访问查询并更新连通块的结果，也可以使用双向链表维护
2289. 使数组按非递减顺序排列（https://leetcode.cn/problems/steps-to-make-array-non-decreasing/description/）经典单调栈优化的线性DP，也可用BFS加链表求解

===================================牛客===================================
牛牛排队伍（https://ac.nowcoder.com/acm/contest/49888/C）使用数组维护链表的前后节点信息

===================================洛谷===================================
P5462 X龙珠（https://www.luogu.com.cn/problem/P5462）经典使用双向链表贪心选取最大字典序队列
P6155 修改（https://www.luogu.com.cn/problem/P6155）经典排序贪心使用并查集思想寻找右边最近的空位

================================CodeForces================================
E. Two Teams（https://codeforces.com/contest/1154/problem/E）使用数组维护链表的前后节点信息

================================AcWing===================================
136. 邻值查找（https://www.acwing.com/problem/content/138/）链表逆序删除，查找前后最接近的值
4943. 方格迷宫（https://www.acwing.com/problem/content/description/4946/）经典BFS加链表，维护四个方向上的未访问点
5034. 配对（https://www.acwing.com/problem/content/5037/）经典堆贪心加链表进行处理

参考：OI WiKi（xx）
"""
import heapq
from collections import deque
from math import inf
from typing import List

from src.utils.fast_io import FastIO


class Solution:
    def __init__(self):
        return

    @staticmethod
    def cf_1154e(ac=FastIO()):

        # 模板：使用链表维护前后的节点信息
        n, k = ac.read_list_ints()
        nums = ac.read_list_ints()
        ans = [0] * n
        pre = [i - 1 for i in range(n)]
        nex = [i + 1 for i in range(n)]
        ind = [0] * n
        for i in range(n):
            ind[nums[i] - 1] = i

        step = 1
        for num in range(n - 1, -1, -1):
            i = ind[num]
            if ans[i]:
                continue
            ans[i] = step
            left, right = pre[i], nex[i]
            for _ in range(k):
                if left != -1:
                    ans[left] = step
                    left = pre[left]
                else:
                    break
            for _ in range(k):
                if right != n:
                    ans[right] = step
                    right = nex[right]
                else:
                    break
            if left >= 0:
                nex[left] = right
            if right < n:
                pre[right] = left
            step = 3 - step
        ac.st("".join(str(x) for x in ans))
        return

    @staticmethod
    def nc_247577(ac=FastIO()):
        # 模板：使用链表维护前后的节点信息
        n, k = ac.read_list_ints()
        pre = list(range(-1, n + 1))
        post = list(range(1, n + 3))
        assert len(pre) == len(post) == n + 2
        for _ in range(k):
            op, x = ac.read_list_ints()
            if op == 1:
                a = pre[x]
                b = post[x]
                if 1 <= b <= n:
                    pre[b] = a
                if 1 <= a <= n:
                    post[a] = b
                pre[x] = post[x] = -1
            else:
                ac.st(pre[x])
        return

    @staticmethod
    def lc_2289(nums: List[int]) -> int:

        # 模板：经典单调栈优化的线性DP，也可用BFS加链表求解
        n = len(nums)
        post = list(range(1, n + 1))
        nums.append(10 ** 9 + 7)
        stack = [i - 1 for i in range(1, n) if nums[i - 1] > nums[i]]
        ans = 0
        visit = [0] * n
        while stack:
            ans += 1
            for i in stack[::-1]:
                if nums[i] > nums[post[i]]:
                    visit[post[i]] = 1
                    post[i] = post[post[i]]
            stack = [i for i in stack if not visit[i] and nums[i] > nums[post[i]]]
        return ans

    @staticmethod
    def lc_2617(grid: List[List[int]]) -> int:
        # 模板：经典BFS加两个方向上的链表，也可以使用并查集代替
        m, n = len(grid), len(grid[0])
        dis = [[inf] * n for _ in range(m)]
        row_nex = [list(range(1, n + 1)) for _ in range(m)]
        col_nex = [list(range(1, m + 1)) for _ in range(n)]
        stack = deque([[0, 0]])
        dis[0][0] = 1

        while stack:
            i, j = stack.popleft()
            d = dis[i][j]
            x = grid[i][j]
            if x == 0:
                continue

            # 按照行取出可以访问到的节点
            nex = row_nex[i]
            y = nex[j]
            lst = []
            while y <= j + x and 0 <= y < n:
                if dis[i][y] == inf:
                    dis[i][y] = d + 1
                    if i == m - 1 and y == n - 1:
                        return d + 1
                    stack.append([i, y])
                lst.append(y)
                y = nex[y]
            # 更新前驱后驱
            for w in lst:
                nex[w] = y

            # 按照列取出可以访问到的节点
            nex = col_nex[j]
            y = nex[i]
            lst = []
            while y <= i + x and 0 <= y < m:
                if dis[y][j] == inf:
                    dis[y][j] = d + 1
                    if y == m - 1 and j == n - 1:
                        return d + 1
                    stack.append([y, j])
                lst.append(y)
                y = nex[y]
            # 更新前驱后驱
            for w in lst:
                nex[w] = y

        ans = dis[-1][-1]
        return ans if ans < inf else -1

    @staticmethod
    def ac_136(ac=FastIO()):
        # 模板：链表逆序删除，查找前后最接近的值，也可直接使用SortedList
        n = ac.read_int()
        nums = ac.read_list_ints()
        ind = list(range(n))
        ind.sort(key=lambda it: nums[it])
        dct = {nums[i]: i for i in range(n)}
        pre = [-1] * n
        post = [-1] * n
        for i in range(1, n):
            a, b = ind[i - 1], ind[i]
            post[a] = b
            pre[b] = a
        ans = []
        for x in range(n - 1, 0, -1):
            num = nums[x]
            i = dct[num]
            a = pre[i]
            b = post[i]
            if a != -1 and b != -1:
                if abs(num - nums[a]) < abs(num - nums[b]) or (
                        abs(num - nums[a]) == abs(num - nums[b]) and nums[a] < nums[b]):
                    ans.append([abs(num - nums[a]), a + 1])
                else:
                    ans.append([abs(num - nums[b]), b + 1])
                post[a] = b
                pre[b] = a
            elif a != -1:
                ans.append([abs(num - nums[a]), a + 1])
                post[a] = post[i]
            else:
                ans.append([abs(num - nums[b]), b + 1])
                pre[b] = pre[i]
        for i in range(n - 2, -1, -1):
            ac.lst(ans[i])
        return

    @staticmethod
    def lg_p5462(ac=FastIO()):
        # 模板：经典使用双向链表贪心选取最大字典序队列
        n = ac.read_int()
        nums = ac.read_list_ints()
        pre = [-1] * (n + 1)
        post = [-1] * (n + 1)
        for i in range(n):
            if i:
                pre[nums[i]] = nums[i - 1]
            if i + 1 < n:
                post[nums[i]] = nums[i + 1]

        # 从大到小取出
        visit = [0] * (n + 1)
        ans = []
        for num in range(n, 0, -1):
            if visit[num] or post[num] == -1:
                continue
            visit[num] = visit[post[num]] = 1
            ans.extend([num, post[num]])
            x, y = pre[num], post[post[num]]
            if x != -1:
                post[x] = y
            if y != -1:
                pre[y] = x
        ac.lst(ans)
        return

    @staticmethod
    def lg_p6155(ac=FastIO()):
        # 模板：经典排序贪心使用并查集思想寻找右边最近的空位
        n = ac.read_int()
        a = ac.read_list_ints()
        b = ac.read_list_ints()
        a.sort(reverse=True)  # 反向遍历从大到小尽早占据已有位置
        mod = 2 ** 64
        b.sort()
        cnt = []
        pre = {}
        for num in a:
            y = num
            # 类似并查集寻找右边最近的空位
            lst = [num]
            while y in pre:
                lst.append(y)
                y = pre[y]
            lst.append(y)
            # 类似链表记录每个数右侧最近的空位
            for x in lst:
                # 更新这个区间所有数右边最近的空位
                pre[x] = y + 1
            cnt.append(y - num)
        cnt.sort(reverse=True)
        ans = sum(cnt[i] * b[i] for i in range(n))
        ac.st(ans % mod)
        return

    @staticmethod
    def lc_1562(arr: List[int], m: int) -> int:
        # 模板：使用类似并查集的前后缀链表求解
        n = len(arr)
        left = [-1] * n
        right = [-1] * n
        cnt = [0] * (n + 1)
        ans = -1
        for x, i in enumerate(arr):
            i -= 1
            if i - 1 >= 0 and left[i - 1] != -1:
                if i + 1 < n and right[i + 1] != -1:
                    start = left[i - 1]
                    end = right[i + 1]
                    cnt[i - start] -= 1
                    cnt[end - i] -= 1
                    cnt[end - start + 1] += 1
                    right[start] = end
                    left[end] = start
                else:
                    start = left[i - 1]
                    cnt[i - start] -= 1
                    end = i
                    cnt[end - start + 1] += 1
                    right[start] = end
                    left[end] = start
            elif i + 1 < n and right[i + 1] != -1:
                start = i
                end = right[i + 1]
                cnt[end - i] -= 1
                cnt[end - start + 1] += 1
                right[start] = end
                left[end] = start
            else:
                left[i] = right[i] = i
                cnt[1] += 1

            if cnt[m]:
                ans = x + 1
        return ans

    @staticmethod
    def ac_4943(ac=FastIO()):
        # 模板：经典BFS加链表，维护四个方向上的未访问点
        m, n, k = ac.read_list_ints()
        grid = [ac.read_str() for _ in range(m)]
        x1, y1, x2, y2 = ac.read_list_ints_minus_one()

        dis = [[inf] * n for _ in range(m)]
        row_nex = [list(range(1, n + 1)) for _ in range(m)]
        row_pre = [list(range(-1, n - 1)) for _ in range(m)]
        col_nex = [list(range(1, m + 1)) for _ in range(n)]
        col_pre = [list(range(-1, m - 1)) for _ in range(n)]
        stack = deque([[x1, y1]])
        dis[x1][y1] = 0

        while stack:
            i, j = stack.popleft()
            d = dis[i][j]
            # 按照右边取出可以访问到的节点
            pre = row_pre[i]
            nex = row_nex[i]
            y = nex[j]
            lst = []
            while y <= j + k and 0 <= y < n and grid[i][y] == ".":
                if dis[i][y] == inf:
                    dis[i][y] = d + 1
                    stack.append([i, y])
                lst.append(y)
                y = nex[y]
            for w in lst:
                nex[w] = y
                pre[w] = pre[j]

            # 按照左边取出可以访问到的节点
            pre = row_pre[i]
            nex = row_nex[i]
            y = pre[j]
            lst = []
            while j - y <= k and 0 <= y < n and grid[i][y] == ".":
                if dis[i][y] == inf:
                    dis[i][y] = d + 1
                    stack.append([i, y])
                lst.append(y)
                y = pre[y]
            for w in lst:
                pre[w] = y
                nex[w] = nex[j]

            # 按照下面取出可以访问到的节点
            pre = col_pre[j]
            nex = col_nex[j]
            y = nex[i]
            lst = []
            while y <= i + k and 0 <= y < m and grid[y][j] == ".":
                if dis[y][j] == inf:
                    dis[y][j] = d + 1
                    stack.append([y, j])
                lst.append(y)
                y = nex[y]
            for w in lst:
                nex[w] = y
                pre[w] = pre[i]

            # 按照上面取出可以访问到的节点
            pre = col_pre[j]
            nex = col_nex[j]
            y = pre[i]
            lst = []
            while i - y <= k and 0 <= y < m and grid[y][j] == ".":
                if dis[y][j] == inf:
                    dis[y][j] = d + 1
                    stack.append([y, j])
                lst.append(y)
                y = pre[y]
            for w in lst:
                pre[w] = y
                nex[w] = nex[i]

        ans = dis[x2][y2]
        ac.st(ans if ans < inf else -1)
        return

    @staticmethod
    def ac_5034(ac=FastIO()):
        # 模板：经典堆贪心加链表进行处理
        n = ac.read_int()
        s = ac.read_str()
        nums = ac.read_list_ints()
        post = list(range(1, n + 1))
        pre = list(range(-1, n - 1))
        stack = []
        for i in range(n - 1):
            if s[i] != s[i + 1]:
                heapq.heappush(stack, [abs(nums[i + 1] - nums[i]), i, i + 1])
        # 模拟出队并使用链表维护前后关系
        ans = []
        visit = [0] * n
        while stack:
            _, i, j = heapq.heappop(stack)
            if not visit[i] and not visit[j]:
                visit[i] = 1
                visit[j] = 1
                ans.append([i + 1, j + 1])

                y = post[j]
                while y < n and visit[y]:
                    y = post[y]

                x = pre[i]
                while x >= 0 and visit[x]:
                    x = pre[x]
                if x != -1:
                    post[x] = y
                if y != n:
                    pre[y] = x
                if x != -1 and y != n and s[x] != s[y]:
                    heapq.heappush(stack, [abs(nums[x] - nums[y]), x, y])

            else:
                continue
        ac.st(len(ans))
        for a in ans:
            ac.lst(a)
        return
