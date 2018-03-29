#include <iostream>

using namespace std;

struct Test
{
};

void foo(Test& test)
{
    cout << "foo() - lValue" << endl;
}


void foo(Test&& test)
{
    cout << "foo() - rValue" << endl;
}


Test getTest()
{
    return Test();
}


int main()
{
    auto&& t = getTest();
    foo(t);
    foo(getTest());

    getchar();
    return 0;
}
