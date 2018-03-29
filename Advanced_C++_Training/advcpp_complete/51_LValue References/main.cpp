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
    vector<A> vec{A(), a, b};
    vec.push_back(A());

    A &ref_a = a;  // we can bind an lValue reference to an lValue
    // if you try to bind an lValue reference to an rValue:
    A &ref_a2 = getA();  // here the result is not guaranteed: in VS2015 we get a warning
                         // in GCC we get an error

    // BUT: we can make this kind of assignment work:
    const A &ref_a3 = getA();

    // so basically if we use auto, auto means const Reference&:
    auto ref_a4 = getA();  // ref_a4 is of type const A&

    // RULE1: const lValue references can bind to rValues !!!
    // What happens is that the life-time of the temporary object returned by
    // the rValue gets extended, being "captured" by a const lValue reference
    // => it will live until the lValue reference gets out of scope
    // the fact that it's const means that we won't escape the temporary object!

    // if you think a bit, it has to be like this:
    // the copy constructor has a const lValue reference parameter:
    // this means that with a copy constructor we can do things like this:
    A a2(getA());
    auto a3(getA());    // getA() is an rValue => I can pass a rValue to the copy constructor
                        // and of course, the constructed object lives until it leaves its scope
}


int main()
{
    test_lvalue_references();

    getchar();
    return 0;
}
