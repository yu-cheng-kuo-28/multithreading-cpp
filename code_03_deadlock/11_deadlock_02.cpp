// 11_deadlock_02.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <utility>
using namespace std;

mutex resource1;
mutex resource2;

void threadFunction1() {
    lock(resource1, resource2); // Lock both mutexes without deadlock
    lock_guard<mutex> lock1(resource1, adopt_lock);
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulating work
    lock_guard<mutex> lock2(resource2, adopt_lock);

    cout << "Thread 1 has both mutexes" << endl;
}

void threadFunction2() {
    lock(resource1, resource2); // Lock both mutexes without deadlock
    lock_guard<mutex> lock2(resource2, adopt_lock);
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulating work
    lock_guard<mutex> lock1(resource1, adopt_lock);

    cout << "Thread 2 has both mutexes" << endl;
}

int main() {
    thread t1(threadFunction1);
    thread t2(threadFunction2);

    t1.join();
    t2.join();

    return 0;
}
