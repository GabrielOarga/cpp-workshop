#include <iostream>
#include <string>
using namespace std;


template <typename T>
void print(T arg)
{
    cout << arg << endl;
}


void print(int n)
{
    cout << "Specific function: " << n << endl;
}


template <class T>
void show()
{
    cout << "Showing '" << T() << "'" << endl;
}


int main()
{
    print<int>(10);
    print<char*>("Hello template");
    print("Hello world");

    // watch type inference below:
    print(10); // calls specific function
    print<int>(10); // calls template function
    print<>(10); // calls template function

    // error: indeed, no argument, but the type cannot be inferred
    // show();
    // show<>();

    show<int>();
    show<string>();

    getchar();
    return 0;
}
