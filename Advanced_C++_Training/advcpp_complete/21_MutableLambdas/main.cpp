#include <iostream>

using namespace std;


void testMutableScope()
{
    cout << "test mutable scope" << endl;
    auto a{ 5 };

    auto ex = [a]() mutable {
        // a is "maintained" between consecutive lambda calls.
        a += 10;
        cout << "internal scope a = " << a << endl;
    };

    ex();
    ex();
    ex();

    cout << "external scope a=" << a << endl;
}


void testUnmutableScope()
{
    cout << "test unmutable scope" << endl;
    auto a{ 5 };
    auto ex = [a]() {
        // a is copied into local scope only once
        cout << "internal scope a = " << a << endl;
    };

    a += 10;
    cout << "external scope a = " << a << endl;
    ex();

    a += 10;
    cout << "external scope a = " << a << endl;
    ex();

    a += 10;
    cout << "external scope a = " << a << endl;
    ex();
}


int main()
{
    testMutableScope();
    testUnmutableScope();

    getchar();
    return 0;
}
