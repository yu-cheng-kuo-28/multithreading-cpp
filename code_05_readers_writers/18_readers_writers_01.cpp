#include <iostream> // Includes standard I/O stream library
#include <thread> // Includes thread library for multi-threading
#include <mutex> // Includes mutex library for synchronization
#include <condition_variable> // Includes condition_variable library for thread waiting
#include <vector> // Includes vector library for dynamic array functionality

std::mutex resource_mutex; // Mutex for protecting shared resource access
std::mutex reader_count_mutex; // Mutex for protecting reader count variable
std::condition_variable cv; // Condition variable for thread synchronization
int reader_count = 0; // Global variable to keep track of reader count

void read(int reader_id) { // Function for reader thread
    {
        std::unique_lock<std::mutex> lock(reader_count_mutex); // Locks reader_count_mutex
        reader_count++; // Increments reader count
        if (reader_count == 1) {
            resource_mutex.lock(); // Locks resource_mutex if first reader
        }
    }
    
    std::cout << "Reader " << reader_id << " is reading." << std::endl; // Outputs reading status
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulates reading operation

    {
        std::unique_lock<std::mutex> lock(reader_count_mutex); // Re-locks reader_count_mutex
        std::cout << "Reader " << reader_id << " has finished reading." << std::endl; // Outputs finished reading status
        reader_count--; // Decrements reader count
        if (reader_count == 0) {
            resource_mutex.unlock(); // Unlocks resource_mutex if last reader
        }
    }
}

void write(int writer_id) { // Function for writer thread
    resource_mutex.lock(); // Locks resource_mutex
    std::cout << "Writer " << writer_id << " is writing." << std::endl; // Outputs writing status
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulates writing operation
    std::cout << "Writer " << writer_id << " has finished writing." << std::endl; // Outputs finished writing status
    resource_mutex.unlock(); // Unlocks resource_mutex
}

int main() { // Main function
    std::vector<std::thread> readers; // Vector to store reader threads
    std::vector<std::thread> writers; // Vector to store writer threads

    for (int i = 1; i <= 5; ++i) { // Loops to create 5 readers and 5 writers
        readers.push_back(std::thread(read, i)); // Starts reader thread
        writers.push_back(std::thread(write, i)); // Starts writer thread
    }

    for (auto& t : readers) t.join(); // Waits for all reader threads to finish
    for (auto& t : writers) t.join(); // Waits for all writer threads to finish

    return 0; // Ends the program
}
