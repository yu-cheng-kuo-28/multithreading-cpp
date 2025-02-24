// 13_deadlock_04.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

mutex resource1;
mutex resource2;
mutex resource3;

// Function to be executed by thread 1
void threadFunction1() {
    lock_guard<mutex> lock1(resource1);
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulating work
    lock_guard<mutex> lock2(resource2);

    cout << "Thread 1 has locked resource1 and resource2" << endl;
}

// Function to be executed by thread 2
void threadFunction2() {
    lock_guard<mutex> lock1(resource2);
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulating work
    lock_guard<mutex> lock2(resource3);

    cout << "Thread 2 has locked resource2 and resource3" << endl;
}

// Function to be executed by thread 3
void threadFunction3() {
    lock_guard<mutex> lock1(resource1);
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulating work
    lock_guard<mutex> lock2(resource3);

    cout << "Thread 3 has locked resource1 and resource3" << endl;
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
