#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


// let's say we need to create a function which is able to raise any
// value to the power given as argument
// this solution implies having a global templated function
template <typename T>
T power(T elem, unsigned int pwr)
{
    T result = pwr == 0 ? 1 : elem;
    for (auto i = 0u; i < pwr - 1; i++) {
        result = result * elem;
    }
    return result;
}


class Test
{
public:
    Test(int x) : x(x) {}
    int get_x() const { return x; }
    bool operator<(const Test& o) const { return x < o.x; }
    bool operator==(const Test& o) const { return x == o.x; }
    bool operator>(const Test& o) const { return x > o.x; }
private:
    int x{};
};


void how_lambdas_work()
{
}


int main()
{
    cout << power(2, 3) << endl;
    // 

    how_lambdas_work();

    vector<Test> v{ 20, 10, 11, 40, 5 };

    getchar();
    return 0;
}
