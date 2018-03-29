#include <iostream>
#include <string>
#include <atomic>

using namespace std;

/**
 * In the following projects we will talk about perfect forwarding,
 * but first we'll have a look at casts in C++
 */

class Animal
{
public:
    Animal() : Animal("") {}
    explicit Animal(string name) : name(name) {}
    virtual ~Animal() {}
    virtual void speak() const {}  // we don't make it pure virtual
protected:
    string name;
};


void test_static_cast()
{
}


void test_dynamic_cast()
{
}


void test_reinterpret_cast()
{
}


int main()
{
    test_static_cast();
    test_dynamic_cast();
    test_reinterpret_cast();

    getchar();
    return 0;
}
