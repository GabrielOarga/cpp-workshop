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
    A a;
    auto b = getA();
    vector<A> vec{a, b, A()};
    
    A &ref_a = a; // I cna bind and lValue to and lValue reference
    
//    A &ref_a2 = getA(); //Non-const lvalue reference to type 'A' cannot bind to a temporary of type 'A'n on pre cpp14 compiler
    
    const A &ref_a3 = getA();
    const auto ref_a4 = getA();
    
}


int main()
{
    test_lvalue_references();

    getchar();
    return 0;
}
