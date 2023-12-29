#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <random>
#include <chrono>

std::mutex resource_mutex;
std::mutex reader_count_mutex;
std::condition_variable reader_cv, writer_cv;
int reader_count = 0, writer_count = 0;
bool writer_waiting = false;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(100, 500);

void read(int reader_id) {
    {
        std::unique_lock<std::mutex> lock(reader_count_mutex);
        reader_cv.wait(lock, [] { return !writer_waiting; });

        reader_count++;
        if (reader_count == 1) {
            resource_mutex.lock();
        }

        std::cout << "Reader " << reader_id << " is reading." << std::endl;
    }

    // Simulating reading
    std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));

    {
        std::unique_lock<std::mutex> lock(reader_count_mutex);
        std::cout << "Reader " << reader_id << " has finished reading." << std::endl;
        reader_count--;
        if (reader_count == 0) {
            resource_mutex.unlock();
            writer_cv.notify_one();
        }
    }
}

void write(int writer_id) {
    {
        std::unique_lock<std::mutex> lock(reader_count_mutex);
        writer_count++;
        writer_waiting = true;

        writer_cv.wait(lock, [] { return reader_count == 0; });
        resource_mutex.lock();

        std::cout << "Writer " << writer_id << " is writing." << std::endl;
    }

    // Simulating writing
    std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));

    {
        std::unique_lock<std::mutex> lock(reader_count_mutex);
        std::cout << "Writer " << writer_id << " has finished writing." << std::endl;
        writer_count--;
        writer_waiting = writer_count > 0;
        resource_mutex.unlock();
        if (writer_waiting) {
            writer_cv.notify_one();
        } else {
            reader_cv.notify_all();
        }
    }
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
