#include <iostream>
#include <string>
#include <vector>

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
}


void test_operators()
{
}


int main()
{
    basics();
    test_operators();

    getchar();
    return 0;
}
