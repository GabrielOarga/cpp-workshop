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
    int width = 100; // cm
    int height = 20; // mm
    int L = 1000; // cm
    auto width_m = width / 100.0f;
    auto height_m = height / 1000.0f;
    auto L_m = L / 100.0f;
    auto volume_m = width_m * height_m * L_m;

    auto volume_in_cm = width_m * height_m * 10 * L_m;
    // etc: the idea is that you always need to be careful to properly make the conversions
    // I sometimes have to translate widths and heights into pixels and vice-versa
}


long double operator"" _kg(long double val) { return val * 1000; }
long double operator"" _g(long double val) { return val; }


// transform into dm3
long double operator"" _m3(long double val) { return val / 1000.0l; }
long double operator"" _cm3(long double val) { return val * 1000.0l; }
long double operator"" _dm3(long double val) { return val; }


float operator "" _f(const char* val, size_t size) { return stof(val); }
long double operator "" _d(const char* val, size_t size) { return stod(val); }


class BankAccount
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

    friend BankAccount operator"" _ron(long double val);

    friend BankAccount operator"" _eur(long double val);

    long double balance{ 0 };
};


long double BankAccount::exchange_rate{ 4.5 };

BankAccount operator"" _ron(long double val)
{
    return BankAccount(val);
}


BankAccount operator"" _eur(long double val)
{
    return BankAccount(val * BankAccount::exchange_rate);
}


int main()
{
    auto duration = 24s + 15ms; // already defined in <chrono>
    cout << chrono::milliseconds(duration).count() << endl;

    BankAccount b1{402.0_ron}; // the literal must be a double literal
    cout << "Balance1 = " << b1.get_balance() << "Lei" << endl;

    BankAccount b2{150.0_eur};
    cout << "Balance2 = " << b2.get_balance() << "Lei" << endl;

    BankAccount b3 = 3200.0_ron + 230.0_eur;
    cout << "Balance3 = " << b3.get_balance() << "Lei" << endl;

    long double volume1 = 250.0_dm3;
    long double volume2 = 400.7_m3;
    cout << "Volume is " << (volume1 + volume2) << endl;

    cout << scientific << "193.005"_f << endl;
    cout << scientific << "201.01"_d << endl;

    getchar();
    return 0;
}
