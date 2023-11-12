"""
算法：Trie字典树，也叫前缀树
功能：处理字符串以及结合位运算相关，01Trie通用用于查询位运算极值
题目：

===================================力扣===================================
421. 数组中两个数的最大异或值（https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/）经典 01 Trie
638. 大礼包（https://leetcode.cn/problems/shopping-offers/）经典使用字典树与记忆化搜索
2416. 字符串的前缀分数和（https://leetcode.cn/problems/sum-of-prefix-scores-of-strings/）单词组前缀计数
1803. 统计异或值在范围内的数对有多少（https://leetcode.cn/problems/count-pairs-with-xor-in-a-range/）经典01Trie，查询异或值在一定范围的数组对，可以使用数组实现
677. 键值映射（https://leetcode.cn/problems/map-sum-pairs/）更新与查询给定字符串作为单词键前缀的对应值的和
2479. 两个不重叠子树的最大异或值（https://leetcode.cn/problems/maximum-xor-of-two-non-overlapping-subtrees/）01Trie计算最大异或值
面试题 17.17. 多次搜索（https://leetcode.cn/problems/multi-search-lcci/）AC自动机计数，也可直接使用字典树逆向思维，字典树存关键字，再搜索文本，和单词矩阵一样的套路
1707. 与数组中元素的最大异或值（https://leetcode.cn/problems/maximum-xor-with-an-element-from-array/）经典排序后离线查询并使用 01 Trie求解
1938. 查询最大基因差（https://leetcode.cn/problems/maximum-genetic-difference-query/）使用深搜回溯与01Trie查询最大异或值
1032. 字符流（https://leetcode.cn/problems/stream-of-characters/description/）字典树典型应用，倒序存储

===================================洛谷===================================
P8306 字典树（https://www.luogu.com.cn/problem/P8306）
P4551 最长异或路径（https://www.luogu.com.cn/problem/P4551）关键是利用异或的性质，将任意根节点作为中转站
P3864 [USACO1.2]命名那个数字 Name That Number（https://www.luogu.com.cn/problem/P3864）使用哈希枚举或者进行字典树存储
P5755 [NOI2000] 单词查找树（https://www.luogu.com.cn/problem/P5755）字典树节点计数
P1481 魔族密码（https://www.luogu.com.cn/problem/P1481）最长词链
P5283 [十二省联考 2019] 异或粽子（https://www.luogu.com.cn/problem/P5283）字典树查询第k大异或值，并使用堆贪心选取
P2922 [USACO08DEC]Secret Message G（https://www.luogu.com.cn/problem/P2922）字典树好题，前缀计数
P1738 洛谷的文件夹（https://www.luogu.com.cn/problem/P1738）字典树键计数
P8420 [THUPC2022 决赛] 匹配（https://www.luogu.com.cn/problem/P8420）字典树贪心匹配

================================CodeForces================================
Fixed Prefix Permutations（https://codeforces.com/problemset/problem/1792/D）变形后使用字典树进行计数查询
D. Vasiliy's Multiset（https://codeforces.com/problemset/problem/706/D）经典01Trie，增加与删除数字，最大异或值查询
B. Friends（https://codeforces.com/contest/241/problem/B）经典01Trie计算第 K 大的异或对，并使用堆贪心选取
E. Beautiful Subarrays（https://codeforces.com/contest/665/problem/E）统计连续区间异或对数目
E. Sausage Maximization（https://codeforces.com/contest/282/problem/E）转换为 01Trie 求数组最大异或值
Set Xor-Min（https://judge.yosupo.jp/problem/set_xor_min）template dynamic xor min

================================AcWing====================================
142. 前缀统计（https://www.acwing.com/problem/content/144/）字典树前缀统计
143. 最大异或对（https://www.acwing.com/problem/content/145/）模板题计算最大异或对
144. 最长异或值路径（https://www.acwing.com/problem/content/description/146/）经典使用01Trie计算树中最长异或路径
161. 电话列表（https://www.acwing.com/problem/content/163/）使用字典树判断是否存在单词前缀包含

参考：OI WiKi（）
"""
import heapq
import math
from collections import Counter, defaultdict
from math import inf
from typing import List

from src.strings.trie.template import TrieZeroOneXorMax, TrieZeroOneXorMaxKth, TriePrefixCount, BinaryTrie, TrieBit, \
    TriePrefixKeyValue, TrieKeyWordSearchInText, TrieZeroOneXorRange
from src.utils.fast_io import FastIO


class Solution:
    def __int__(self):
        return

    @staticmethod
    def lc_1717(big: str, smalls: List[str]) -> List[List[int]]:
        # 模板：AC自动机类似题目，查询关键词在文本中的出现索引
        trie = TrieKeyWordSearchInText()
        for i, word in enumerate(smalls):
            trie.add_key_word(word, i)

        ans = [[] for _ in smalls]
        n = len(big)
        for i in range(n):
            for j in trie.search_text(big[i:]):
                ans[j].append(i)
        return ans

    @staticmethod
    def lc_677():
        # 模板：更新与查询给定字符串作为单词键前缀的对应值的和
        class MapSum:
            def __init__(self):
                self.trie = TriePrefixKeyValue()

            def insert(self, key: str, val: int) -> None:
                self.trie.update(key, val)

            def sum(self, prefix: str) -> int:
                return self.trie.query(prefix)

        MapSum()
        return

    @staticmethod
    def lc_1803(nums: List[int], low: int, high: int) -> int:
        # 模板：使用01字典树查询异或值在有一定范围内的数对个数
        count = Counter(nums)
        # 确定二进制序列的长度
        big = max(nums)
        n = 0
        while (1 << (n + 1)) - 1 < big:
            n += 1
        trie = TrieZeroOneXorRange(n)
        trie.update(0, 0)
        # 滚动更新字典树同时查询符合条件的数对个数
        ans = 0
        for num in count:
            ans += count[num] * (trie.query(num, high) - trie.query(num, low - 1))
            trie.update(num, count[num])
        return ans

    @staticmethod
    def lc_1803_2(nums: List[int], low: int, high: int) -> int:
        # 模板：统计范围内的异或对数目
        ans, cnt = 0, Counter(nums)
        high += 1
        while high:
            nxt = Counter()
            for x, c in cnt.items():
                if high & 1:
                    ans += c * cnt[x ^ (high - 1)]
                if low & 1:
                    ans -= c * cnt[x ^ (low - 1)]
                nxt[x >> 1] += c
            cnt = nxt
            low >>= 1
            high >>= 1
        return ans // 2

    @staticmethod
    def cf_706d(ac=FastIO()):
        # 模板：使用01字典树增加与删除数字后查询最大异或值
        trie = BinaryTrie(32)
        q = ac.read_int()
        trie.add(0)
        for _ in range(q):
            op, x = ac.read_list_strs()
            if op == "+":
                trie.add(int(x))
            elif op == "-":
                trie.remove(int(x))
            else:
                ac.st(trie.max_xor(int(x)))
        return

    @staticmethod
    def lc_2479(n: int, edges: List[List[int]], values: List[int]) -> int:
        # 模板：借助深搜的顺序进行01字典树查询最大异或数对值
        dct = [[] for _ in range(n)]
        for i, j in edges:
            dct[i].append(j)
            dct[j].append(i)

        # 预处理子树取值之和
        def dfs1(x, fa):
            res = values[x]
            for y in dct[x]:
                if y != fa:
                    dfs1(y, x)
                    res += son[y]
            son[x] = res
            return

        son = [0] * n
        dfs1(0, -1)

        def dfs2(x, fa):
            nonlocal ans
            cur = trie.query_xor_max(son[x])
            ans = ans if ans > cur else cur
            for y in dct[x]:
                if y != fa:
                    dfs2(y, x)
            trie.add(son[x])
            return

        # 根据题意使用深搜序和01字典树动态维护查询
        trie = TrieZeroOneXorMax(int(math.log2(sum(values)) + 2))
        ans = 0
        dfs2(0, -1)
        return ans

    @staticmethod
    def lc_2416(words: List[str]) -> List[int]:
        trie = TriePrefixCount()
        for word in words:
            trie.update(word)
        return [trie.query(word) for word in words]

    @staticmethod
    def lg_p1481(ac=FastIO()):
        # 模板：字典树计算最长词链
        n = ac.read_int()

        dct = dict()
        ans = 0
        for _ in range(n):
            cur = dct
            x = 0
            for w in ac.read_str():
                if "isEnd" in cur:
                    x += 1
                if w not in cur:
                    cur[w] = dict()
                cur = cur[w]
            cur["isEnd"] = 1
            x += 1
            ans = ans if ans > x else x
        ac.st(ans)
        return

    @staticmethod
    def lg_p4551(ac=FastIO()):
        # 模板：计算树中异或值最长的路径
        n = ac.read_int()
        trie = TrieZeroOneXorMax(32)

        dct = [dict() for _ in range(n)]
        for _ in range(n - 1):
            i, j, k = ac.read_list_ints()
            dct[i - 1][j - 1] = k
            dct[j - 1][i - 1] = k

        stack = [[0, -1, 0]]
        ans = 0
        while stack:
            i, fa, pre = stack.pop()
            ans = ac.max(ans, trie.query_xor_max(pre))
            ans = ac.max(ans, pre)
            trie.add(pre)
            for j in dct[i]:
                if j != fa:
                    stack.append([j, i, pre ^ dct[i][j]])
        ac.st(ans)
        return

    @staticmethod
    def lg_p5283(ac=FastIO()):
        # 模板：计算数组中最大的 k 组异或对
        n, k = ac.read_list_ints()
        nums = [0] + ac.read_list_ints()
        for i in range(1, n + 1):
            nums[i] ^= nums[i - 1]
        trie = TrieZeroOneXorMaxKth(len(bin(max(nums))))
        for i, num in enumerate(nums):
            trie.add(num)
        stack = [(-trie.query_xor_kth_max(nums[i], 1), i, 1) for i in range(n + 1)]
        heapq.heapify(stack)
        ans = 0
        res = []
        for _ in range(2 * k):
            num, i, c = heapq.heappop(stack)
            ans -= num
            res.append(-num)
            if c + 1 <= n + 1:
                heapq.heappush(stack, (-trie.query_xor_kth_max(nums[i], c + 1), i, c + 1))
        ac.st(ans // 2)
        return

    @staticmethod
    def cf_241b(ac=FastIO()):
        # 模板：计算数组中最大的 k 组异或对
        mod = 10 ** 9 + 7
        n, k = ac.read_list_ints()
        nums = ac.read_list_ints()
        trie = TrieZeroOneXorMaxKth(len(bin(max(nums))))
        for i, num in enumerate(nums):
            trie.add(num)
        stack = [(-trie.query_xor_kth_max(nums[i], 1), i, 1) for i in range(n)]
        heapq.heapify(stack)
        ans = 0
        for _ in range(2 * k):
            num, i, c = heapq.heappop(stack)
            ans -= num
            if c + 1 <= n:
                heapq.heappush(stack, (-trie.query_xor_kth_max(nums[i], c + 1), i, c + 1))
        ac.st((ans // 2) % mod)
        return

    @staticmethod
    def ac_143(ac=FastIO()):
        # 模板：计算最大异或对
        ac.read_int()
        ans = 0
        trie = TrieZeroOneXorMax(32)
        for num in ac.read_list_ints():
            ans = ac.max(ans, trie.query_xor_max(num))
            trie.add(num)
        ac.st(ans)
        return

    @staticmethod
    def ac_144(ac=FastIO()):

        # 模板：经典使用01Trie计算树中最长异或路径
        n = ac.read_int()
        dct = [dict() for _ in range(n)]
        for _ in range(n - 1):
            i, j, w = ac.read_list_ints()
            dct[i][j] = w
            dct[j][i] = w

        ans = 0
        trie = BinaryTrie(32)

        stack = [[0, -1, 0]]
        ceil = (1 << 31) - 1
        while stack:
            i, fa, val = stack.pop()
            ans = max(ans, trie.max_xor(val))
            if ans == ceil:
                break
            trie.add(val)
            for j in dct[i]:
                if j != fa:
                    stack.append([j, i, val ^ dct[i][j]])
        ac.st(ans)
        return

    @staticmethod
    def ac_161(ac=FastIO()):
        # 模板：经典O(n)使用字典树判断是否存在单词前缀包含
        for _ in range(ac.read_int()):
            n = ac.read_int()
            dct = dict()
            ans = True
            for _ in range(n):
                s = ac.read_str()
                if not ans:
                    continue
                cur = dct
                flag = True
                for w in s:
                    if w not in cur:
                        cur[w] = dict()
                        flag = False
                    cur = cur[w]
                    if "cnt" in cur:
                        ans = False
                        break
                if flag:
                    ans = False
                cur["cnt"] = 1
            ac.st("YES" if ans else "NO")
            del dct
        return

    @staticmethod
    def lg_p2922(ac=FastIO()):
        # 模板：字典树进行前缀匹配
        m, n = ac.read_list_ints()
        dct = dict()
        for _ in range(m):
            b = ac.read_list_ints()
            cur = dct
            for num in b[1:]:
                if num not in cur:
                    cur[num] = dict()
                cur = cur[num]
                cur["mid"] = cur.get("mid", 0) + 1
            cur["cnt"] = cur.get("cnt", 0) + 1

        for _ in range(n):
            ans = 0
            cur = dct
            for num in ac.read_list_ints()[1:]:
                if num not in cur:
                    break
                cur = cur[num]
                ans += cur.get("cnt", 0)
            else:
                ans += cur.get("mid", 0) - cur.get("cnt", 0)
            ac.st(ans)
        return

    @staticmethod
    def lg_p1738(ac=FastIO()):
        # 模板：动态维护字典树键个数
        n = ac.read_int()
        dct = dict()
        ans = 0
        for _ in range(n):
            s = ac.read_str().split("/")[1:]
            cur = dct
            for w in s:
                if w not in cur:
                    ans += 1
                    cur[w] = dict()
                cur = cur[w]
            ac.st(ans)
        return

    @staticmethod
    def lg_p8420(ac=FastIO()):
        # 模板：字典树贪心匹配
        n, m, length = ac.read_list_ints()

        # 计算后缀 0 1 匹配的代价和
        cnt = [0] * length
        for _ in range(n):
            s = ac.read_str()
            for i in range(length):
                cnt[i] += 1 if s[i] == "1" else 0
        post = [0] * (length + 1)
        for i in range(length - 1, -1, -1):
            post[i] = post[i + 1] + ac.min(n - cnt[i], cnt[i])

        # 使用禁用词构建字典
        dct = dict()
        for _ in range(m):
            s = ac.read_str()
            cur = dct
            for w in s:
                if w not in cur:
                    cur[w] = dict()
                cur = cur[w]

        def dfs(x, cur_dct, p):
            nonlocal ans
            if x == length:
                return
            if "1" in cur_dct:
                dfs(x + 1, cur_dct["1"], p + n - cnt[x])
            else:
                # 当前键为空时进行贪心匹配
                ans = ac.min(ans, p + n - cnt[x] + post[x + 1])
            if "0" in cur_dct:
                dfs(x + 1, cur_dct["0"], p + cnt[x])
            else:
                ans = ac.min(ans, p + cnt[x] + post[x + 1])
            return

        ans = inf
        dfs(0, dct, 0)
        ac.st(ans)
        return

    @staticmethod
    def lc_1707(nums: List[int], queries: List[List[int]]) -> List[int]:
        # 模板：经典排序后离线查询并使用 01 Trie求解最大异或值
        n = len(nums)
        nums.sort()

        # 添加指针
        m = len(queries)
        for i in range(m):
            queries[i].append(i)
        queries.sort(key=lambda it: it[1])

        # 使用指针进行离线查询
        trie = TrieZeroOneXorMax(32)
        ans = [-1] * m
        j = 0
        for x, m, i in queries:
            while j < n and nums[j] <= m:
                trie.add(nums[j])
                j += 1
            if trie.dct:
                ans[i] = trie.query_xor_max(x)
            else:
                ans[i] = -1
        return ans

    @staticmethod
    def cf_665e(ac=FastIO()):
        n, k = ac.read_list_ints()
        nums = ac.read_list_ints()
        for i in range(1, n):
            nums[i] ^= nums[i - 1]
        cnt = {0: 1}
        for num in nums:
            cnt[num] = cnt.get(num, 0) + 1
        # 模板：统计范围内的异或对数目
        ans = 0
        del nums
        high = 1 << 30
        low = k
        while high:
            nxt = dict()
            for x in cnt:
                c = cnt[x]
                if high & 1:
                    ans += c * cnt.get(x ^ (high - 1), 0)
                if low & 1:
                    ans -= c * cnt.get(x ^ (low - 1), 0)
                nxt[x >> 1] = nxt.get(x >> 1, 0) + c
            cnt = nxt
            low >>= 1
            high >>= 1
        ac.st(ans // 2)
        return

    @staticmethod
    def lib_check_1(ac=FastIO()):
        """template of set xor min"""
        bt = BinaryTrie(32)
        dct = set()
        for _ in range(ac.read_int()):
            op, x = ac.read_list_ints()
            if op == 0:
                if x not in dct:
                    dct.add(x)
                    bt.add(x)
            elif op == 1:
                if x in dct:
                    dct.discard(x)
                    bt.remove(x)
            else:
                ac.st(bt.min_xor(x))
        return

    @staticmethod
    def lc_421(nums: List[int]) -> int:
        # 模板：求解数组最大的异或对，经典题，有更快解法
        trie = TrieZeroOneXorMax(32)
        ans = 0
        for num in nums:
            cur = trie.query_xor_max(num)
            ans = ans if ans > cur else cur
            trie.add(num)
        return ans

    @staticmethod
    def lc_421_2(nums: List[int]) -> int:
        # 模板：更快解法
        res = 0
        mask = 0
        max_len = len(bin(max(nums))) - 2
        # 最大长度不会超过最大值，异或的特性
        for i in range(max_len - 1, -1, -1):
            cur = 1 << i
            mask = mask | cur
            res |= cur
            d = {}
            find = 0
            for num in nums:
                d[num & mask] = 1
                if (num & mask) ^ res in d:
                    find = 1
                    break
            if not find:
                res ^= 1 << i
        return res

    @staticmethod
    def cf_282e(ac=FastIO()):
        # 模板：维护和查询最大异或数值对
        n = ac.read_int()
        nums = ac.read_list_ints()
        ans = pre = 0
        trie = BinaryTrie(40)
        trie.add(0)
        for i in range(n):
            pre ^= nums[i]
            trie.add(pre)
            ans = ac.max(ans, pre)

        pre = 0
        for i in range(n - 1, -1, -1):
            pre ^= nums[i]
            ans = ac.max(ans, trie.max_xor(pre))
        ac.st(ans)
        return

    @staticmethod
    def lc_1938(parents: List[int], queries: List[List[int]]) -> List[int]:
        # 模板：深搜回溯结合01Trie离线查询最大异或值对
        n = len(parents)
        x = -1
        dct = [[] for _ in range(n)]
        for i in range(n):
            if parents[i] == -1:
                x = i
            else:
                dct[parents[i]].append(i)

        query = [dict() for _ in range(n)]
        for node, val in queries:
            query[node][val] = 0
        trie = BinaryTrie(20)

        def dfs(a):
            trie.add(a)
            for v in query[a]:
                query[a][v] = trie.max_xor(v)
            for b in dct[a]:
                dfs(b)
            trie.remove(a)
            return

        dfs(x)
        return [query[node][val] for node, val in queries]

    @staticmethod
    def lc_1938_2(parents: List[int], queries: List[List[int]]) -> List[int]:
        # 模板：深搜回溯结合01Trie离线查询最大异或值对
        n = len(parents)
        dct = [[] for _ in range(n)]
        root = -1
        for i in range(n):
            if parents[i] == -1:
                root = i
            else:
                dct[parents[i]].append(i)

        ind = [defaultdict(dict) for _ in range(n)]
        for node, val in queries:
            ind[node][val] = 0

        def dfs(i):
            tree.update(i)
            for v in ind[i]:
                ind[i][v] = tree.query(v)
            for j in dct[i]:
                dfs(j)
            tree.delete(i)
            return

        tree = TrieBit()
        dfs(root)
        return [ind[node][v] for node, v in queries]
