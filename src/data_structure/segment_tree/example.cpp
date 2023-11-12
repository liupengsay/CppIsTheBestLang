import random
import unittest
from functools import reduce
from operator import or_

from src.data_structure.segment_tree.template import RangeAscendRangeMax, \
    RangeDescendRangeMin, \
    RangeAddRangeSumMinMax, RangeChangeRangeSumMinMax, SegmentTreeRangeUpdateSubConSum, \
    RangeOrRangeAnd, \
    RangeChangeRangeSumMinMaxDynamic, RangeChangeRangeOr


class TestGeneral(unittest.TestCase):

    def test_range_or_range_and(self):
        low = 0
        high = (1 << 31) - 1
        n = 1000
        nums = [random.randint(low, high) for _ in range(n)]
        segment_tree = RangeOrRangeAnd(n)
        segment_tree.build(nums)
        for _ in range(1000):
            ll = random.randint(0, n-1)
            rr = random.randint(ll, n-1)
            num = random.randint(low, high)
            for i in range(ll, rr+1):
                nums[i] |= num
            segment_tree.range_or(ll, rr, num)

            ll = random.randint(0, n-1)
            rr = random.randint(ll, n-1)
            res = high
            for i in range(ll, rr+1):
                res &= nums[i]
            assert res == segment_tree.range_and(ll, rr)
        assert nums == segment_tree.get()
        return

    def test_range_ascend_range_max(self):
        low = 0
        high = 10000
        nums = [random.randint(low, high) for _ in range(high)]
        segment_tree = RangeAscendRangeMax(high)
        segment_tree.build(nums)
        assert segment_tree.get() == nums
        for _ in range(high):
            # 区间更新最大值
            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            num = random.randint(low, high)
            segment_tree.range_ascend(left, right, num)
            for i in range(left, right + 1):
                nums[i] = nums[i] if nums[i] > num else num
            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            assert segment_tree.range_max(left, right) == max(nums[left:right + 1])

            # 单点更新最大值
            left = random.randint(0, high - 1)
            right = left
            num = random.randint(low, high)
            segment_tree.range_ascend(left, right, num)
            for i in range(left, right + 1):
                nums[i] = nums[i] if nums[i] > num else num
            assert segment_tree.range_max(left, right) == max(nums[left:right + 1])

            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            assert segment_tree.range_max(left, right) == max(nums[left:right + 1])
        assert segment_tree.get() == nums
        return

    def test_range_descend_range_min(self):
        low = 0
        high = 10000
        nums = [random.randint(low, high) for _ in range(high)]
        segment_tree = RangeDescendRangeMin(high)
        segment_tree.build(nums)

        for _ in range(high):
            # 区间更新与查询最小值
            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            num = random.randint(low, high)
            segment_tree.range_descend(left, right, num)
            for i in range(left, right + 1):
                nums[i] = nums[i] if nums[i] < num else num
            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            assert segment_tree.range_min(left, right) == min(nums[left:right + 1])

            # 单点更新与查询最小值
            left = random.randint(0, high - 1)
            right = left
            num = random.randint(low, high)
            segment_tree.range_descend(left, right, num)
            for i in range(left, right + 1):
                nums[i] = nums[i] if nums[i] < num else num
            assert segment_tree.range_min(left, right) == min(nums[left:right + 1])

            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            assert segment_tree.range_min(left, right) == min(nums[left:right + 1])

        assert segment_tree.get() == nums
        return

    def test_range_add_range_sum_min_max(self):
        low = -10000
        high = 10000
        nums = [random.randint(low, high) for _ in range(high)]
        segment_tree = RangeAddRangeSumMinMax(high)
        segment_tree.build(nums)

        assert segment_tree.range_min(0, high - 1) == min(nums)
        assert segment_tree.range_max(0, high - 1) == max(nums)
        assert segment_tree.range_sum(0, high - 1) == sum(nums)

        for _ in range(high):

            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            num = random.randint(-high, high)
            segment_tree.range_add(left, right, num)
            for i in range(left, right + 1):
                nums[i] += num
            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            assert segment_tree.range_min(left, right) == min(
                nums[left:right + 1])
            assert segment_tree.range_max(left, right) == max(
                nums[left:right + 1])
            assert segment_tree.range_sum(left, right) == sum(
                nums[left:right + 1])

            left = random.randint(0, high - 1)
            right = left
            num = random.randint(-high, high)
            segment_tree.range_add(left, right, num)
            for i in range(left, right + 1):
                nums[i] += num
            assert segment_tree.range_min(left, right) == min(
                nums[left:right + 1])
            assert segment_tree.range_max(left, right) == max(
                nums[left:right + 1])
            assert segment_tree.range_sum(left, right) == sum(
                nums[left:right + 1])

        assert segment_tree.get() == nums
        return

    def test_range_change_range_sum_min_max(self):
        low = -10000
        high = 10000
        n = 10000
        nums = [random.randint(low, high) for _ in range(n)]
        segment_tree = RangeChangeRangeSumMinMax(n)
        segment_tree.build(nums)
        assert segment_tree.range_min(0, n - 1) == min(nums)
        assert segment_tree.range_max(0, n - 1) == max(nums)
        assert segment_tree.range_sum(0, n - 1) == sum(nums)
        assert segment_tree.get() == nums

        for _ in range(high):
            # 区间修改
            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            num = random.randint(-high, high)
            segment_tree.range_change(left, right, num)
            for i in range(left, right + 1):
                nums[i] = num
            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            assert segment_tree.range_min(left, right) == min(
                nums[left:right + 1])
            assert segment_tree.range_max(left, right) == max(
                nums[left:right + 1])
            assert segment_tree.range_sum(left, right) == sum(
                nums[left:right + 1])

            # 单点修改
            left = random.randint(0, high - 1)
            right = left
            num = random.randint(-high, high)
            segment_tree.range_change(left, right, num)
            for i in range(left, right + 1):
                nums[i] = num
            assert segment_tree.range_min(left, right) == min(
                nums[left:right + 1])
            assert segment_tree.range_max(left, right) == max(
                nums[left:right + 1])
            assert segment_tree.range_sum(left, right) == sum(
                nums[left:right + 1])

            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            assert segment_tree.range_min(left, right) == min(
                nums[left:right + 1])
            assert segment_tree.range_max(left, right) == max(
                nums[left:right + 1])
            assert segment_tree.range_sum(left, right) == sum(
                nums[left:right + 1])

        assert segment_tree.get() == nums
        return

    def test_range_change_range_or(self):
        low = 0
        high = 10000
        n = 10000
        nums = [random.randint(low, high) for _ in range(n)]
        segment_tree = RangeChangeRangeOr(n)
        segment_tree.build(nums)

        for _ in range(high):
            # 区间修改
            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            num = random.randint(0, high)
            segment_tree.range_change(left, right, num)
            for i in range(left, right + 1):
                nums[i] = num
            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            assert segment_tree.range_or(left, right) == reduce(or_, nums[left:right + 1])

        assert segment_tree.get() == nums
        return

    def test_range_change_range_sum_min_max_dynamic(self):
        high = 10000
        n = 10000
        nums = [0]*n
        segment_tree = RangeChangeRangeSumMinMaxDynamic(n)

        for _ in range(high):
            # 区间修改
            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            num = random.randint(-high, high)
            segment_tree.range_change(left, right, num)
            for i in range(left, right + 1):
                nums[i] = num
            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            assert segment_tree.range_min(left, right) == min(
                nums[left:right + 1])
            assert segment_tree.range_max(left, right) == max(
                nums[left:right + 1])
            assert segment_tree.range_sum(left, right) == sum(
                nums[left:right + 1])

            # 单点修改
            left = random.randint(0, high - 1)
            right = left
            num = random.randint(-high, high)
            segment_tree.range_change(left, right, num)
            for i in range(left, right + 1):
                nums[i] = num
            assert segment_tree.range_min(left, right) == min(
                nums[left:right + 1])
            assert segment_tree.range_max(left, right) == max(
                nums[left:right + 1])
            assert segment_tree.range_sum(left, right) == sum(
                nums[left:right + 1])

            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            assert segment_tree.range_min(left, right) == min(
                nums[left:right + 1])
            assert segment_tree.range_max(left, right) == max(
                nums[left:right + 1])
            assert segment_tree.range_sum(left, right) == sum(
                nums[left:right + 1])
        assert segment_tree.range_min(0, n - 1) == min(nums)
        assert segment_tree.range_max(0, n - 1) == max(nums)
        assert segment_tree.range_sum(0, n - 1) == sum(nums)
        return


    def test_segment_tree_range_sub_con_max(self):

        def check(lst):
            pre = ans = lst[0]
            for x in lst[1:]:
                pre = pre + x if pre + x > x else x
                ans = ans if ans > pre else pre
            return ans

        low = 0
        high = 10000
        nums = [random.randint(low, high) for _ in range(high)]
        segment_tree = SegmentTreeRangeUpdateSubConSum(nums)

        assert segment_tree.query_max(0, high - 1, low, high - 1, 1)[0] == check(nums)

        for _ in range(high):
            # 区间更新值
            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            num = random.randint(-high, high)
            segment_tree.update(left, right, low, high - 1, num, 1)
            for i in range(left, right + 1):
                nums[i] = num
            left = random.randint(0, high - 1)
            right = random.randint(left, high - 1)
            assert segment_tree.query_max(left, right, low, high - 1, 1)[0] == check(nums[left:right + 1])
        return


if __name__ == '__main__':
    unittest.main()
