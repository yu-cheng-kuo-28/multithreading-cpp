#include <iostream> // Includes the standard I/O library
#include <queue> // Includes the queue library for queue operations
#include <thread> // Includes the thread library for threading operations
#include <mutex> // Includes the mutex library for synchronization
#include <condition_variable> // Includes the condition_variable library for thread communication

std::mutex mtx; // Declares a mutex for critical section management
std::condition_variable cond_var; // Declares a condition variable for blocking and waking threads
std::queue<int> buffer; // Declares a queue to act as the buffer
const unsigned int MAX_BUFFER_SIZE = 10; // Sets the maximum size of the buffer

void producer(int value) { // Defines the producer function
    std::unique_lock<std::mutex> lock(mtx); // Locks the mutex before accessing the buffer
    cond_var.wait(lock, [] { return buffer.size() < MAX_BUFFER_SIZE; }); // Waits if the buffer is full

    std::cout << "Producing " << value << std::endl; // Prints the produced value
    buffer.push(value); // Pushes the value into the buffer
    std::cout << "Buffer size after producing: " << buffer.size() << std::endl << std::endl; // Prints the buffer size after producing

    lock.unlock(); // Unlocks the mutex
    cond_var.notify_one(); // Notifies one waiting thread
}

void consumer() { // Defines the consumer function
    std::unique_lock<std::mutex> lock(mtx); // Locks the mutex before accessing the buffer
    cond_var.wait(lock, [] { return buffer.size() > 0; }); // Waits if the buffer is empty

    int value = buffer.front(); // Gets the value from the front of the buffer
    buffer.pop(); // Removes the value from the buffer
    std::cout << "Consuming " << value << std::endl; // Prints the consumed value
    std::cout << "Buffer size after consuming: " << buffer.size() << std::endl << std::endl; // Prints the buffer size after consuming

    lock.unlock(); // Unlocks the mutex
    cond_var.notify_one(); // Notifies one waiting thread
}

int main() { // The main function
    std::thread producerThread([] { // Creates a producer thread
        for (int i = 1; i <= 20; ++i) {
            producer(i); // Produces 20 items
        }
    });

    // Delay before starting consumer thread
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::thread consumerThread([] { // Creates a consumer thread
        for (int i = 1; i <= 20; ++i) {
            consumer(); // Consumes 20 items
        }
    });

    producerThread.join(); // Waits for producer thread to finish
    consumerThread.join(); // Waits for consumer thread to finish

    return 0; // Ends the program
}
