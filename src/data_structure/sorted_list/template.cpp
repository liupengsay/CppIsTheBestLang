#include <iostream>
#include <set>

struct CustomCompare {
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const {
        return lhs.first < rhs.first;
    }
};

int main() {
    std::multiset<std::pair<int, int>, CustomCompare> ms = {{1, 2}, {3, 4}, {3, 5}, {5, 6}, {7, 8}, {9, 10}};

    // Value to search for
    std::pair<int, int> value = {3, 0}; // We are only interested in the first element of the pair

    // Get the iterator to the first element that is not less than 'value'
    auto it = ms.lower_bound(value);

    // Check if the iterator points to a valid position and print the result
    if (it != ms.end()) {
        std::cout << "The first pair not less than (" << value.first << ", " << value.second << ") is ("
                  << it->first << ", " << it->second << ")" << std::endl;
    } else {
        std::cout << "All pairs are less than (" << value.first << ", " << value.second << ")" << std::endl;
    }

    return 0;
}
