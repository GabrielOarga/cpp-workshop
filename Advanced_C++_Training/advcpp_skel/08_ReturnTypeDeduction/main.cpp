#include <iostream>
#include <typeinfo>

using namespace std;


/**
 * In a function declaration that uses the trailing return type syntax,
 * the keyword auto does not perform automatic type detection
 */

template <class T, class U>
auto add(T t, U u) {}


auto get_fun(int arg) {}


int main()
{


    getchar();
    return 0;
}
