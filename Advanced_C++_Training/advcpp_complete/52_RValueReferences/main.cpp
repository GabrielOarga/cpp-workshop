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
 * This is what rValue references are for!
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

// usually you don't need the const modifier for functions which accept rValue references
// we'll see soon that a benefit is that we can change objects and "steal" resources from
// objects that we no longer need!
// and we can do that if a is not const
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
    A a1;
    auto a2 = getA();
    auto a3(getA());
    vector<A> vec{a1, a2, a3, A(), getA()};
    vec.push_back(A());

    // Step 1

    A&  lval1 = a1;         // nothing new: an lValue reference bound to an lValue
    // A&& rval1 = a1;      // this doesn't work: an rValue reference bound to a lValue
    A&& rval2 = A();        // I can bind an rValue reference to an rValue!

    A&& rval3 = getA();     // this also works

    auto&& rval4 = getA();  // this is the preferred way

    // => rValue references give a way to differentiate between temporary values and non-temporary values
    // <=> differentiate between lValues and rValues

    // Step 3: let's call the overloaded functions
    foo(a1);        // calls foo(const A& a)
    foo(lval1);     // calls foo(const A& a)
    foo(rval2);     // calls foo(const A& a)

    foo(getA());    // calls foo(A&& a)
    foo(A());       // calls foo(A&& a)

    cout << "Test passing int& and int&& to an overloaded foo() function: " << endl;
    int v{ 100 };
    int& pv = v;
    foo(pv);        // calls foo(int& a)
    foo(pv++);      // calls foo(int&& a)
    foo(++pv);      // calls foo(int& a)

    auto lambda = []() { return 500; };
    foo(lambda());  // calls foo(int&& a)

    getchar();
    return 0;
}
