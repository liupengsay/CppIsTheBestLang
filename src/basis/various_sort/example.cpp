import random
import unittest

from src.basis.various_sort.template import VariousSort


class TestGeneral(unittest.TestCase):

    def test_various_sort(self):
        vs = VariousSort()
        n = 1000
        for _ in range(n):
            nums = [random.randint(0, n) for _ in range(n)]
            assert vs.defined_sort(nums) == vs.quick_sort_two(nums) == vs.merge_sort(nums) == sorted(nums)
        return


if __name__ == '__main__':
    unittest.main()
