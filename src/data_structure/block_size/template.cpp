class BlockSize:
    def __init__(self):
        return

    @staticmethod
    def get_divisor_split(n):
        # Decompose the interval [1, n] into each interval whose divisor of n does not exceed the range
        if n == 1:
            return [1], [[1, 1]]
        m = int(n ** 0.5)
        pre = []
        post = []
        for x in range(1, m + 1):
            pre.append(x)
            post.append(n // x)
        if pre[-1] == post[-1]:
            post.pop()
        post.reverse()
        res = pre + post

        cnt = [res[0]] + [res[i + 1] - res[i] for i in range(len(res) - 1)]
        k = len(cnt)
        assert k == 2 * m - int(m == n // m)

        right = [n // (k - i) for i in range(1, k)]
        pre = n // k
        seg = [[1, pre - 1]] if pre > 1 else []
        for num in right:
            seg.append([pre, num])
            pre = num + 1
        assert sum([ls[1] - ls[0] + 1 for ls in seg]) == n
        return cnt, seg
