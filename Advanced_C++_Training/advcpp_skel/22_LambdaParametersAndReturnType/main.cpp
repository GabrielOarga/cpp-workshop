#include <iostream>
#include <string>

using namespace std;


void greet(void(*greetType)(const string&), string name)
{
    greetType(name);
}


void greet2(const string& name)
{
    cout << "Good bye, " << name << endl;
}

int main()
{

    getchar();
    return 0;
}
