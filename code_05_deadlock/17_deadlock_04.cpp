#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex resource1;
std::mutex resource2;
std::mutex resource3;

// Function to be executed by thread 1
void threadFunction1() {
    std::lock_guard<std::mutex> lock1(resource1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulating work
    std::lock_guard<std::mutex> lock2(resource2);

    std::cout << "Thread 1 has locked resource1 and resource2" << std::endl;
}

// Function to be executed by thread 2
void threadFunction2() {
    std::lock_guard<std::mutex> lock1(resource2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulating work
    std::lock_guard<std::mutex> lock2(resource3);

    std::cout << "Thread 2 has locked resource2 and resource3" << std::endl;
}

// Function to be executed by thread 3
void threadFunction3() {
    std::lock_guard<std::mutex> lock1(resource1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulating work
    std::lock_guard<std::mutex> lock2(resource3);

    std::cout << "Thread 3 has locked resource1 and resource3" << std::endl;
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
