#include <iostream>
#include <thread>
#include <mutex>

std::mutex resource1;
std::mutex resource2;

// Function to be executed by thread 1
void threadFunction1() {
    // Locks are acquired in the order: resource1, then resource2
    std::lock_guard<std::mutex> lock1(resource1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulating work
    std::lock_guard<std::mutex> lock2(resource2);

    std::cout << "Thread 1 has both resources" << std::endl;
}

// Function to be executed by thread 2
void threadFunction2() {
    // Locks are acquired in the same order: resource1, then resource2
    std::lock_guard<std::mutex> lock1(resource1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulating work
    std::lock_guard<std::mutex> lock2(resource2);

    std::cout << "Thread 2 has both resources" << std::endl;
}

int main() {
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);

    t1.join();
    t2.join();

    return 0;
}
