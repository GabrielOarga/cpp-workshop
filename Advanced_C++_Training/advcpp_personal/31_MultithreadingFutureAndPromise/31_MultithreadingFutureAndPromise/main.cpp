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
    auto promise{ std::promise<int> {} };
    auto future{ promise.get_future() };
    
    thread worker{ [&promise]() {
        this_thread::sleep_for(chrono::seconds(6));
        promise.set_value(100);
    }};
    
    cout << future.get() << endl;
    worker.join();
}


/**
* A promise can return a value or throw an exception
* Remember how we dealt with exceptions in the previous example.
* On a promise you can set_exception(exception_ptr) and try/catch
* in the main thread when calling future::get()
*/
void test_promise_exception()
{
    auto promise{ std::promise<string>{} };
    auto future{ promise.get_future() };
    
    thread worker{ [&promise]() {
        try {
            throw string("Cucu bau!");
        }
        catch (string&) {
            promise.set_exception(current_exception());
        }
    } };
    
    try {
        cout << future.get() << endl;
    }
    catch (string& s) {
        cerr << "Something went wrong: " << s << endl;
    }
    
    worker.join();
}


void test_fork_more_than_once()  // "fork" is not the best name :)
{
    auto promise{ std::promise<int>{} };
    auto future{ promise.get_future() };
    auto cloned_future{ future.share() };
    
    thread w{ [&promise]() {
        promise.set_value_at_thread_exit(200);
        this_thread::sleep_for(chrono::seconds(5));
    } };
    
    thread t1{ [cloned_future]() { cout << cloned_future.get() << endl; } };
    thread t2{ [cloned_future]() { cout << cloned_future.get() << endl; } };
    thread t3{ [cloned_future]() { cout << cloned_future.get() << endl; } };
    
    cout << "main thread: " << cloned_future.get() << endl;
    
    t1.join(); t2.join(); t3.join();
    w.join();
}


int main()
{
    test_simple_promise_future();
    test_promise_exception();
    test_fork_more_than_once();

    getchar();
    return 0;
}
