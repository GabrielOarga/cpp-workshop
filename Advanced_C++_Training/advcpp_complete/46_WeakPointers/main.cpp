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
    } else {
        cout << "The object doesn't exist (anymore)" << endl;
    }
}


void test_circular_references()
{
    cout << "Test bad circular reference: begin (no message should be displayed)" << endl;
    struct B
    {
        std::shared_ptr<B> ptr;
        ~B() { cout << "B destructor" << endl; }
    };
    auto b1 = make_shared<B>();
    auto b2 = make_shared<B>();
    b1->ptr = b2;
    b2->ptr = b1;  // now you have a cyclic reference
    // ~B() will not be called here
    cout << "Test bad circular reference: end" << endl;
}


void circular_references_eliminated()
{
    cout << "Test circular reference elimination: begin" << endl;
    struct A
    {
        std::weak_ptr<A> ptr;
        ~A() { cout << "A destructor" << endl; }
    };
    auto a1 = make_shared<A>();
    auto a2 = make_shared<A>();
    a1->ptr = weak_ptr<A>(a2);
    a2->ptr = weak_ptr<A>(a1);
    // ~A() should be called now
}


// A common use for weak_ptr: simple cache implementations
template<typename T>
shared_ptr<T> get_thing(int id)
{
    static map<int, weak_ptr<T>> cache; // C++11 guarantees static variables are initialized thread-safely
    static mutex m;
    // let's define some dummy values (owners of the pointers)
    static shared_ptr<T> possible_values[3]{
        make_shared<T>(1),
        make_shared<T>(2),
        make_shared<T>(3)
    };
    static auto i = 0;

    lock_guard<mutex> locker(m);
    auto shared_p = cache[id].lock();   // if id is not there operator[] will make one for you
    if (!shared_p) {                    // lock() is thread-safe and guarantees the object will live until shared_p is out of scope!
        cout << "Cache miss" << endl;
        auto value = possible_values[i++];
        i = i % 3;
        cache[id] = value;
        shared_p = value;
    } else {
        cout << "Cache hit" << endl;
    }
    return shared_p;
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
    weak_ptr<int> wp;
    auto sp = make_shared<int>(100);
    wp = sp;
    foo(wp);
    sp.reset();
    foo(wp);

    // Important: weak_ptr is used to break circular references of shared_ptr
    test_circular_references();
    circular_references_eliminated();
    test_cache();

    getchar();
    return 0;
}
