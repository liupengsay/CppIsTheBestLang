#include <iostream>
#include <vector>
#include <algorithm>

int bisect_right(const std::vector<int>& sorted_list, int target) {
    return std::upper_bound(sorted_list.begin(), sorted_list.end(), target) - sorted_list.begin();
}

int main() {
    std::vector<int> numbers = {1, 3, 5, 5, 7, 9};

    int target = 6;

    int index = bisect_right(numbers, target);

    std::cout << "Insert position for " << target << ": " << index << std::endl;

    return 0;
}