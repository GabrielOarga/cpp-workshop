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

struct //Basically a generic lambda
{
    template<typename T>
    auto operator()(T a, T b) const { return a + b; };
} add_generic;

void how_lambdas_work()
{
    struct //Basically a normal lambda
    {
        int operator()(int a, int b) const { return a + b; };
    } add ;
    cout << add(10,20) << endl;
    
    cout << add_generic(10, 20) << endl;
    cout << add_generic(12.30, 21.45) << endl;
}


int main()
{
    cout << power(2, 3) << endl;

    auto pwr = [](auto value, unsigned int p) { //Still templates internally
        auto result = p == 0 ? 1 : value;
        
        for (auto i = 0u; i < p - 1; i++)
        {
            result *= value;
        }
        return result;
    };
    
    cout << pwr(10, 2) << endl; //Lambdas don'te xist untill called, the compiler just skips them entirely

    vector<Test> tests{ 20, 10, 11, 40, 5 };
    sort(tests.begin(), tests.end(), [](auto a, auto b) {
        return a > b;
    });
    
    //Test is now { 40 20 11 10 5 };
    for (auto t : tests) {
        cout << t.get_x() << " ";
    }
    cout << endl;
    
    
    
    how_lambdas_work();

    vector<Test> v{ 20, 10, 11, 40, 5 };

    getchar();
    return 0;
}
