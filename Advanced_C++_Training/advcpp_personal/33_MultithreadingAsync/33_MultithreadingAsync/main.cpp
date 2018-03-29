#include <iostream>
#include <thread>
#include <future>

using namespace std;

void f() { cout << "f() is executing" << endl; }


int g(int a, int b)
{
    cout << this_thread::get_id() << ": g() is executing" << endl;
    return a * b;
}


void test_simple_async()
{
    auto future{std::async(f)};
    future.get();
    
    async( []() { cout << "Inline async" << endl; }).get();
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
