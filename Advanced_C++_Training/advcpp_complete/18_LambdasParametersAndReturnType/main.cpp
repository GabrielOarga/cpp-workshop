#include <iostream>
#include <string>

using namespace std;


void greet(void (*greetType)(const string&), string name)
{
    greetType(name);
}


void runDivide(double (*div)(double, double), double a, double b)
{
    auto result = div(a, b);
    cout << scientific << result << endl;
}


auto add(int a, int b)
{
    return a + b;
}


int main()
{
    cout << []() { return 1; }() << endl;

    auto simpleGreet = [](const string& name) { cout << "Hello " << name << endl; };
    greet(simpleGreet, "Adrian");

    auto morningGreet = [](const string& name) { cout << "Good morning " << name << endl; };
    greet(morningGreet, "Mihai");

    // Sometimes the return type can be inferred at compile-time:
    auto add = [](int a, int b) { return a + b; };

    cout << add(10, 20) << endl;

    // Other times the return type cannot be inferred => we need to tell
    // the compiler the return type:
    auto divide = [](double a, double b) -> double
    {
        if (b == 0.0) {
            return 0; // here we return int
        }
        return a / b; // here we return double => compiler cannot *infer* the return type
        // => I have to specify it with *trailing return* syntax
    };

    cout << scientific << divide(10.0, 5.0) << endl;

    runDivide(divide, 10, 20);

    getchar();
    return 0;
}
