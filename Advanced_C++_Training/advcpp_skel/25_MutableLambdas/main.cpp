#include <iostream>

using namespace std;


void testMutableScope()
{
    cout << "test mutable - start" << endl;

    cout << "test mutable - end" << endl;
}


void testUnmutableScope()
{
    cout << "test unmutable - start" << endl;

    cout << "test unmutable - end" << endl;
}


int main()
{
    testMutableScope();
    testUnmutableScope();

    getchar();
    return 0;
}
