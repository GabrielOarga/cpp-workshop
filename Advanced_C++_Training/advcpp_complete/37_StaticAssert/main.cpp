#include <iostream>
#include <cassert>
#include <stdexcept>
#include "RandomUtil.h"

using namespace std;
using namespace edocti::utils;


/**
 * In C++03 we have two main ways of dealing with errors:
 * - assert: runtime assertions
 * - exceptions
 * In C++11 a third mechanism was added:
 * - static_assert
 * 
 * These are assertions that can be verified by the compiler
 */


template <typename L, typename R>
L compare(L l, R r)  // yes, we can lose precision
{
    static_assert(sizeof(L) <= sizeof(R), "Left type is too big");
    static_assert(std::is_arithmetic<L>() && is_arithmetic<R>(), "Not arithmetic types");
    return l - r;
}


template <typename T>
T factorial(T a)
{
    static_assert(std::is_integral<T>::value, "T is not integral");
    // The following assert cannot be solved by the compiler. It's pretty clear why:
    // static_assert(a >= 0, "Cannot calculate factorial(negative number)");

    if (a < 0) {
        throw std::invalid_argument("Cannot calculate factorial of negative number");
    }
    T result = 1;
    while (a > 0) {
        result *= a;
        --a;
    }
    return result;
}


struct A
{
    virtual void foo() const { cout << "A::foo()" << endl; }
    virtual ~A() = default;
};
struct B : public A
{
    virtual void foo() const override { cout << "B::foo()" << endl; }
    virtual ~B() = default;
};
struct C : public B
{
    virtual void foo() const override { cout << "C::foo()" << endl; }
    virtual ~C() = default;
};

struct D
{
    void foo() const { cout << "D::foo()" << endl; }
};

template <typename T>
void sayFoo(T &t)
{
    static_assert(!std::is_abstract<T>(), "T cannot be abstract");
    static_assert(std::is_base_of<A, T>(), "T is not derived from A");

    t.foo();
}


int main()
{
    RandomUtil::randomize();
    assert(RandomUtil::nextInt(1, 100) < 98); // true most of the time

    static_assert(true, "true is not true");
    static_assert(sizeof(size_t) == 8, "Not a 64bit machine");

    //    If you uncomment this, you'll get a compilation error:
    //    static_assert(sizeof(size_t) == 4, "Not a 32bit machine")
    
    long double ld{ 1.0L };  // I don't use auto so that it's clear what I'm doing
    short d{ 1 };
    cout << compare(d, ld) << endl;
    cout << compare(ld, d) << endl;

    // cout << compare("cucu", "bau") << endl;  // error C2338: Not arithmetic type

    try {
        cout << factorial(-100) << endl;  // runtime error handling
    } catch (std::invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
    cout << factorial(RandomUtil::nextInt(1, 8)) << endl;

    // line below does not compile:
    // cout << factorial("alabala") << endl;

    A a{};
    B b{};
    C c{};
    D _d{};
    sayFoo(a);
    sayFoo(b);
    sayFoo(c);
    auto val{ 10 };
    sayFoo(val);    // error C2338: T is not derived from A
    sayFoo(_d);     // error C2338: T is not derived from A

    getchar();
    return 0;
}
