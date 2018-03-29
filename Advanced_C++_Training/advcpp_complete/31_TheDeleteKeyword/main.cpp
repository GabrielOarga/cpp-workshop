#include <iostream>
#include <vector>

using namespace std;


class Empty
{
};


// this "empty" class is equivalent to the following:

class NotEmpty
{
public:
    NotEmpty() = default;

    NotEmpty(const NotEmpty& another) = default;

    NotEmpty& operator=(const NotEmpty& another) = default;

    virtual void foo() { cout << "NotEmtpy" << endl; }

protected:
    ~NotEmpty() = default;
};

// so the compiler writes these four public functions for us
// default is used to explicitly add default functions to a class
// delete, besides memory de-allocation, has the role of explicitly
// muting functions: either default functions which the compiler writes
// for us, or other functions


class T : protected NotEmpty
{
public:
    virtual ~T() {}

    virtual void foo2() = delete;
};


// so the compiler writes these four public functions for us
// default is used to explicitly add default functions to a class
// delete, besides memory de-allocation, has the role of explicitly
// muting functions: either default functions which the compiler writes
// for us, or other functions

class A
{
public:
    A() {}

    A(const A& o) = delete;

    A& operator=(const A& o) = delete;
};


int main()
{
    A a1, a2, a3;
    // A a4 = a2;  // this line doesn't compile (copy constructor is deleted)
    A a5;
    // a5 = a1;    // this line also doesn't compile (assignment operator is deleted)

    // this also doesn't compile, because inserting in a vector implies calling the copy constructor
    // vector<A> aaa{a1, a2, a3};

    getchar();
    return 0;
}
