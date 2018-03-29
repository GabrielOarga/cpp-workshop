#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * In C++98 we had of course references and in C++11 these references are specifically
 * called lValue references, because C++11 introduces rValue references (we'll see soon)
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


void test_lvalue_references()
{
}


int main()
{
    test_lvalue_references();

    getchar();
    return 0;
}
