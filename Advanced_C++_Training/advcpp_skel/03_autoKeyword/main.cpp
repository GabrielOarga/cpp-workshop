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
}


int main()
{
    test_cpp03();
    test_cpp11();

    getchar();
    return 0;
}
