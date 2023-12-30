#include <iostream>
#include <thread>
#include <mutex>
#include <utility>

std::mutex resource1;
std::mutex resource2;

void threadFunction1() {
    std::lock(resource1, resource2); // Lock both mutexes without deadlock
    std::lock_guard<std::mutex> lock1(resource1, std::adopt_lock);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulating work
    std::lock_guard<std::mutex> lock2(resource2, std::adopt_lock);

    std::cout << "Thread 1 has both mutexes" << std::endl;
}

void threadFunction2() {
    std::lock(resource1, resource2); // Lock both mutexes without deadlock
    std::lock_guard<std::mutex> lock2(resource2, std::adopt_lock);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulating work
    std::lock_guard<std::mutex> lock1(resource1, std::adopt_lock);

    std::cout << "Thread 2 has both mutexes" << std::endl;
}

int main() {
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);

    t1.join();
    t2.join();

    return 0;
}
