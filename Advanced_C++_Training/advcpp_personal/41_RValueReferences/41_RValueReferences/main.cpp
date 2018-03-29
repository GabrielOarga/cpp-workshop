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


void foo(int&& a) //Without this overload, rvalue get's transformed to lvalue automatically [test]
{
    cout << "int rValue" << endl;
}


int main()
{
    A a1;
    auto a2 = getA();
    
    A& lval1 = a1;
    A&& rval1 = A();
    A&& rval2 = getA(); //#1
    
    foo(a1);
    foo(lval1);
    foo(rval1);
    foo(rval2);
    
    foo(getA()); //the temp value get's sent to the foo function, without beeing lost in the assignment from #1
    foo(A()); // smae as above
    
    getchar();
    return 0;
}
