// 17_producer_consumer_02.cpp
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex mtx; // Declares a mutex for critical section management
condition_variable cond_var; // Declares a condition variable for blocking and waking threads
queue<int> buffer; // Declares a queue to act as the buffer
const unsigned int MAX_BUFFER_SIZE = 10; // Sets the maximum size of the buffer

void producer(int value) { // Defines the producer function
    unique_lock<mutex> lock(mtx); // Locks the mutex before accessing the buffer
    cond_var.wait(lock, [] { return buffer.size() < MAX_BUFFER_SIZE; }); // Waits if the buffer is full

    cout << "Producing " << value << endl; // Prints the produced value
    buffer.push(value); // Pushes the value into the buffer
    cout << "Buffer size after producing: " << buffer.size() << endl << endl; // Prints the buffer size after producing

    lock.unlock(); // Unlocks the mutex
    cond_var.notify_one(); // Notifies one waiting thread
}

void consumer() { // Defines the consumer function
    unique_lock<mutex> lock(mtx); // Locks the mutex before accessing the buffer
    cond_var.wait(lock, [] { return buffer.size() > 0; }); // Waits if the buffer is empty

    int value = buffer.front(); // Gets the value from the front of the buffer
    buffer.pop(); // Removes the value from the buffer
    cout << "Consuming " << value << endl; // Prints the consumed value
    cout << "Buffer size after consuming: " << buffer.size() << endl << endl; // Prints the buffer size after consuming

    lock.unlock(); // Unlocks the mutex
    cond_var.notify_one(); // Notifies one waiting thread
}

int main() { // The main function
    thread producerThread([] { // Creates a producer thread
        for (int i = 1; i <= 20; ++i) {
            producer(i); // Produces 20 items
        }
    });

    // Delay before starting consumer thread
    this_thread::sleep_for(chrono::seconds(3));

    thread consumerThread([] { // Creates a consumer thread
        for (int i = 1; i <= 20; ++i) {
            consumer(); // Consumes 20 items
        }
    });

    producerThread.join(); // Waits for producer thread to finish
    consumerThread.join(); // Waits for consumer thread to finish

    return 0; // Ends the program
}
