#include <iostream>

using namespace std;


class Test
{
public:
    void run()
    {
        auto c{ 3 }, d{ 4 };
//        auto printAll = [=]() {
//        auto printAll = [c, d, this]() {
        auto printAll = [c, d, this]() {
            cout << "a = " << a << endl;
            cout << "b = " << b << endl;
            cout << "c = " << c << endl;
            cout << "d = " << d << endl;
            
            a++;
        };
        
        printAll();
        cout << "a = " << a << endl;

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
