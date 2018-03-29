#include <iostream>
#include <cassert>
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

template <typename T>
T factorial(T in)
{
    static_assert(std::is_integral<T>::value, "Nubmer is not integral");
    
    if (in < 0)
    {
        throw std::invalid_argument("Invalid Argument");
    }
    
    T res = 1;
    while (in > 0) {
        res = res * in;
        in--;
    }
    return res;
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
    static_assert(std::is_base_of<A, T>(), "T is not a derived of A");
    t.foo();
}

int main()
{
    RandomUtil::randomize();
    //assert(RandomUtil::nextInt(1, 10) < 8);  // dynamic assert

    static_assert(true, "true is not true");
    static_assert(sizeof(size_t) == 8, "Not on a 64b system");
    
    A a{};
    B b{};
    C c{};
    D d{};
    
    sayFoo(a);
    sayFoo(b);
    sayFoo(c);
    //sayFoo(d);
    
    cout << factorial<int>(10) << endl;
    
    getchar();
    return 0;
}
