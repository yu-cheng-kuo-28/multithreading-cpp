// 18_readers_writers_01.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
using namespace std;

mutex resource_mutex; // Mutex for protecting shared resource access
mutex reader_count_mutex; // Mutex for protecting reader count variable
condition_variable cv; // Condition variable for thread synchronization
int reader_count = 0; // Global variable to keep track of reader count

void read(int reader_id) { // Function for reader thread
    {
        unique_lock<mutex> lock(reader_count_mutex); // Locks reader_count_mutex
        reader_count++; // Increments reader count
        if (reader_count == 1) {
            resource_mutex.lock(); // Locks resource_mutex if first reader
        }
    }
    
    cout << "Reader " << reader_id << " is reading." << endl; // Outputs reading status
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulates reading operation

    {
        unique_lock<mutex> lock(reader_count_mutex); // Re-locks reader_count_mutex
        cout << "Reader " << reader_id << " has finished reading." << endl; // Outputs finished reading status
        reader_count--; // Decrements reader count
        if (reader_count == 0) {
            resource_mutex.unlock(); // Unlocks resource_mutex if last reader
        }
    }
}

void write(int writer_id) { // Function for writer thread
    resource_mutex.lock(); // Locks resource_mutex
    cout << "Writer " << writer_id << " is writing." << endl; // Outputs writing status
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulates writing operation
    cout << "Writer " << writer_id << " has finished writing." << endl; // Outputs finished writing status
    resource_mutex.unlock(); // Unlocks resource_mutex
}

int main() { // Main function
    vector<thread> readers; // Vector to store reader threads
    vector<thread> writers; // Vector to store writer threads

    for (int i = 1; i <= 5; ++i) { // Loops to create 5 readers and 5 writers
        readers.push_back(thread(read, i)); // Starts reader thread
        writers.push_back(thread(write, i)); // Starts writer thread
    }

    for (auto& t : readers) t.join(); // Waits for all reader threads to finish
    for (auto& t : writers) t.join(); // Waits for all writer threads to finish

    return 0; // Ends the program
}
