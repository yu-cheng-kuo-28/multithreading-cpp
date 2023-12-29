#include <iostream>
#include <thread>
#include <chrono>

void function1() {
    for (int i = 0; i < 200; ++i) {
        std::cout << "A";
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void function2() {
    for (int i = 0; i < 200; ++i) {
        std::cout << "B";
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main() {
    std::thread worker1(function1);
    std::thread worker2(function2);
    worker1.join();
    worker2.join();
    std::cout << "\n";
}

