#include <iostream>
using namespace std;


// in C++03 null is represented as NULL == 0
// some projects use NULL, others simply use 0
// in C++11 nullptr was introduced and it has some advantages
// over NULL and 0
int main()
{
    class Test
    {
    public:
        explicit Test(int x) : x(x) { }

        static void show_info(int c) {
			cout << c << endl;
        }

        static void show_info(Test* t) {
			
        }

    private:
        int x;
    };


    getchar();
    return 0;
}
