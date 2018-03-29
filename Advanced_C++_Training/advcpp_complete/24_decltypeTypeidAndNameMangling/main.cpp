#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;


int main()
{
    string value;
    decltype(value) name = "Ghita";  // <=> string name = "Bob";

    cout << "Type of value is '" << typeid(value).name() << "'" << endl;
    cout << "name is " << name << endl;
    cout << "Type of name is '" << typeid(name).name() << "'" << endl;

    getchar();
    return 0;
}
