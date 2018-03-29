#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

using namespace std;

/**
 * atomic is a class template for non-interleaved value access and operations
 */

class BankAccount
{
public:
    BankAccount(int amount)
    : m_balance(amount)
    {}
    
    BankAccount()
    : BankAccount(0)
    {}
    
    void deposit(int amount)
    {
        m_balance.fetch_add(amount, std::memory_order_relaxed);
    }
    
    void withdraw(int amount)
    {
        m_balance.fetch_sub(amount, std::memory_order_relaxed);
    }
    
    int get_balance() const
    {
        return m_balance.load();
    }
    
private:
    atomic_int m_balance; //must be initialised with an amount
    
};

void prod(BankAccount& common)
{
    while(true) {
        auto val{ 100 };
        cout << "Producer " << std::this_thread::get_id() << " produced" << val << endl;
        common.deposit(val);
    }
}

void cons(BankAccount& common)
{
    while(true)
    {
        auto val{ 50 };
        cout << "Producer " << std::this_thread::get_id() << " produced" << val << endl;
        common.withdraw(val);
    }
}

int main()
{
    BankAccount mihai{ };
    vector<thread> workers;
    
    workers.emplace_back(thread(cons, ref(mihai)));
    workers.emplace_back(thread(prod, ref(mihai)));
    workers.emplace_back(thread(cons, ref(mihai)));
    
    for (auto& w: workers)
        if (w.joinable())
            w.join();
    
    getchar();
    return 0;
}
