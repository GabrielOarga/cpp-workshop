#include "stdafx.h"
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


int main()
{
//	vector<Customer*> customers { new Customer("Ion"), new Customer("Gigi") };

//	for (auto c : customers) {
//		Deposit::getInstance().buy(c);
//	}

	this_thread::sleep_for(1s);
	Deposit::getInstance().addSmartphones(1);

//	for (auto c : customers)
//		delete c;
//
//	customers.clear();

	getchar();
	return 0;
}
