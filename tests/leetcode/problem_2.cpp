#include <iostream>
#include <vector>
#include <algorithm>

long long bisect_right(const std::vector<long long>& sorted_list, long long target) {
    return std::upper_bound(sorted_list.begin(), sorted_list.end(), target) - sorted_list.begin();
}

long long main() {
    std::vector<long long> numbers = {1, 3, 5, 5, 7, 9};

    long long target = 6;

    long long index = bisect_right(numbers, target);

    std::cout << "Insert position for " << target << ": " << index << std::endl;

    return 0;
}