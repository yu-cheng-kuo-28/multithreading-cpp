#include <iostream> // Include for standard input/output stream objects
#include <thread> // Include for using thread functionality
#include <mutex> // Include for using mutex for synchronization
#include <condition_variable> // Include for using condition variables
#include <vector> // Include for using the vector container

std::mutex resource_mutex; // Mutex for resource access
std::mutex reader_count_mutex; // Mutex for reader count access
std::condition_variable cv; // Condition variable for reader/writer signaling
int reader_count = 0; // Counter for number of readers

void read(int reader_id) { // Function for reader threads
    {
        std::unique_lock<std::mutex> lock(reader_count_mutex); // Lock for reader count
        reader_count++; // Increment reader count
        if (reader_count == 1) { // If first reader, lock resource
            resource_mutex.lock();
        }
    }
    
    // Reading section...
    std::cout << "Reader " << reader_id << " is reading." << std::endl; // Output reading status
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate reading time

    {
        std::unique_lock<std::mutex> lock(reader_count_mutex); // Lock for reader count
        reader_count--; // Decrement reader count
        if (reader_count == 0) { // If last reader, unlock resource
            resource_mutex.unlock();
        }
    }
}

void write(int writer_id) { // Function for writer threads
    resource_mutex.lock(); // Lock resource for writing
    // Writing section...
    std::cout << "Writer " << writer_id << " is writing." << std::endl; // Output writing status
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate writing time
    resource_mutex.unlock(); // Unlock resource after writing
}

int main() { // Main function
    std::vector<std::thread> readers; // Vector to store reader threads
    std::vector<std::thread> writers; // Vector to store writer threads

    for (int i = 1; i <= 5; ++i) { // Create 5 reader and writer threads
        readers.push_back(std::thread(read, i)); // Start reader thread
        writers.push_back(std::thread(write, i)); // Start writer thread
    }

    for (auto& t : readers) t.join(); // Join all reader threads
    for (auto& t : writers) t.join(); // Join all writer threads

    return 0; // End of program
}
