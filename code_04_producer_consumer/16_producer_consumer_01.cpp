#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cond_var;
std::queue<int> buffer;
const unsigned int MAX_BUFFER_SIZE = 10;

void producer(int value) {
    std::unique_lock<std::mutex> lock(mtx);
    cond_var.wait(lock, [] { return buffer.size() < MAX_BUFFER_SIZE; });

    buffer.push(value);
    std::cout << "Producing " << value << std::endl;
    std::cout << "Buffer size after producing: " << buffer.size() << std::endl << std::endl; // Display buffer size after pushing

    lock.unlock();
    cond_var.notify_one();
}

void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    cond_var.wait(lock, [] { return buffer.size() > 0; });

    int value = buffer.front();
    buffer.pop();
    std::cout << "Consuming " << value << std::endl;
    std::cout << "Buffer size after consuming: " << buffer.size() << std::endl << std::endl; // Display buffer size after popping

    lock.unlock();
    cond_var.notify_one();
}

int main() {
    std::thread producerThread([] {
        for (int i = 1; i <= 20; ++i) {
            producer(i);
        }
    });

    std::thread consumerThread([] {
        for (int i = 1; i <= 20; ++i) { // Changed from i = 0; i <= 20; ++i
            consumer();
        }
    });

    producerThread.join();
    consumerThread.join();

    return 0;
}
