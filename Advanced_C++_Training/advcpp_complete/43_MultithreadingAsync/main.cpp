#include <iostream>
#include <future>

using namespace std;
using namespace literals;  // std::literals


void f() { cout << "f() is executing" << endl; }


int g(int a, int b) { cout << "g() is executing" << endl; return a * b; }


void test_simple_async()
{
    // test 1
    auto future{ std::async(f) };
    future.get();

    // test 2
    async([]() { cout << "Inline async execution" << endl; }).get();
}


void test_launch_async_policy()
{
    // test 1
    auto future { async(launch::async | launch::deferred, g, 10, 20) };
    this_thread::sleep_for(100ms);
    cout << "Async with default launch policy: " << future.get() << endl;

    // This default policy allows async to run EITHER (because of |)
    // - synchronously  (same thread) or
    // - asynchronously (in another thread)
    // It is up to the scheduler to decide what's best, at runtime

    // launch::deferred means that the execution will happen only when get() or wait()
    // is called on the future returned by async => the execution might not happen => flexibility

    // test 2: async execution: always launch using a thread
    auto future2{ async(launch::async, g, 20, 30) };
    cout << "Async with launch::async policy: " << future2.get() << endl;

    // test 3: deferred execution: execute only on get() <=> lazy execution
    cout << this_thread::get_id() << ": Testing deferred execution ..." << endl;
    auto future3{ async(launch::deferred, []() { cout << this_thread::get_id() << "deferred execution" << endl; }) };
    this_thread::sleep_for(4s);
    future3.get();

    // OBS:
    // get() is the synchronization point
    // depending on launch policy, we may have:
    // - immediate fire + eventual sync
    // - deferred fire + eventual ... fire AND sync (two-in-one, triggered via get())
    // - in the second case the thread management components from the std lib will
    //   decide whether the execution will happen in a new thread or in the same thread
}


void test_async_may_not_run()
{
    // test 1: may run forever, because calling wait_for() on an async
    // causes the launch policy to be set to deferred
    // => in a heavy load the main thread may stay in the loop a very long time
    auto future = async([]()
    {
        this_thread::sleep_for(200ms);
        cout << this_thread::get_id() << ": async is running" << endl;
    });

    // with default policy it is possible that async doesn't finish => loop forever
    while (future.wait_for(10ms) != std::future_status::ready) {
        cout << this_thread::get_id() << ": async is not yet ready" << endl;
    }

    // test 2: here there is no risk of not running
    auto future2 = async(std::launch::async, []()
    {
        this_thread::sleep_for(200ms);
        cout << this_thread::get_id() << ": async is running" << endl;
    });
    // Conclusion: always use launch::async when calling wait_for() or wait_until() on a task
}


int main()
{
    test_simple_async();
    test_launch_async_policy();
    test_async_may_not_run();

    getchar();
    return 0;
}
