#include <iostream>
#include <typeinfo>
#include <cmath>

using namespace std;


/**
 * In a function declaration that uses the trailing return type syntax,
 * the keyword auto does not perform automatic type detection
 */

template <class T, class U>
auto add(T t, U u) -> decltype(t + u)
{
    return t + u;
}

auto get_fun(int arg) -> double(*)(double)
{
    static auto c = [](double b) {return b; };
    switch(arg) {
        case 1: return std::fabs;
        case 2: return std::sin;
        case 3: return std::cos;
        case 4: return [](double c) { return c * c; };
        default: return std::cos;
    }
}


int main()
{
    cout << get_fun(2)(90.0) << endl;
    auto result = add(1, 3.7);
    cout << result << endl;
    

    getchar();
    return 0;
}
