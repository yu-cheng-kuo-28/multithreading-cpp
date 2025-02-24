// 10_deadlock_01.cpp
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex resource1;
mutex resource2;

void threadFunction1() {
    lock_guard<mutex> lock1(resource1);
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulating work
    lock_guard<mutex> lock2(resource2); // This will wait for resource2

    cout << "Thread 1 has both mutexes" << endl;
}

void threadFunction2() {
    lock_guard<mutex> lock2(resource2);
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulating work
    lock_guard<mutex> lock1(resource1); // This will wait for resource1

    cout << "Thread 2 has both mutexes" << endl;
}

int main() {
    thread t1(threadFunction1);
    thread t2(threadFunction2);

    t1.join();
    t2.join();

    return 0;
}
