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
    cout << "Test simple promise / future (begin)" << endl;
    auto promise{ std::promise<int>{} };
    auto future{ promise.get_future() };

    thread worker{ [&promise]()
    {
        using namespace std::literals;
        this_thread::sleep_for(2s);
        promise.set_value(100);
    } };

    cout << future.get() << endl;
    // Rule: it is illegal to get() the value more than once!
    worker.join();  // you need to join(), even if set_value_at_thread_exit()
    cout << "Test simple promise / future (end)" << endl << endl;
}


/**
 * A promise can return a value or throw an exception
 * Remember how we dealt with exceptions in the previous example.
 * On a promise you can set_exception(exception_ptr) and try/catch
 * in the main thread when calling future::get()
 */
void test_promise_exception()
{
    cout << "Test promise exception (begin)" << endl;
    auto promise = std::promise<string>{};
    auto future = promise.get_future();

    class MyException : public exception
    {
    public:
        explicit MyException(char const* const message) : message(message) {}
        char const* what() const noexcept override { return message.c_str(); }
    private:
        string message;
    };

    thread worker{[&promise]()
    {
        // other operations on pomise:
        // promise.set_value_at_thread_exit("cucu");
        try {
            throw MyException{"I cannot do what you want"};
        } catch (exception&) {
            exception_ptr e = current_exception();
            promise.set_exception(e);
            // promise.set_exception_at_thread_exit(e);
        }
    }};

    try {
        cout << future.get() << endl;
    } catch (MyException& e) {
        cerr << e.what() << endl;
    }

    worker.join();
    cout << "Test promise exception (end)" << endl << endl;
}


void test_fork_more_than_once()  // "fork" is not the best name, but you get the idea
{
    // Say you need the future value in more than one thread
    // remember: you cannot cal get() multiple times => how do you do that?
    // Answer: you share the future
    auto promise{ std::promise<int>{} };
    auto future{ promise.get_future() };
    auto cloned_future{ future.share() };
    cout << "Test shared future (begin)" << endl;
    thread worker{ [&promise]()
    {
        using namespace std::literals;
        promise.set_value_at_thread_exit(100);  // => sync happens at thread exit, not here
        this_thread::sleep_for(2s);
    } };
    using namespace std::this_thread;
    thread t1{ [cloned_future]() { cout << get_id() << ": " << cloned_future.get() << endl; } };
    thread t2{ [cloned_future]() { cout << get_id() << ": " << cloned_future.get() << endl; } };
    thread t3{ [cloned_future]() { cout << get_id() << ": " << cloned_future.get() << endl; } };

    cout << "Main thread (" << this_thread::get_id() << "): " << cloned_future.get() << endl;

    // if you're sharing you cannot call get on the original future
    // cout << "Main thread: " << future.get() << endl;
    t1.join(); t2.join(); t3.join();
    worker.join();
    cout << "Test shared future (end)" << endl << endl;
}


int main()
{
    test_simple_promise_future();
    test_promise_exception();
    test_fork_more_than_once();

    getchar();
    return 0;
}
