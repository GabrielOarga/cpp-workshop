#include <iostream>

using namespace std;


void testMutableScope()
{
    /*
     * Mutable lambda means that you can modify internal scope variables, without having exterior modifications because it keeps a separate internal copy, while the function scope is active
    */
    
    cout << "test mutable - start" << endl;
    
    auto a{ 5 };
    auto example = [a]() mutable {
        a += 10;
        cout << "Internal scope: " << a << endl;
    };

    example();
    example();
    
    cout << "Exsternal scope: " << a << endl;
    
    cout << "test mutable - end" << endl;
}


void testUnmutableScope()
{
    /*
     * Non Mutable means that you cannot modifiy the variables within internal scope, it still has a copy, so taht means even if modified outside, it's internal variable does not change
    */
    
    cout << "test unmutable - start" << endl;

    auto a{ 5 };
    auto example = [a]() {
        cout << "Internal scope: " << a << endl;
    };
    
    a += 10;
    example();
    a += 10;
    example();
    a += 10;
    
    cout << "Exsternal scope: " << a << endl;
    
    cout << "test unmutable - end" << endl;
}


int main()
{
    testMutableScope();
    testUnmutableScope();

    getchar();
    return 0;
}
