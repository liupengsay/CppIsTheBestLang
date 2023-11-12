class Node(object):
    def __init__(self, val=" ", left=None, right=None):
        if val[0] == "+" and len(val) >= 2:
            val = val[1:]
        self.val = val
        self.left = left
        self.right = right


class TreeExpression:
    def __init__(self):
        return

    def exp_tree(self, s: str) -> Node:

        try:
            int(s)
            # number rest only
            return Node(s)
        except ValueError as _:
            pass

        # case start with -(
        if len(s) >= 2 and s[0] == "-" and s[1] == "(":
            cnt = 0
            for i, w in enumerate(s):
                if w == "(":
                    cnt += 1
                elif w == ")":
                    cnt -= 1
                    if not cnt:
                        pre = s[1:i].replace("+", "-").replace("-", "+")
                        s = pre + s[i:]
                        break
        # case start with -
        neg = ""
        if s[0] == "-":
            neg = "-"
            s = s[1:]

        n = len(s)
        cnt = 0
        # 按照运算符号的优先级倒序遍历字符串
        for i in range(n - 1, -1, -1):
            cnt += int(s[i] == ')') - int(s[i] == '(')
            if s[i] in ['+', '-'] and not cnt:
                return Node(s[i], self.exp_tree(neg + s[:i]), self.exp_tree(s[i + 1:]))

        # 注意是从后往前
        for i in range(n - 1, -1, -1):
            cnt += int(s[i] == ')') - int(s[i] == '(')
            if s[i] in ['*', '/'] and not cnt:
                return Node(s[i], self.exp_tree(neg + s[:i]), self.exp_tree(s[i + 1:]))

        # 注意是从前往后
        for i in range(n):
            cnt += int(s[i] == ')') - int(s[i] == '(')
            if s[i] in ['^'] and not cnt:  # 这里的 ^ 表示幂
                return Node(s[i], self.exp_tree(neg + s[:i]), self.exp_tree(s[i + 1:]))

        # 其余则是开头结尾为括号的情况
        return self.exp_tree(s[1:-1])

    def main_1175(self, s):

        # 按照前序、中序与后序变成前缀中缀与后缀表达式
        def dfs(node):
            if not node:
                return
            dfs(node.left)
            dfs(node.right)
            pre.append(node.val)
            return

        ans = []
        root = self.exp_tree(s)
        pre = []
        dfs(root)
        while len(pre) > 1:
            ans.append(pre)
            n = len(pre)
            stack = []
            for i in range(n):
                if pre[i] in "+-*/^":
                    op = pre[i]
                    b = stack.pop()
                    a = stack.pop()
                    op = "//" if op == "/" else op
                    op = "**" if op == "^" else op
                    stack.append(str(eval(f"{a}{op}{b}")))
                    stack += pre[i + 1:]
                    break
                else:
                    stack.append(pre[i])
            pre = stack[:]
        ans.append(pre)
        return ans


class EnglishNumber:
    def __init__(self):
        return

    @staticmethod
    def number_to_english(n):

        # 将 0-9999 的数字转换为美式英语即有 and
        one = ["", "one", "two", "three", "four",
               "five", "six", "seven", "eight", "nine",
               "ten", "eleven", "twelve", "thirteen", "fourteen",
               "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"]

        ten = [
            "twenty",
            "thirty",
            "forty",
            "fifty",
            "sixty",
            "seventy",
            "eighty",
            "ninety"]

        for word in ten:
            one.append(word)
            for i in range(1, 10):
                one.append(word + " " + one[i])

        ans = ""
        s = str(n)
        if n >= 1000:
            ans += one[n // 1000] + " thousand "

        if (n % 1000) // 100 > 0:
            ans += one[n % 1000 // 100] + " hundred "
        if (n >= 100 and 0 < n % 100 < 10) or (n >= 1000 and 0 < n % 1000 < 100):
            ans += "and "
        ans += one[n % 100]

        if ans == "":
            return "zero"
        return ans
