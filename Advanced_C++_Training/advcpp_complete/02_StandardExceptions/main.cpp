#include <iostream>
#include <memory>
#include <functional>
using namespace std;


class Device
{
    // Empty
};


class Settings
{
private:
    shared_ptr<Device> device;

public:
    explicit Settings(weak_ptr<Device> device) :
        device(device)
    {
        // Empty
    }
};


void test_bad_weak_ptr()
{
    cout << "[TEST] bad_weak_ptr" << endl;
    try {
        shared_ptr<Device> d{new Device};
        weak_ptr<Device> backup(d);
        d.reset();
        Settings s1{backup};
    } catch (const bad_weak_ptr& e) {
        cerr << "Caught " << e.what() << endl;
    }
    cout << "[TEST] bad_weak_ptr complete" << endl;
}


void test_bad_function_call()
{
    cout << "[TEST] bad function call" << endl;
    // usually thrown when invoking operator() on a function object
    // if the function wrapper returns null
    function<int()> foo = nullptr;
    try {
        foo();
    } catch (std::bad_function_call& e) {
        cerr << "Caught " << e.what() << endl;
    }
    cout << "[TEST] bad function call complete" << endl;
}


int main()
{
    test_bad_weak_ptr();
    test_bad_function_call();

    getchar();
    return 0;
}
