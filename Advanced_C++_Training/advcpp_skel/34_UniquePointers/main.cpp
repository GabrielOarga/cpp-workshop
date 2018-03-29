#include <iostream>
#include <string>
#include <memory>  // we need to include this to work with smart pointers

using namespace std;

/**
* unique_ptr is a smart pointer that owns and manages another object through a pointer
* and disposes of that object when the unique_ptr goes out of scope.
* The object is disposed of using the associated deleter when either of the following happens:
* <ul>
* <li> the managing unique_ptr object is destroyed</li>
* <li> the managing unique_ptr object is assigned another pointer via operator= or reset() </li>
* </ul>
*/

// we create a small class and cout the most important moments in object lifecycle
struct Greet
{
    explicit Greet(string name) : name(name) { cout << "Constructor: " << name << endl; }
    void greet() const { cout << "Hello, " << name << "!" << endl; }
    ~Greet() { cout << "Destructor: " << name << endl; }
    string name;
};


void test_make_unique()
{
    // in C++14 make_unique was added:
    // it creates a new object and wraps it in a unique_ptr
    auto paul = make_unique<Greet>("Paul");
    paul->greet();
}


void test_basic_usage()
{
    // unique_ptr is a template class from <memory>
    unique_ptr<int> iptr{ new int(10) };  // we don't need a star * to say that it's a pointer
    *iptr = 7;
    cout << *iptr << endl;

    // let's test with our class:
    unique_ptr<Greet> greet_george{ new Greet("George") };
    greet_george->greet();

    // now look what happens:
    greet_george = unique_ptr<Greet>{ new Greet("Ion") };
    greet_george->greet();
    // a new unique_ptr was created for Ion; then, when operator= was called on greet_george,
    // the old object was automatically deleted (automatic memory management)

    // we can obtain the raw pointer out of the unique_ptr
    cout << "Test raw pointer: ";
    Greet* pGeorge = greet_george.get();
    pGeorge->greet();

    cout << "Test move ownership: ";
    // unique means that object *ownership* is unique, cannot be shared
    unique_ptr<Greet> greet_ion = std::move(greet_george);  // now greet_ion owns instance Greet("Ion")
    greet_ion->greet();

    // the following line give runtime error (access violation):
    // greet_george->greet();  // runtime error, access violation
    pGeorge->greet();

    // before going out of scope, the new object will also be deleted
}


int main()
{
    test_basic_usage();
    test_make_unique();

    cout << "Program finished" << endl;
    getchar();
    return 0;
}
