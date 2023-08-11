
#include <functional>
#include <vector>
#include <cassert>
#include <iostream>
using namespace std;


class Sample {
public:
    static int add(int low, int high) {
        // 模板: 整数范围内二分查找，选择最靠左满足check
        return low + high;
    }
};



class TestGeneral {
public:
    static void SampleTest() {

        assert(Sample().add(1, 10) == 11);
    }

};


int main() {
    TestGeneral::SampleTest();
    return 0;
};
