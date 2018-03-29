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
    Test(int x) : x(x){}
    int getX() const { return x; }
    bool operator<(const Test& another) const { return x < another.x; }
    bool operator==(const Test& another) const { return x == another.x; }
    bool operator>(const Test& another) const { return !operator==(another) && !operator<(another); }

private:
    int x;
};


// Example of how an add "generic lambda" looks like in C++14:
struct
{
    template<typename T>
    auto operator() (T a, T b) const { return a + b; }
} add_generic;  // we cannot embed template class inside a function!


/**
 * Lambdas are nothing more than anonymous functors, except:
 * functors can not be called inline:
 * - struct {//}();
 * - functors cannot have a capture [] operator in front of struct definition
 */
void how_lambdas_work()
{
    struct
    {
        int operator() (int a, int b) const { return a + b; }
    } add;
    cout << add(10, 20) << endl;

    cout << add_generic(10.1, 20.2) << endl;
    cout << add_generic(char{10}, char{20}) << endl;

    // We cannot capture with a functor (at least I don't know how to do it):
//    [] struct
//    {
//        int operator() (int a, int b) const { return a + b; }
//    } add2;
}


void test_variadic_lambdas()
{
    // NOT YET WORKING
    //auto variadic_l = [](auto ... params)
    //{

    //};
    //std::function<int(int, int)> f = variadic_l;
    // cout << variadic_l(10, 20) << endl;
}


int main()
{
    // test the classic template-function version
    cout << power(2, 3) << endl;

    // now let's try the generic-lambda aproach (introduced in C++14):
    auto pwr = [](auto val, unsigned int pwr)  // you can have auto as input param type!
    {
        auto res = pwr == 0 ? 1 : val;
        for (auto i = 0u; i < pwr-1; i++)
            res *= val;
        return res;
    };

    cout << pwr(5, 5u) << endl;
    cout << pwr(2.23, 3u) << endl;
    cout << scientific << pwr(24.5f, 5u) << endl;
    cout << pwr(20u, 3u) << endl;

    // let's see how we can sort any elements in reverse order
    vector<Test> tests{20, 10, 5, 70, 100, 22};
    sort(tests.begin(), tests.end(), [](auto a, auto b) { return a > b; });
    // with above line we can sort any vectors of elements which override operator>

    for (auto e : tests) {
        cout << e.getX() << " ";
    }
    cout << endl;

    how_lambdas_work();

    getchar();
    return 0;
}
