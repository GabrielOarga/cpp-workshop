#include <iostream>
#include <vector>

using namespace std;

/**
 * We've seen so far that there are some potential inneficiencies
 * when passing temporary values: e.g. insert a value in a vector
 *
 * If we detect such cases, we could maybe handle them differently
 * (like we handle non-temporary values) => gain back efficiency
 *
 * This is what rValue references are for
 */

struct A
{
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
};


A getA()
{
    return A();
}


// Step 2: let's define two overloaded functions:
void foo(const A& a)
{
    cout << "function involving an lValue" << endl;
}


void foo(A&& a)
{
    cout << "function involving an rValue" << endl;
}


void foo(int& a)
{
    cout << "int lValue" << endl;
}


void foo(int&& a)
{
    cout << "int rValue" << endl;
}


int main()
{

    getchar();
    return 0;
}
