#include <iostream>

using namespace std;


/**
 * In a function declaration that uses the trailing return type syntax,
 * the keyword auto does not perform automatic type detection
 */

template <class T, class U>
auto add(T t, U u) -> decltype(t + u) // the return type is the type of operator+(T, U)
{
    return t + u;
}


auto get_fun(int arg) -> double(*)(double) // same as: double (*get_fun(int))(double)
{
    switch (arg) {
    case 1: return std::fabs;
    case 2: return std::sin;
    default: return std::cos;
    }
}


int main()
{
    string value;
    decltype(value) name{ "Ion" };

    cout << "Type of value is '" << typeid(value).name() << "'" << endl;

    cout << get_fun(2)(90.0) << endl;

    auto a = 1 + 2;
    std::cout << "type of a: " << typeid(a).name() << '\n';
    auto b = add(1, 1.2);
    std::cout << "type of b: " << typeid(b).name() << '\n';
    auto c = {1, 2};
    std::cout << "type of c: " << typeid(c).name() << '\n';

    auto my_lambda = [](int x) { return x + 3; };
    std::cout << "my_lambda: " << my_lambda(5) << '\n';

    auto my_fun = get_fun(2);
    std::cout << "type of my_fun: " << typeid(my_fun).name() << '\n';
    std::cout << "my_fun: " << my_fun(3) << '\n';

    getchar();
    return 0;
}
