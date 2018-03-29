#include <iostream>
#include <functional>

using namespace std;
using namespace placeholders;  // used for _i placeholders

/**
 * std::bind() is C++'s way of implementing partial functions
 * We can create partial functions out of existing functions and
 * 
 */


long prod(int x, int y, int z)
{
    cout << x << " * " << y << " * " << z << " = ";
    return x * y * z;
}


long run(function<long(int, int)> func)
{
    return func(10, 20);
}


// we can also bind to a method of a class
class Test
{
public:
    Test(int x, int y, int z) : m_x(x), m_y(y), m_z(z) {}

    int add(int a, int b) const
    {
        cout << a << " + " << b << " + " << m_x << " + " << m_y << " + " << m_z << " = ";
        return a + b + m_x + m_y + m_z;
    }

private:
    int m_x;
    int m_y;
    int m_z;
};

int main()
{
    auto pr1 = bind(prod, 10, 2, 3);
    cout << pr1() << endl;

    auto pr2 = bind(prod, _1, 2, 3);
    cout << pr2(20) << endl;
    cout << pr2(100) << endl;

    // the number in the bind placeholder represents the order in the called function (add)
    // => we can have something like this:
    auto pr3 = bind(prod, _2, _1, 100);
    cout << pr3(10, 15) << endl;  // 10 is _2, and 15 is _1 => x = 15 and y = 10!

    auto pr4 = bind(prod, _2, 100, _1);
    cout << pr4(10, 15) << endl;  // x is 15 and y is 100

//      RULE: bind() parameters correspond to target function's parameters
//      placeholder indexes can mix the arguments of the partial function
//      you usually won't want to change the order

    // we can send a partial function as function argument to another function:
    cout << run(pr4) << endl;

    // we can also bind to a non-static method inside a class / struct
    Test t(10, 20, 30);
    auto test1 = bind(&Test::add, t, 10, 20);
    cout << test1(100, 200) << endl;

    getchar();
    return 0;
}
