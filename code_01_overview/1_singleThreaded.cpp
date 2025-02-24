/* 1_singleThreaded.cpp */
/*
$ g++ 1_singleThreaded.cpp -o 1_singleThreaded
*/
#include <iostream>
using namespace std;

void function1() {
    for (int i = 0; i < 200; ++i)
        cout << "A";
}

void function2() {
    for (int i = 0; i < 200; ++i)
        cout << "B";
}

int main() {
    function1();
    function2();
    printf("\n");
}

