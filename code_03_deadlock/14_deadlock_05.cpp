// 14_deadlock_05.cpp
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex resource1;
mutex resource2;
mutex resource3;

void threadFunction1() {
    lock_guard<mutex> lock1(resource1);
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulating work
    lock_guard<mutex> lock2(resource2);
    lock_guard<mutex> lock3(resource3);  // Attempt to lock resource3 as well

    cout << "Thread 1 has locked resource1, resource2, and resource3" << endl;
}

void threadFunction2() {
    lock_guard<mutex> lock1(resource1);
    this_thread::sleep_for(chrono::milliseconds(100));
    lock_guard<mutex> lock2(resource2);
    lock_guard<mutex> lock3(resource3);

    cout << "Thread 2 has locked resource1, resource2, and resource3" << endl;
}

void threadFunction3() {
    lock_guard<mutex> lock1(resource1);
    this_thread::sleep_for(chrono::milliseconds(100));
    lock_guard<mutex> lock2(resource2);
    lock_guard<mutex> lock3(resource3);

    cout << "Thread 3 has locked resource1, resource2, and resource3" << endl;
}

int main() {
    thread t1(threadFunction1);
    thread t2(threadFunction2);
    thread t3(threadFunction3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
