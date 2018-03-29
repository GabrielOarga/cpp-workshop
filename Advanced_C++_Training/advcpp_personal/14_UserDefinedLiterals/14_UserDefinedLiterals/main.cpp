#include <iostream>
#include <chrono>
#include <string>

using namespace std;


/**
* Allow (1) integer, (2) FP, (3) character and (4)string literals to
* *produce* objects of user-defined type by defining a user-defined suffix
*
* Attention: this obviously adds runtime.
* BUT: you'll use this feature in cases where you'd anyway perform that runtime
* => this feature adds readability and coding speed
*/

/**
* When would you do that?
* When you want for instance to make conversions on the fly:
*/

void an_old_example()
{
    auto width_cm{ 100 };
    auto height_mm {20};
    auto L_cm{ 1000 };
    auto width_m = width_cm / 100.0f;
    auto height_m = height_mm / 1000.0f;
    auto L_m = L_cm / 100.0f;
    auto volume_m = width_m * height_m * L_m;

    auto volume_in_cm = width_m * height_m * 10 * L_m;
    // etc: the idea is that you always need to be care to properly make the conversions
    // I sometimes have to translate widths and heights into pixels and vice-versa
}

inline long double operator"" _kg(long double val) { return val * 1000; }
inline long double operator"" _g(long double val) { return val; }

// transform into dm3
inline long double operator"" _m3(long double val) { return val / 1000.0l; }
inline long double operator"" _cm3(long double val) { return val * 1000.0l; }
inline long double operator"" _dm3(long double val) { return val; }

float operator "" _f(const char* val, size_t size) { return stof(val); }
long double operator "" _d(const char* val, size_t size) { return stod(val); }

struct BankAccount
{
public:
    static long double exchange_rate;

    long double get_balance() const { return balance; }

    BankAccount operator+(BankAccount& other) const
    {
        return BankAccount(get_balance() + other.get_balance());
    }

    void deposit(long double amount)
    {
        balance += amount;
    }

    void withdraw(long double amount)
    {
        deposit(-amount);
    }

private:
    explicit BankAccount(long double val) : balance(val) { }

    long double balance{ 0 };
};


int main()
{
    //auto duration = 24s + 15ms; // already defined in <chrono>
    //cout << chrono::milliseconds(duration).count() << endl;



    getchar();
    return 0;
}
