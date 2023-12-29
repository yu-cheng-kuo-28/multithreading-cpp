#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

std::mutex resource_mutex;
std::mutex reader_count_mutex;
std::condition_variable cv;
int reader_count = 0;

void read(int reader_id) {
    {
        std::unique_lock<std::mutex> lock(reader_count_mutex);
        reader_count++;
        if (reader_count == 1) {
            resource_mutex.lock();
        }
    }
    
    // Reading...
    std::cout << "Reader " << reader_id << " is reading." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate reading time

    {
        std::unique_lock<std::mutex> lock(reader_count_mutex);
        reader_count--;
        if (reader_count == 0) {
            resource_mutex.unlock();
        }
    }
}

void write(int writer_id) {
    resource_mutex.lock();
    // Writing...
    std::cout << "Writer " << writer_id << " is writing." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate writing time
    resource_mutex.unlock();
}

int main() {
    std::vector<std::thread> readers;
    std::vector<std::thread> writers;

    for (int i = 1; i <= 5; ++i) {
        readers.push_back(std::thread(read, i));
        writers.push_back(std::thread(write, i));
    }

    for (auto& t : readers) t.join();
    for (auto& t : writers) t.join();

    return 0;
}
