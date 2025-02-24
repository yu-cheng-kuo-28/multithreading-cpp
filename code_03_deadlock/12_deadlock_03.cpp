// 12_deadlock_03.cpp
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex resource1;
mutex resource2;

// Function to be executed by thread 1
void threadFunction1() {
    // Locks are acquired in the order: resource1, then resource2
    lock_guard<mutex> lock1(resource1);
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulating work
    lock_guard<mutex> lock2(resource2);

    cout << "Thread 1 has both resources" << endl;
}

// Function to be executed by thread 2
void threadFunction2() {
    // Locks are acquired in the same order: resource1, then resource2
    lock_guard<mutex> lock1(resource1);
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulating work
    lock_guard<mutex> lock2(resource2);

    cout << "Thread 2 has both resources" << endl;
}

int main() {
    thread t1(threadFunction1);
    thread t2(threadFunction2);

    t1.join();
    t2.join();

    return 0;
}
