#include <iostream>

using namespace std;


class Test
{
public:
    void run()
    {
        auto c{ 3 }, d{ 4 };
        // auto printAll = [=]() {             // this is possible, captures also the "this" pointer (which btw cannot be modified => cannot be captured by reference!)
        // auto printAll = [c, this, d] () {   // "this" can be placed anywhere
        // auto printAll = [&, this] () {      // capture everything by reference, except "this" (which would be illegal)
        auto printAll = [this, c, d]() {
            cout << "a = " << a << endl;
            cout << "b = " << b << endl;
            cout << "c = " << c << endl;
            cout << "d = " << d << endl;
        };

        printAll();
    }

private:
    int a{ 1 };
    int b{ 2 };
};


int main()
{
    Test t;
    t.run();

    getchar();
    return 0;
}
