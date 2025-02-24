// 8_raceCondition_03.cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
using namespace std;

// (1) Race Condition 01: The race condition may not happen if the CPU is faster enough
int sharedVariable_race_01 = 0;

void increment_race_01() {
    for (int i = 0; i < 100000; ++i) {
        sharedVariable_race_01++;
    }
}

// (2) Race Condition 02: Introduce delay to make race condition happen definitely
int sharedVariable_race_02 = 0;
int currentValue_02 = sharedVariable_race_02;

void increment_race_02() {
    for (int i = 0; i < 100000; ++i) {
        int currentValue_02 = sharedVariable_race_02;
        this_thread::sleep_for(chrono::microseconds(1)); // Introduce a delay
        sharedVariable_race_02 = currentValue_02 + 1;
    }
}


// (3) Mutex 01: With separate "mtx.lock();" & "mtx.unlock();"
int sharedVariable_mutex_01 = 0;
mutex mtx_1; // Mutex for synchronization
int currentValue_mutex = sharedVariable_mutex_01;

void increment_mutex_01() {
    for (int i = 0; i < 100000; ++i) {
        mtx_1.lock(); // Lock the mutex
        int currentValue_mutex = sharedVariable_mutex_01;
        this_thread::sleep_for(chrono::microseconds(1)); // Introduce a delay
        sharedVariable_mutex_01 = currentValue_mutex + 1;
        mtx_1.unlock(); // Unlock the mutex
    }
}


// (4) Mutex 02: With "lock_guard<mutex>"
int sharedVariable_mutex_02 = 0;
mutex mtx_2; // Mutex for synchronization

void increment_mutex_02() {
    for (int i = 0; i < 100000; ++i) {
        lock_guard<mutex> lock(mtx_2); // Automatically locks and unlocks
        sharedVariable_mutex_02++;
    }
}
/*
lock_guard is a safer alternative to manual locking and unlocking because it
automatically unlocks the mutex when it goes out of scope.
*/


// (5) Atomic: With "atomic<int>"
atomic<int> sharedVariable_atomic(0);

void increment_atomic() {
    for (int i = 0; i < 100000; ++i) {
        sharedVariable_atomic++;
    }
}
/*
In this example, sharedVariable is declared as atomic<int>.
Atomic operations are indivisible, ensuring that the variable is incremented
correctly even when multiple threads access it concurrently.
*/


int main() {
    thread thread1(increment_race_01);
    thread thread2(increment_race_01);
    thread thread3(increment_race_02);
    thread thread4(increment_race_02);

    thread thread5(increment_mutex_01);
    thread thread6(increment_mutex_01);
    thread thread7(increment_mutex_02);
    thread thread8(increment_mutex_02);

    thread thread9(increment_atomic);
    thread thread10(increment_atomic);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();
    thread8.join();
    thread9.join();
    thread10.join();

    cout << "Expected value: 200000" << endl;

    cout << "Actual value of Race Condition 01: " << sharedVariable_race_01 << endl;
    cout << "Actual value of Race Condition 02: " << sharedVariable_race_02 << endl;

    cout << "Actual value of Mutex 01: " << sharedVariable_mutex_01 << endl;
    cout << "Actual value of Mutex 02: " << sharedVariable_mutex_02 << endl;

    cout << "Actual value of Atomic: " << sharedVariable_atomic.load() << endl;

    return 0;
}

