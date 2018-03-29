#include <iostream>
#include <string>

using namespace std;


struct A
{
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
};


A getA()
{
    return A();
}


void basics()
{
    // value is lValue, 7 is rValue
    auto value{ 10 };
    // since the beginning, C++ made a distinction between lValues and rValues

    // C++11 changes / enhances the definition of lValue and rValue for reasons
    // that will soon be discovered

    // in C++11 an lValue is *basically* anything that you can take the address of:
    int* p_value = &value;          // this compiles => value is an lValue
//    int* p_expression = &10;     // this obviously doesn't compile => 7 is an rValue

    A a = getA();
    A *p_a = &a;    // a is an lValue
                    // getA() is an rValue: you can't take the address of it
                    // rValues are often temporary values (return objects, etc.)
    // with lValue references we can implement all sort of operations:
}


void test_operators()
{
    auto value{ 10 };
    int *p_value = &value;
    int *p_value2 = &++value;       // this works fine (++value is an lValue) => 11
    cout << *p_value2 << endl;

    // int *p_value3 = &value++;       // this doesn't compile! Why?
    // because value before incrementation is a temporary variable <=> rValue
    // You can't take the address of a temporary value

    // Rule:
    auto another = value + 10;      // value + 10 is an rValue, even if value is an lValue!
}


int main()
{
    basics();
    test_operators();

    getchar();
    return 0;
}
