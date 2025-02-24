// 16_producer_consumer_01.cpp
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex mtx; // Mutex for synchronization
condition_variable cond_var; // Condition variable for producer-consumer signaling
queue<int> buffer; // Queue to act as a buffer
const unsigned int MAX_BUFFER_SIZE = 10; // Maximum size of the buffer

void producer(int value) {
    unique_lock<mutex> lock(mtx); // Lock the mutex
    cond_var.wait(lock, [] { return buffer.size() < MAX_BUFFER_SIZE; }); // Wait until there's space in buffer

    buffer.push(value); // Add value to the buffer
    cout << "Producing " << value << endl; // Output the produced value
    cout << "Buffer size after producing: " << buffer.size() << endl << endl; // Display buffer size after producing

    lock.unlock(); // Unlock the mutex
    cond_var.notify_one(); // Notify one waiting thread
}

void consumer() {
    unique_lock<mutex> lock(mtx); // Lock the mutex
    cond_var.wait(lock, [] { return buffer.size() > 0; }); // Wait until there's something in the buffer

    int value = buffer.front(); // Get the front value from buffer
    buffer.pop(); // Remove the value from buffer
    cout << "Consuming " << value << endl; // Output the consumed value
    cout << "Buffer size after consuming: " << buffer.size() << endl << endl; // Display buffer size after consuming

    lock.unlock(); // Unlock the mutex
    cond_var.notify_one(); // Notify one waiting thread
}

int main() {
    thread producerThread([] {
        for (int i = 1; i <= 20; ++i) {
            producer(i); // Create a thread to produce values
        }
    });

    thread consumerThread([] {
        for (int i = 1; i <= 20; ++i) {
            consumer(); // Create a thread to consume values
        }
    });

    producerThread.join(); // Wait for producer thread to finish
    consumerThread.join(); // Wait for consumer thread to finish

    return 0;
}
