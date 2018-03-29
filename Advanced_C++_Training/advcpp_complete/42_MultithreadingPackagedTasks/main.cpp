#include <iostream>
#include <string>
#include <future>

using namespace std;


/**
 * Effective Modern C++ - item 35: prefer tasks to threads
 * std::packaged_task is a wrapper for a functor: it can wrap
 * any Callable (function, functor, lambda, std::bind)
 *
 * We pass parameters to it
 * and the packaged_task will bind these to its constructor AND it returns
 * a std::future; calling the task() (operator()) means starting a thread (maybe)
 * which will set the value (promise) that we expect (in the future)
 */

void test_basic_packaged_task()
{
    auto task{ packaged_task<int(int)>{ [](int value) { return value * value; } } };
    auto future = task.get_future();

    // just a paranthesis: std::invoke
    invoke([]() { cout << "std::invoke() usage test" << endl; });

    task(100);
    cout << future.get() << endl;

    // No need to create a thread (manually)
    // => no need to join() on that thread
    // The code simply looks better.
}


// a dummy function used to create a std::bind and pass to a packaged_task
void display(int a, int b) { cout << "displaying " << a << " and " << b << endl; }


void test_bind_packaged_task()
{
    using namespace placeholders;  // std::placeholders, but we're already using namespace std
    // we can create a packaged_task out of a std::bind object (remember std::bind)
    auto display10 = bind(display, 10, _1);
    auto task = packaged_task<void(int)>{display10};
    auto future = task.get_future();
    task(100);  // this will get placed in the _1 placeholder of the bind object
    future.get();
}


int main()
{
    test_basic_packaged_task();
    test_bind_packaged_task();

    getchar();
    return 0;
}
