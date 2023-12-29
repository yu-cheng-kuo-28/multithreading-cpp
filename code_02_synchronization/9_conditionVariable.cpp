#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void workerThread() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });

    // Perform work after the condition is met
    std::cout << "Worker thread is processing data." << std::endl;
}

int main() {
    std::thread worker(workerThread);

    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one();

    worker.join();
    std::cout << "Back in main." << std::endl;

    return 0;
}

