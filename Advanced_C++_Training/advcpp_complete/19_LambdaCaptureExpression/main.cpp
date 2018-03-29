#include <iostream>
using namespace std;


int main()
{
    auto a = 1, b = 2, c = 3;
    // pass all by reference, in order to get all changes done in other places
    // if by value => a new scope will be created, and it won't be changed!!!!! READ THIS!!! :)
    auto print = [&]() { cout << "a=" << a << ", b=" << b << ", c=" << c << endl; };
    print();

    // pass all by reference, increment a
    [&]() { a++; cout << "a was incremented: "; }();
    print();

    // pass only a and b, by value; see: passing print also, in order to use it
    [a, b, print]() { cout << "a and b were passed by value: "; print(); }();

    // everything is passed by value, except c, which is passed by reference
    [=, &c]() { c++; cout << "c was incremented: "; print(); }();

    auto inc = [&b, print](int amount) { b += amount; cout << "b was incremented by " << amount << ": "; print(); };
    inc(10);
    inc(20);
    inc(30);

    getchar();
    return 0;
}
