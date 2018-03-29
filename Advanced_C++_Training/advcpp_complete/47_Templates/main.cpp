#include <iostream>
#include <string>
#include "RingBuffer.h"

using namespace std;


template <typename T>
void foo(T t)
{
    cout << "generic" << endl;
}


//template <>
//void foo(int i)
//{
//	cout << "template specialization" << endl;
//}


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

    // Old-school iteration
    for (RingBuffer<string>::iterator it = names.begin(); it != names.end(); ++it)
        cout << *it << endl;

    // c++ 11 range for loop
    for (auto name : names) cout << name << endl;

    auto ring2 = names;
    cout << ring2 << endl;

    RingBuffer<int> numbers{1, 2, 3, 4, 5};
    cout << numbers << endl;

    foo<int>(10);
    foo<>(10);
    foo(10);
    
    getchar();
    return 0;
}
