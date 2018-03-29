#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;


void test_cpp03()
{
    // C++03 we wrote something like this:
    int a = 100;  // equivalent to auto int a = 100; (not supported in modern compilers)

    // auto was inherited from C and never used (basically); other specifiers are:
    // - register: a hint to compiler that the local variable should be stored in a register
    // - static: the variable never dies during program lifecycle => value remains the same
    //           between succesive calls
    // - extern: the extern variable cannot be initialized, instead it points to a global
    //           variable defined in another source file

    vector<int> numbers;
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(40);

    for (vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it)
        cout << *it << " ";
    cout << endl;
    // imagine how some interfaces looked like in header files inside a deeply nested class!
}


void test_cpp11()
{
    vector<int> numbers{ 10, 20, 30, 40 };

    // from c++11 auto was given a better role: type inference
	for (auto it{ numbers.begin() }; it != numbers.end(); ++it)
        cout << *it << " ";
    cout << endl;

    auto i = 100u;
    const auto PI = acos(-1);
    auto val = pow(sin(PI / 2), 2) + cos(PI / 4);
    cout << scientific << val << endl;

    // what about pointers:
    auto *pInt = new int[5];
    cout << pInt[1] << endl;
    delete[] pInt;

	pInt = new int[5]{};        // with {} we initialize members to 0
    cout << pInt[1] << endl;
    delete[] pInt;

    auto pInt2 = new int[5]{};  // type inference works well with both cases; you usually use auto for the "whole" type
    cout << pInt2[1] << endl;
    delete[] pInt2;

    auto j = 10, *pJ = &j;      // but sometimes it makes sense to use auto only for the type (without *)

	auto n2 = { 1, 2, 3 };
	cout << typeid(n2).name() << endl;

}


int main()
{
    test_cpp03();
    test_cpp11();

    getchar();
    return 0;
}
