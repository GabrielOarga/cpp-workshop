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


int main()
{
    RandomUtil::randomize();
    assert(RandomUtil::nextInt(1, 10) < 8);  // dynamic assert

    
    getchar();
    return 0;
}
