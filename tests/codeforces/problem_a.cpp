#include <iostream>
#include <thread>
#include <shared_mutex>
#include <mutex>

std::shared_mutex shared_mtx;
int shared_var = 0;

void read_shared_var() {
    std::shared_lock<std::shared_mutex> lock(shared_mtx);
    std::cout << "Read shared_var: " << shared_var << "\n";
}

void write_shared_var(int x) {
    std::unique_lock<std::shared_mutex> lock(shared_mtx);
    shared_var = x;
    std::cout << "Updated shared_var to: " << shared_var << "\n";
}

int main() {
    std::thread t1(read_shared_var);
    std::thread t2(write_shared_var, 2);
    std::thread t4(write_shared_var, 4);
    std::thread t3(read_shared_var);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
