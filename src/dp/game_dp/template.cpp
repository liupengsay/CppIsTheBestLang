class DateTime:
    def __init__(self):
        self.leap_month = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        self.not_leap_month = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        return

    def is_leap_year(self, yy):
        # Determine whether it is a leap year
        assert sum(self.leap_month) == 366
        assert sum(self.not_leap_month) == 365
        return yy % 400 == 0 or (yy % 4 == 0 and yy % 100 != 0)

    def year_month_day_cnt(self, yy, mm):
        ans = self.leap_month[mm - 1] if self.is_leap_year(yy) else self.not_leap_month[mm - 1]
        return ans

    def is_valid(self, yy, mm, dd):
        if not [1900, 1, 1] <= [yy, mm, dd] <= [2006, 11, 4]:
            return False
        day = self.year_month_day_cnt(yy, mm)
        if not 1 <= dd <= day:
            return False
        return True
