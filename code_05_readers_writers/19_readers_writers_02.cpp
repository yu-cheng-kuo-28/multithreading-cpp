// 19_readers_writers_02.cpp
#include <iostream> // Includes the standard I/O library
#include <thread> // Includes the thread library for using threads
#include <mutex> // Includes the mutex library for synchronization
#include <condition_variable> // Includes the condition_variable library for waiting for conditions
#include <vector> // Includes the vector library for using vector container
#include <random> // Includes the random library for generating random numbers
#include <chrono> // Includes the chrono library for dealing with durations
using namespace std;

mutex resource_mutex; // Mutex to protect shared resource access
mutex reader_count_mutex; // Mutex to protect reader count
condition_variable reader_cv, writer_cv; // Condition variables for readers and writers
int reader_count = 0, writer_count = 0; // Counters for the number of readers and writers
bool writer_waiting = false; // Flag to indicate if a writer is waiting

random_device rd; // Random device to seed the generator
mt19937 gen(rd()); // Mersenne Twister generator
uniform_int_distribution<> dis(100, 500); // Uniform distribution for random sleep duration

void read(int reader_id) { // Function for reader threads
    {
        unique_lock<mutex> lock(reader_count_mutex); // Acquire lock for reader count
        reader_cv.wait(lock, [] { return !writer_waiting; }); // Wait until no writer is waiting

        reader_count++; // Increment reader count
        if (reader_count == 1) {
            resource_mutex.lock(); // Lock resource if first reader
        }

        cout << "Reader " << reader_id << " is reading." << endl; // Print reading message
    }

    this_thread::sleep_for(chrono::milliseconds(dis(gen))); // Simulate reading by sleeping

    {
        unique_lock<mutex> lock(reader_count_mutex); // Re-acquire lock for reader count
        cout << "Reader " << reader_id << " has finished reading." << endl; // Print finished reading message
        reader_count--; // Decrement reader count
        if (reader_count == 0) {
            resource_mutex.unlock(); // Unlock resource if last reader
            writer_cv.notify_one(); // Notify one writer if any
        }
    }
}

void write(int writer_id) { // Function for writer threads
    {
        unique_lock<mutex> lock(reader_count_mutex); // Acquire lock for writer count
        writer_count++; // Increment writer count
        writer_waiting = true; // Set writer waiting flag

        writer_cv.wait(lock, [] { return reader_count == 0; }); // Wait until no readers are present
        resource_mutex.lock(); // Lock resource for writing

        cout << "Writer " << writer_id << " is writing." << endl; // Print writing message
    }

    this_thread::sleep_for(chrono::milliseconds(dis(gen))); // Simulate writing by sleeping

    {
        unique_lock<mutex> lock(reader_count_mutex); // Re-acquire lock for writer count
        cout << "Writer " << writer_id << " has finished writing." << endl; // Print finished writing message
        writer_count--; // Decrement writer count
        writer_waiting = writer_count > 0; // Update writer waiting flag
        resource_mutex.unlock(); // Unlock resource after writing
        if (writer_waiting) {
            writer_cv.notify_one(); // Notify next writer if any
        } else {
            reader_cv.notify_all(); // Notify all readers if no writers
        }
    }
}

int main() { // Main function
    vector<thread> readers; // Vector to store reader threads
    vector<thread> writers; // Vector to store writer threads

    for (int i = 1; i <= 5; ++i) { // Create and start 5 reader and writer threads
        readers.push_back(thread(read, i)); // Start reader thread
        writers.push_back(thread(write, i)); // Start writer thread
    }

    for (auto& t : readers) t.join(); // Wait for all reader threads to finish
    for (auto& t : writers) t.join(); // Wait for all writer threads to finish

    return 0; // End of program
}
