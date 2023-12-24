#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

int sharedVariable = 0;
std::mutex mtx; // Mutex for synchronization

void increment() {
    for (int i = 0; i < 100000; ++i) {
        mtx.lock(); // Lock the mutex
        int currentValue = sharedVariable;
        std::this_thread::sleep_for(std::chrono::microseconds(1)); // Introduce a delay
        sharedVariable = currentValue + 1;
        mtx.unlock(); // Unlock the mutex
    }
}

int main() {
    std::thread thread1(increment);
    std::thread thread2(increment);

    thread1.join();
    thread2.join();

    std::cout << "Expected value: 200000" << std::endl;
    std::cout << "Actual value: " << sharedVariable << std::endl;

    return 0;
}

