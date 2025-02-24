// 9_conditionVariable.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex mtx;
condition_variable cv;
bool ready = false;

void workerThread() {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });

    // Perform work after the condition is met
    cout << "Worker thread is processing data." << endl;
}

int main() {
    thread worker(workerThread);

    {
        lock_guard<mutex> lock(mtx);
        ready = true; // Try replacing true with false and test what would happen!
    }
    cv.notify_one();

    worker.join();
    cout << "Back in main." << endl;

    return 0;
}

