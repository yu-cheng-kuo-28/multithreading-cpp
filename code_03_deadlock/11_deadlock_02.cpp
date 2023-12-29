#include <iostream>
#include <thread>
#include <mutex>
#include <utility>

std::mutex mutex1;
std::mutex mutex2;

void threadFunction1() {
    std::lock(mutex1, mutex2); // Lock both mutexes without deadlock
    std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);

    std::cout << "Thread 1 has both mutexes" << std::endl;
}

void threadFunction2() {
    std::lock(mutex1, mutex2); // Lock both mutexes without deadlock
    std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);

    std::cout << "Thread 2 has both mutexes" << std::endl;
}

int main() {
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);

    t1.join();
    t2.join();

    return 0;
}
