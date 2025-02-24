/* 4_multithreaded_03.cpp */
// g++ 4_multithreaded_03.cpp -o 4_multithreaded_03 -pthread
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void function1() {
  for (int i = 0; i < 200; ++i) {
    cout << "A";
    this_thread::sleep_for(chrono::nanoseconds(1)); // 0.1 milliseconds = 100 microseconds
  }
}

void function2() {
  for (int i = 0; i < 200; ++i) {
    cout << "B";
    this_thread::sleep_for(chrono::nanoseconds(1)); // 0.1 milliseconds = 100 microseconds
  }
}

void function3(char c) {
  for (int i = 0; i < 200; ++i) {
    cout << c;
    this_thread::sleep_for(chrono::nanoseconds(1)); // 0.1 milliseconds = 100 microseconds
  }
}

int main() {
  thread worker1(function1);
  thread worker2(function2);
  thread worker3(function3, '-');
  worker1.join();
  worker2.join();
  worker3.join();
  cout << "\n";
}

