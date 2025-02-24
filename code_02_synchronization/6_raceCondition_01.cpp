// 6_raceCondition_01.cpp
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int sharedVariable = 0;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        int currentValue = sharedVariable;
        this_thread::sleep_for(chrono::microseconds(1)); // Introduce a delay
        sharedVariable = currentValue + 1;
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

