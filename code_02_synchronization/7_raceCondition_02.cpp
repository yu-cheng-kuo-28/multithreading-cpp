// 7_raceCondition_02.cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

int sharedVariable = 0;
mutex mtx; // Mutex for synchronization

void increment() {
    for (int i = 0; i < 100000; ++i) {
        mtx.lock(); // Lock the mutex
        int currentValue = sharedVariable;
        this_thread::sleep_for(chrono::microseconds(1)); // Introduce a delay
        sharedVariable = currentValue + 1;
        mtx.unlock(); // Unlock the mutex
    }
}

int main() {
    thread thread1(increment);
    thread thread2(increment);

    thread1.join();
    thread2.join();

    cout << "Expected value: 200000" << endl;
    cout << "Actual value: " << sharedVariable << endl;

    return 0;
}

