#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <exception>

using namespace std;


/**
* Here we use the thread-centric aproach. Async comes in the next project.
*/

/**
* The future - promise paradigm
* - future: holds a handle on a variable whose value will be set in the future, asynchronously
* - promise: a handle which enables setting the value of a future in an async manner
*
* Futures and promises are managed for us: they share a **synchronized** memory region
*
* "I promise I will set you": a promise acts like an async setter for a variable held by a future
* the promise will set the value in one thread, while the future will get it from another thread
*/

void test_simple_promise_future()
{
}


/**
* A promise can return a value or throw an exception
* Remember how we dealt with exceptions in the previous example.
* On a promise you can set_exception(exception_ptr) and try/catch
* in the main thread when calling future::get()
*/
void test_promise_exception()
{
}


void test_fork_more_than_once()  // "fork" is not the best name :)
{
}


int main()
{
    test_simple_promise_future();
    test_promise_exception();
    test_fork_more_than_once();

    getchar();
    return 0;
}
