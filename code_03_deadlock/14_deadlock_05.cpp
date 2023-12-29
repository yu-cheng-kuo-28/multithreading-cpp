#include <iostream>
#include <thread>
#include <mutex>

std::mutex resource1;
std::mutex resource2;
std::mutex resource3;

void threadFunction1() {
    std::lock_guard<std::mutex> lock1(resource1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulating work
    std::lock_guard<std::mutex> lock2(resource2);
    std::lock_guard<std::mutex> lock3(resource3);  // Attempt to lock resource3 as well

    std::cout << "Thread 1 has locked resource1, resource2, and resource3" << std::endl;
}

void threadFunction2() {
    std::lock_guard<std::mutex> lock1(resource1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock2(resource2);
    std::lock_guard<std::mutex> lock3(resource3);

    std::cout << "Thread 2 has locked resource1, resource2, and resource3" << std::endl;
}

void threadFunction3() {
    std::lock_guard<std::mutex> lock1(resource1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock2(resource2);
    std::lock_guard<std::mutex> lock3(resource3);

    std::cout << "Thread 3 has locked resource1, resource2, and resource3" << std::endl;
}

int main() {
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);
    std::thread t3(threadFunction3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
