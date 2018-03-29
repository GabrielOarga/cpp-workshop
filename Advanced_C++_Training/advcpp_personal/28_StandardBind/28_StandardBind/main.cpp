#include <iostream>
#include <functional>

using namespace std;
using namespace placeholders;  // used for _i placeholders


/**
 * std::bind() is C++'s way of implementing partial functions
 */


long prod(int x, int y, int z)
{
    cout << x << " * " << y << " * " << z << " = ";
    return x * y * z;
}

class Test
{
public:
    Test(int x, int y, int z)
    : m_x(x)
    , m_y(y)
    , m_z(z)
    { }
    
    int add (int x, int y, int z)
    {
        int res = x + y + z;
        return res;
    }
    
private:
    int m_x;
    int m_y;
    int m_z;
};

long run(function<long(int, int)> f) //#1
{
    return f(10, 20);
}

int main()
{
    auto pr1 = bind(prod, 10, 5, 5);
    cout << pr1() << endl;
    
    auto pr2 = bind(prod, _1, 2, 3); // _1 is a palceholder, willr eq a paramater beeing passed
    cout << pr2(10) << endl; //the '10' will repalce the _
    
    auto pr3 = bind(prod, _2, _1, 50);
    cout << pr3(10, 15) << endl; // position coincides with the _number, as you can see in this example _2 <- 15, _1 <- 10
    
    cout << run(pr3) << "caca" << endl; //send function pr3, that needs two args, to the function that accepts a function as a param that takes two params @ #1
    
    auto pr4 = bind(prod, _2, 100, _1);
    cout
    << pr4(10, 20) << endl;
    
    Test t{ 1, 2, 3 };
    auto adder = bind (&Test::add, t, 10, 20 ,30); //Nice!
    auto sum{ adder() }; //Nice!
    
    cout << sum << endl; //Nice!

    getchar();
    return 0;
}
