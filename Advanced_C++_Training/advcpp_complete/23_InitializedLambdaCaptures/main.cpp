#include <iostream>
#include <memory>

using namespace std;


int main()
{
    // C++11 lambda functions capture variables declared in their outer scope by value-copy or by reference
    // => value members cannot be move-only types!!
    // C++14 allows captured variables to be initialized:
	int value = 10;
    auto pwr2 = [value = 3]() { return value * value; };

    cout << "pwr2 = " << pwr2() << endl;

    // now let's see how lambda can capture a unique pointer:
	shared_ptr<int>outer_int;
    auto inner_int = outer_int = make_shared<int>(2);
 
    // now we can move inner_int inside the lambda:
    auto pwr3 = [val = std::move(inner_int)]() { *val = *val * *val * *val; return val; };

    cout << "pwr3: inner_int = " << *pwr3() << endl;
    cout << "pwr3: inner_int = " << *pwr3() << endl;
    cout << "pwr3: inner_int = " << *pwr3() << endl;

    cout << "outer_int(" << outer_int.get() << ") = " << *outer_int << endl;

    // along the way we didn't copy anything, we initialized value with the same myint
    // and also changed value == myint along multiple lambda calls
    // this is only possible in C++14

    getchar();
    return 0;
}
