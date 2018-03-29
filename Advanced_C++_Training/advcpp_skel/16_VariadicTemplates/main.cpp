#include <iostream>
#include <array>
#include <vector>

using namespace std;

/**
 * A template parameter pack is a template parameter that accepts
 * zero or more template arguments (non-types, types, or templates).
 * A function parameter pack is a function parameter that accepts
 * zero or more function arguments.
 *
 * A template with at least one parameter pack is called a variadic template.
 */

template <typename T>
auto increment(T& value)
{
    ++value; // btw, try with value++ and see what you get
    return; // we're just helping the compiler (should work also without)
}


void increment_test()
{
    auto i = 1;
    auto d = 2.3;
    auto f = 3.6f;
    increment<int>(i); // <int> is not needed actually
    increment(d);
    increment(f);
    cout << i << " " << d << " " << f << endl;
}


void process1_test()
{
    cout << "process1 test:" << endl;
    auto i = 1;
    auto d = 2.3;
    auto f = 3.6f;
    auto g = 100.0;
    auto h = 10.2;
    auto j = -29;

    cout << i << ", " << d << ", " << f << ", " << g << ", " << h << ", " << j;
}



void process2_test()
{
    cout << "process2 test:" << endl;
    auto i = 1;
    auto d = 2.3;
    auto f = 3.6f;
    auto g = 100.0;
    auto h = 10.2;
    auto j = -29;
}


int main()
{
    increment_test();
    process1_test();
    process2_test();

    getchar();
    return 0;
}
