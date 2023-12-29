/*
Though multithreaded, the lack of delay 
*/

#include <iostream>
#include <thread>

void function1() {
    for (int i = 0; i < 200; ++i)
        std::cout << "A";
}

void function2() {
    for (int i = 0; i < 200; ++i)
        std::cout << "B";
}

int main() {
    std::thread worker1(function1);
    std::thread worker2(function2);
    worker1.join();
    worker2.join();
    printf("\n");
}

