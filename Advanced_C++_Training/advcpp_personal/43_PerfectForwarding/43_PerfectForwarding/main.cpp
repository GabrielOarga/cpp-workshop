#include <iostream>

using namespace std;

struct Test
{
    Test() { cout << "Test()" << endl; }
    ~Test() { cout << "~Test()" << endl; }
    Test(const Test& other) = default;
    Test(Test&& other) noexcept { cout << "Test() being moved" << endl; }
    
//    Test operator==(Test& const other) {};
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

template<typename T>
void call(T &&t)
{
    foo(t);
}

template<typename T>
void call2(T &&t)
{
    foo(static_cast<T&&>(t));
}

template<typename T>
void call3(T &&t)
{
    foo((T&&)t);
}

template<typename T>
void call4(T &&t)
{
    foo(std::forward<T>(t));
}

template<typename T>
void swap2(T& a, T& b) noexcept
{
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}


int main()
{
    auto&& t = getTest();
    foo(t);
    foo(getTest());
    
    call(getTest());
    call2(getTest());
    call3(getTest());
    call4(getTest());
    
    Test t1{};
    Test t2{};
    
    swap2<Test>(t1, t2);
    


    getchar();
    return 0;
}
