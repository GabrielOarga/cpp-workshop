#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

// a basic example:
constexpr int getArraySize() { return 10; }

// there are some limitations on what can a constexpr contain:

// this will not work: the compiler cannot call this
// constexpr double PI = acos(-1);

// constexpr tells the compiler that a given function / expression
// will ALWAYS return the same value
// that value can be calculated at compile-time

// a constexpr can depend on constants and/or on other constexpr-essions

// in C++11 there were some limitations for constexpr:
// - constexpr could not be placed on a virtual function
// - constexpr functions cannot be void!
// 

// C++14 lifted some of these restrictions: https://isocpp.org/files/papers/N3652.html
// BUT: the code below didn't compile in older versions of VS2015. It does now (VS2017)
constexpr void square(double& x) { x *= x; }

constexpr int f(int i)
{
    return i * i;
	auto SIZE{ 10 };
    // code below was not supported in VS2015 some months ago (~start of 2017)
	// now it is:
    int j = 0;
    for (; SIZE > 0; --SIZE)
        ++j;
    return j;
}

constexpr int SIZE = f(5);

constexpr int fibo(int n)
{
    return (n <= 2) ? 1 : fibo(n - 1) + fibo(n - 2);
}

constexpr int FIBO_10 = fibo(10);
constexpr int FIBO_5 = fibo(5);
const int FIBO_20 = fibo(20);

// there is a limit here: we know that fibo consumes a lot of stack!!
// => the following constexpr value cannot be wholy computed on VS2015:
// 'constexpr' call evaluation step limit of 100000 exceeded; use /constexpr:steps<NUMBER> to increase the limit

// const int FIBO_100 = fibo(100);


class Foo
{
public:
    constexpr explicit Foo(int i) : n(i) {}
    constexpr int get_n() const { return n; }
private:
    int n;
};


int main()
{
    // we can check at compile-time via static_assert:
    static_assert(FIBO_10 == 55, "fibo() is not correct. Check fibo(10)!");
    static_assert(FIBO_5 == 5, "fibo() is not correct. Check fibo(5)!");

    static_assert(std::is_literal_type<Foo>(), "Foo is not a literal type => cannot be a constexpr");

    constexpr Foo foo(5);

    int numbers[getArraySize()];
    for (auto& n : numbers) n = 0;
    for (auto n : numbers) cout << n << " ";
    cout << endl;

    // we can have a constexpr also inside a function
    // here our constexpr depends on other constexpr-essions
    constexpr int other_numbers[SIZE + getArraySize() + f(2)]{};

    // line below doesn't work:
    // for (auto& n : names) n = 10;
    for (auto n : other_numbers) cout << n << " ";
    cout << endl;

    // on the other hand, fill compiles, but doesn't link!
    // fill_n(other_numbers, SIZE, 10);
    
    getchar();
    return 0;
}
