#include <iostream>
#include <string>

using namespace std;


void greet(void(*greetType)(const string&), string name) //Se poate trimite lambda #1
{
    greetType(name);
}


void greet2(const string& name)
{
    cout << "Good bye, " << name << endl;
}

auto divide1(double a, double b) -> double //Check this out on a newer compiler, investiagete multiple return types in normal functions / lambdas
{
    if (b == 0)
        return -1;
    return a / b;
}

int main()
{
    auto morningGreet = [](const string& name) {
        cout << "Good morning " << name << endl;
    };
    
    auto eveningGreet = [](const string& name) {
        cout << "Good evening " << name << endl;
    };
    
    morningGreet("Ana");
    eveningGreet("Mihai");

    greet(morningGreet, "Ana"); //#1
    greet2("Mihai");
    
    auto divide = [](double a, double b) -> double {
        if (b == 0)
            return -1;
        return a / b;
    };
    
    cout << divide (1.0, 1.3) << endl;
    
    getchar();
    return 0;
}
