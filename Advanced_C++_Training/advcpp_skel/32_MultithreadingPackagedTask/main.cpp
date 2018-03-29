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
}



void test_bind_packaged_task()
{
}


int main()
{
    test_basic_packaged_task();
    test_bind_packaged_task();

    getchar();
    return 0;
}
