#include <iostream>
#include <atomic>
#include <thread>
#include "RandomUtil.h"

using namespace std;
using namespace edocti::utils;

/**
 * atomic is a class template for non-interleaved value access and operations
 */

class BankAccount
{
public:
    explicit BankAccount(int balance) : balance{balance} {}

    BankAccount() : BankAccount(0) {}

    void deposit(int amount)
    {
        // memory_order_relaxed only enforces atomicity
        // and modification order consistency
        // it is the fastest 
        balance.fetch_add(amount, std::memory_order_relaxed);
    }

    void withdraw(int amount)
    {
        balance.fetch_sub(amount, std::memory_order_relaxed);
    }

    int get_balance() const { return  balance.load(std::memory_order_relaxed); }

    virtual ~BankAccount() = default;
    BankAccount(const BankAccount& other) = delete;
    BankAccount& operator=(const BankAccount& other) = delete;

private:
    atomic_int balance;
};


void produce(BankAccount& account)
{
    RandomUtil::randomize();
    for (auto i=0; i< 10; i++) {
        auto val = RandomUtil::nextInt(1, 10);
        account.deposit(10);
        cout << "Producer-" << this_thread::get_id() << " added " << val << ". Current = " << account.get_balance() << endl;
    }
}

void consume(BankAccount& account)
{
    RandomUtil::randomize();
    for (auto i = 0; i < 10; i++) {
        auto val = RandomUtil::nextInt(1, 10);
        account.withdraw(10);
        cout << "Consumer-" << this_thread::get_id() << " added " << val << ". Current = " << account.get_balance() << endl;
    }
}


int main()
{
    BankAccount ionescu;
    thread t1(produce, ref(ionescu));
    thread t2(consume, ref(ionescu));
    t1.join();
    t2.join();

    // other atomic operations:
    // ++, --, fetch_sub(), fetch_and(), fetch_or(), fetch_xor()

    getchar();
    return 0;
}
