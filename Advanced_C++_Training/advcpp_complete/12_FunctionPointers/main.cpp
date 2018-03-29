#include <iostream>
using namespace std;


void test()
{
    cout << "Test function" << endl;
}


int sum(int a, int b)
{
    return a + b;
}


int prod(int a, int b)
{
    return a * b;
}


int main()
{
    test();

    void(); // legal, but useless statement

    void (*pTest)();
    // this works
    pTest = &test;
    (*pTest)();
    pTest();

    // this also works
    pTest = test; // test is already a pointer
    pTest();

    int (*pCalculate)(int, int);
    auto finish{ false };
    while (!finish) {
        int op, a, b;
        cout << "1. Sum" << endl;
        cout << "2. Prod" << endl;
        cout << "3. Exit" << endl;
        cout << "Your choice:";
        cin >> op;

        switch (op) {
        case 1:
            pCalculate = sum;
            cout << "operand1 = ";
            cin >> a;
            cout << "operand2 = ";
            cin >> b;
            cout << "Result = " << pCalculate(a, b) << endl;
            break;
        case 2:
            pCalculate = prod;
            cout << "operand1 = ";
            cin >> a;
            cout << "operand2 = ";
            cin >> b;
            cout << "Result = " << pCalculate(a, b) << endl;
            break;
        case 3:
            finish = true;
            break;
        default:
            cout << "Unknown operation" << endl;
            break;
        }
    }

    getchar();
    return 0;
}
