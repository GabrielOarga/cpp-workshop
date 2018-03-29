#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <mutex>

using namespace std;

/**
* weak_ptr is a smart pointer that holds a weak reference to an object.
* It cannot access the object by itself.
* when an object needs to be accessed only if it exists, and it may be
* deleted at any time by someone else, std::weak_ptr is used to track the
* object, and it is converted to std::shared_ptr to assume temporary
* ownership. If the original std::shared_ptr is destroyed at this time,
* the object's lifetime is extended until the temporary std::shared_ptr
* is destroyed as well
*/


void foo(weak_ptr<int>& wp)
{
    // cout << *wp << endl;  // this doesn't work! You cannot use a weak_ptr directly
    if (auto shared_copy = wp.lock()) {  // convert to shared_ptr
        cout << *shared_copy << endl;    // if object still exists => conversion succeeds
    }
    else {
        cout << "The object doesn't exist (anymore)" << endl;
    }
}


void test_circular_references()
{
}


void circular_references_eliminated()
{
}


// A common use for weak_ptr: simple cache implementations
template<typename T>
shared_ptr<T> get_thing(int id)
{
    return nullptr;
}


void test_cache()
{
    cout << *get_thing<int>(1) << endl;
    cout << *get_thing<int>(2) << endl;
    cout << *get_thing<int>(3) << endl;
    // now cache should be full
    cout << *get_thing<int>(1) << endl;
    cout << *get_thing<int>(2) << endl;

    // in reality you'd have another function which generated the expensive objects
}


int main()
{
    // Important: weak_ptr is used to break circular references of shared_ptr
    test_circular_references();
    circular_references_eliminated();
    test_cache();

    getchar();
    return 0;
}
