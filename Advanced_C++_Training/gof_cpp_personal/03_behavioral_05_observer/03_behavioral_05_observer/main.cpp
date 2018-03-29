//
//  main.cpp
//  03_behavioral_05_observer
//
//  Created by Gabriel Oarga on 17/10/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>

using namespace std;

class Observer
{
public:
    virtual void update() = 0;
};

class Observable
{
public:
    virtual void attach(Observer *obs)
    {
        m_observers.push_back(obs);
    }
    
    virtual void detach(Observer* obs)
    {
        m_observers.erase(
                          remove_if(
                                    m_observers.begin(),
                                    m_observers.end(),
                                    [obs](auto o) { return o == obs; }
                                    )
                          );
    }
    
    virtual void notifyObservers()
    {
        for (auto o : m_observers)
            o->update();
    }
    
protected:
    vector<Observer*> m_observers;
};

// Add customer
class Customer : public Observer
{
public:
    Customer( string name ) { m_name = name; }
    string getName() { return m_name; };
    void update() override;
    
private:
    string m_name{};
};

class Deposit : public Observable
{
public:
    int getNrSmartphones() const { return m_nrSmartphones; }
    
    static Deposit& getInstance()
    {
        static Deposit d{};
        return d;
    }
    
    // implement buy(Customer* c)
    void buy(Customer *c)
    {
        if (m_nrSmartphones <= 0 )
        {
            cout << c->getName() << " cannot buy yet" << endl;
            attach(c);
        } else {
            detach(c);
            m_nrSmartphones--;
            cout << c->getName() << " bought a smartphone" << endl;
        }
    }
    
    
    void setNrSmartphones(int nr)
    {
        m_nrSmartphones = nr;
        notifyObservers();
    }
    
    void addSmartphones(int nr)
    {
        m_nrSmartphones += nr;
        notifyObservers();
    }
    
private:
    int m_nrSmartphones{};
    
    Deposit() {}
    Deposit(const Deposit& o) = delete;
    
    void notifyObservers()
    {
        if (m_nrSmartphones > 0)
            for (auto o : m_observers)
                o->update();
    }
};

void Customer::update()
{
    Deposit::getInstance().buy(this);
}

int main()
{
    vector<Customer*> customers { new Customer("Ion"), new Customer("Gigi") };
    
    for (auto c : customers) {
        Deposit::getInstance().buy(c);
    }
    
    this_thread::sleep_for(1s);
    Deposit::getInstance().addSmartphones(1);
    
    for (auto c : customers)
        delete c;
    
    customers.clear();
    
    getchar();
    return 0;
}

