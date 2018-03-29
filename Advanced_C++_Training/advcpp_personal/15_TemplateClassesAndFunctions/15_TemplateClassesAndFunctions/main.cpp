#include <iostream>
#include <string>
#include "RingBuffer.h"

using namespace std;


template <typename T>
void foo(T t)
{
    cout << "generic" << endl;
}

/*
template <> //if template specialisation exists, it will be called rather then the normal template
void foo(int i)
{
    cout << "specialised template function for no param" << endl;
}
*/

/*
void foo(int i)
{
    cout << "specific (non-template) function" << endl;
}
*/

int main()
{
    RingBuffer<string> names(3);
    names.add("Ion");
    names.add("Mihai");
    names.add("Paul");
    names.add("Ionel");  // will replace "Ion" on position 0
    
    for (RingBuffer<string>::iterator it = names.begin(); it != names.end(); ++it)
    {
        cout << *it << endl;
    }
    
    RingBuffer<int> numbers{ 1, 2, 3, 4 };

    foo<int>(10); //calls template function because of <>
    foo<>(10); // same as asbove
    foo(10); // calls nnon template function || daca nu este functie non template, va fi chemata si in cazul acesta functia cucu template

    getchar();
    return 0;
}
