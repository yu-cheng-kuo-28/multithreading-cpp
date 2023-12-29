#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Resource {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int available_units;

public:
    Resource(int units) : available_units(units) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]{ return available_units > 0; });
        available_units--;
    }

    void release() {
        std::unique_lock<std::mutex> lock(mtx);
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
    std::cout << "Thread " << id << " has acquired all resources" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulating work
    releaseResources();
    std::cout << "Thread " << id << " has released all resources" << std::endl;
}

int main() {
    std::thread t1(threadFunction, 1);
    std::thread t2(threadFunction, 2);
    std::thread t3(threadFunction, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
