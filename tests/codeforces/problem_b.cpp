#include <iostream>
#include <thread>
#include <shared_mutex>
#include <string>
#include <mutex>

std::shared_mutex shared_mtx;
std::string shared_str;

void write_shared_str(const std::string& str) {
    std::unique_lock<std::shared_mutex> lock(shared_mtx);
    shared_str = str;
    std::cout << "Written: " << shared_str << "\n";
}

std::string read_shared_str() {
    std::shared_lock<std::shared_mutex> lock(shared_mtx);
    return shared_str;
}

int main() {

    std::thread reader3([]() {
        std::string result = read_shared_str();
        std::cout << "Read: " << result << "\n";
    });

    reader3.join();

    std::thread writer1(write_shared_str, "Hello");
    std::thread writer2(write_shared_str, "World");
    writer1.join();
    writer2.join();

    std::thread reader1([]() {
        std::string result = read_shared_str();
        std::cout << "Read: " << result << "\n";
    });
    std::thread writer3(write_shared_str, "Check");

    std::thread reader2([]() {
        std::string result = read_shared_str();
        std::cout << "Read: " << result << "\n";
    });

    reader1.join();
    reader2.join();
    writer3.join();
    return 0;
}
