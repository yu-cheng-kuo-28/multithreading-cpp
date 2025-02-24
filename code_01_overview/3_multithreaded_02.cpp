/* 3_multithreaded_02.cpp */
/*
$ g++ 3_multithreaded_02.cpp -o 3_multithreaded_02 -pthread
*/
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void function1() {
    for (int i = 0; i < 200; ++i) {
        cout << "A";
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

void function2() {
    for (int i = 0; i < 200; ++i) {
        cout << "B";
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

int main() {
    thread worker1(function1);
    thread worker2(function2);
    worker1.join();
    worker2.join();
    cout << "\n";
}
