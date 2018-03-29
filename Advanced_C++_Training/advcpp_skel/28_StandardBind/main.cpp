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


int main()
{

    getchar();
    return 0;
}
