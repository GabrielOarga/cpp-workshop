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


// this is NECESSARY because we don't have a process1 with no params
// and the recursive template function will at some point invoke process1()
void process1() { }

template <typename T1, typename ... Ts>
void process1(T1& head, Ts& ... params)
{
    increment(head);
    process1(params...);    // template function recursive call
                            // this is recursive template instantiation
                            // this is the classic way of dealing with variadic templates
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

    process1(d, f);
    process1(i, d, f, g, h, j);
    cout << i << " " << d << " " << f << " " << g << " " << 
        h << " " << j << endl;
}


template <typename T>
int to_int(T& arg)
{
    return static_cast<int>(arg);
}


// in some examples we don't necessarily need to use recursive template instantiation
// We will notice that the code is smaller thus compiles faster with the following aproach:
template <typename ... Ts>
vector<int> process2(Ts& ... params)
{
    // use an initializer list to initialize the return value
    // all the to_int() calls will be expanded for each param
    return{to_int(params)...};
}


// Look how ugly the code below is
// It will take longer to compile and produce more functions
template <typename T, typename... Ts>
vector<int> process2_bad(T head, Ts& ... params)
{
    vector<int> vec;
    vec.push_back(increment(head));
    const auto rest = process2_bad(params...);
    vec.insert(vec.end(), rest.begin(), rest.end());
    return vec;
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
    auto result{ process2(i, d, f, g, h, j) };
    for (auto elem : result) cout << elem << endl;
}


int main()
{
    increment_test();
    process1_test();
    process2_test();

    getchar();
    return 0;
}
