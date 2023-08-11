#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string name;
    int score;
};


bool compare(const Student& a, const Student& b) {
    return a.score > b.score;
}




class TestGeneral {
public:
    static void StructDataSortTest() {

        cout << "students_array" << endl;
        Student students_array[] = {{"Tom", 90}, {"Jerry", 85}, {"Bob", 95}, {"Alice", 88}};
        int len = sizeof(students_array) / sizeof(students_array[0]);
        sort(students_array, students_array+len, compare);

        // 输出排序后的结果
        for (int i = 0; i < len; i++) {
            cout << students_array[i].name << " " << students_array[i].score << endl;
        }

        cout << "students_vector" << endl;
        vector<Student> students_vector = {Student{"Tom", 90}, Student{"Jerry", 85},
                                           Student{"Bob", 95}, Student{"Alice", 88}};

        sort(students_vector.begin(), students_vector.end(), compare);

        // 输出排序后的结果
        for (int i = 0; i < len; i++) {
            cout << students_vector[i].name << " " << students_vector[i].score << endl;
        }
    }

};


int main() {
    TestGeneral::StructDataSortTest();
    return 0;
};
