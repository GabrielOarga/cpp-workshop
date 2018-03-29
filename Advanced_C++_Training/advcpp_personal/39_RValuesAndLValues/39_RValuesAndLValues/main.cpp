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
    auto value{ 7 };
    int* pv = &value;
//    int* p7 = &7; //not ok
    
    A a = getA(); //getA(0 saves into temp value, that cannot be assigned via #1
    A* pa = &a;
//    A* pga = &getA(); //#1
}


void test_operators()
{
    auto value{ 10 };
    int* pv1 = &value;
    int* pv2 = &++value;
    
    cout << pv2 << endl;
    
//    int* pv3 = &value++; // this also creates a temp value that cannot be assigned
}

int main()
{
    basics();
    test_operators();

    getchar();
    return 0;
}
