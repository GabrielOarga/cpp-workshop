#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

/*
 * constepr must be resolvable at compile time
 * constexpr can be used with templates for meta programing
 * constexpr will be linked at runtime if forced
 * needs clarification, constexpr vs const, and how it can be used properly and where
*/

constexpr int getArrSize() { return 10; }

//constexpr void square(double& x) { x *= x; } //Should be possible, update compiler

constexpr double square_d(double d) { return d * d; }

constexpr double area = square_d(100); //uses another const expr

/* Can't use for in constexpr, needs update compiler
constexpr int f(int i)
{
    auto SIZE{ 10 };
    auto res{ 0 };
    
    for (; SIZE > 0; --SIZE)
    {
        res++;
    }
    
    return res;
}
*/

//constexpr int SIZE1{ f(10) }; //f(10) se va rezolva la runtime, si va fi salvata valoarea in SIZE1
//constexpr int SIZE2{ f(20) }; // This can only be run if F(10) is constexpr

//int fibo_15 = f(10); //Constexpr function can be used as nromal function if desired, outside of consexpr functions

class Test
{
public:
    constexpr Test(int nr)
    : m_nr(nr)
    {
        
    }
/*    constexpr setNr(int nr)
    {
        m_nr = nr;
    }*/
    
private:
    int m_nr;
};

int main()
{
    int numbers[getArrSize()] {}; //what is this? do some more research
    
    cout << area << endl;
    
    constexpr Test t{ 10 };
    //t.setNr(100); cannot change constexpr state at runtime
    
    getchar();
    return 0;
}
