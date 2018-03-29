#include <iostream>
#include <string>
#include "RingBuffer.h"

using namespace std;


template <typename T>
void foo(T t)
{
    cout << "generic" << endl;
}


void foo(int i)
{
    cout << "specific (non-template) function" << endl;
}


int main()
{
    RingBuffer<string> names(3);
    names.add("Ion");
    names.add("Mihai");
    names.add("Paul");
    names.add("Ionel");  // will replace "Ion" on position 0


    getchar();
    return 0;
}
