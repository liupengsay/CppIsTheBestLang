#include <iostream>
#include <thread>
#include <mutex>
#include <string>

std::mutex mtx;
std::string shared_str;

void write_shared_str(const std::string& str) {
    std::lock_guard<std::mutex> lock(mtx);
    shared_str = str;
    std::cout << "Written: " << shared_str << "\n";
}

void read_shared_str() {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Read: " << shared_str << "\n";
}

int main() {
    std::thread writer1(write_shared_str, "Hello");
    writer1.join();
    std::thread writer2(write_shared_str, "World");
    writer2.join();
    std::thread reader1(read_shared_str);
    std::thread reader2(read_shared_str);
    reader1.join();
    reader2.join();
    return 0;
}
