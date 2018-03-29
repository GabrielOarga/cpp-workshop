#include <iostream>
using namespace std;


void do_something(void (*operation)())
{
    operation();
}


template<typename T>
void do_something(T t, int a, int b)
{
	cout << "Do something generic" << endl;
	t(a, b);
}

int main()
{
    []() {};


    auto lambda = []() { cout << "Simple lambda example" << endl; };

    lambda();

    // we can call lambda directly, anonymously:
    []() { cout << "Directly call lambda expression" << endl; }();

    []() {return 1; };

    // the usual scenario: pass lambdas as parameters to functions:
    auto print = []() { cout << "Another lambda" << endl; };
    do_something(print);

	int c = 10;
	auto lambda_capture = [c](int a, int b) { cout << "Context: " << c << "; variables: " << a << ", " << b << endl; };
	do_something(lambda_capture, 10, 20);
	 
    getchar();
    return 0;
}
