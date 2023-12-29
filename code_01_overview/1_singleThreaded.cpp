#include <iostream>

void function1() 
{
    int i;
    for (i = 0; i < 200; ++i)
        std::cout << "A";
}

void function2() 
{
    int i;
    for (i = 0; i < 200; ++i)
        std::cout << "B";
}

int main() 
{
    function1();
    function2();
    printf("\n");
}

