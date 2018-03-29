#include <iostream>

using namespace std;


class Test
{
public:
    void run() const
    {
        auto c{ 3 }, d{ 4 };

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
