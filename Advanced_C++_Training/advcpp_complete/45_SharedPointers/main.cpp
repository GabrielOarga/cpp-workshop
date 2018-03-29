#include <iostream>
#include <memory>
#include <string>

using namespace std;

/**
 * Shared pointers are similar to unique pointers, except:
 * <ul>
 * <li>they allow multiple shared_ptr objects to share ownership of the same object</li>
 * <li>they will call the Deleter when all shared pointers are out of scope</li>
 * </ul>
 * Individual shared_ptr-s may go out of scope, but if there is at least one shared_ptr
 * which wraps its wrapped object, then that object will not get deleted
 */

// we create a small class and cout the most important moments in object lifecycle
struct Greet
{
    explicit Greet(string name) : name(name) { cout << "Constructor: " << name << endl; }
    void greet() const { cout << "Hello, " << name << "!" << endl; }
    ~Greet() { cout << "Destructor: " << name << endl; }
    string name;
};


void foo(shared_ptr<Greet>& greet)  // if we pass by value, the number of pointers will increment
{
    auto copy = greet;
    copy->greet();
    cout << "Nr of pointers: " << copy.use_count() << endl;
}


void test_basic_usage()
{
    auto greet_ion{ make_shared<Greet>("Ion" )};
    greet_ion->greet();
    cout << "Nr of pointers: " << greet_ion.use_count() << endl;

    auto greet_ion2{ greet_ion };
    greet_ion2->greet();
    cout << "Nr of pointers: " << greet_ion.use_count() << endl;

    foo(greet_ion);
    cout << "Nr of pointers: " << greet_ion.use_count() << endl;

    // swap usage
    auto greet_grigore{ make_shared<Greet>("Grigore") };
    greet_grigore.swap(greet_ion);
    greet_ion->greet();
}


int main()
{
    test_basic_usage();

    // A shared_ptr may also own no objects, in which case it is called empty
    // an empty shared_ptr may have a non-null stored pointer if the aliasing
    // constructor was used to create it

    // Important: all shared_ptr member functions are thread-safe
    // (including copy constructor and copy assignment operators)
    // you can share ownership of the same object from multiple threads
    getchar();
    return 0;
}
