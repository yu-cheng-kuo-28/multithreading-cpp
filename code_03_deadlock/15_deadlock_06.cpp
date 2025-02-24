// 15_deadlock_06.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

class Resource {
private:
    mutex mtx;
    condition_variable cv;
    int available_units;

public:
    Resource(int units) : available_units(units) {}

    void acquire() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&]{ return available_units > 0; });
        available_units--;
    }

    void release() {
        unique_lock<mutex> lock(mtx);
        available_units++;
        cv.notify_one();
    }
};

Resource resource1(2);
Resource resource2(2);
Resource resource3(2);

void acquireResources() {
    resource1.acquire();
    resource2.acquire();
    resource3.acquire();
}

void releaseResources() {
    resource1.release();
    resource2.release();
    resource3.release();
}

void threadFunction(int id) {
    acquireResources();
    cout << "Thread " << id << " has acquired all resources" << endl;
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulating work
    releaseResources();
    cout << "Thread " << id << " has released all resources" << endl;
}

int main() {
    thread t1(threadFunction, 1);
    thread t2(threadFunction, 2);
    thread t3(threadFunction, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
