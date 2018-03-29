#include <iostream>
using namespace std;

// in C++03 null is represented as NULL == 0
// some projects use NULL, others simply use 0
// in C++11 nullptr was introduced and it has some advantages
// over NULL and 0
int main()
{
    // PROBLEM: both NULL and 0 are integers
    // => you could use them interchangeably

    class Test
    {
    public:
        explicit Test(int x) : x(x) {}

        static void show_info(int i) { cout << i << endl; }
        static void show_info(Test* t) { if (t != nullptr) show_info(t); }

        void show_info() const
        {
            cout << x << endl;
        }

    private:
        int x;
    };

    Test::show_info(10);
    Test::show_info(20);
    Test::show_info(NULL);  // which function am I calling?

    Test* t2 = nullptr;
    Test::show_info(t2);

    // so nullptr will always refer to a null reference, not an int

    cout << (NULL == nullptr) << endl;
    // cout << (nullptr + 1) << endl;

    getchar();
    return 0;
}
