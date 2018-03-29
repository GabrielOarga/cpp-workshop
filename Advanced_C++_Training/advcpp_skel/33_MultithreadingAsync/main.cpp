#include <iostream>
#include <future>

using namespace std;
using namespace literals;  // std::literals


void f() { cout << "f() is executing" << endl; }


int g(int a, int b)
{
    cout << this_thread::get_id() << ": g() is executing" << endl; return a * b;
}


void test_simple_async()
{
}


void test_launch_async_policy()
{
}


void test_async_may_not_run()
{
}


int main()
{
    test_simple_async();
    test_launch_async_policy();
    test_async_may_not_run();

    getchar();
    return 0;
}
