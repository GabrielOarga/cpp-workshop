#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class Employee;
class Manager;
class Programmer;

class IVisitor
{
public:
	virtual void visit(Employee& e) = 0;
	virtual void visit(Manager& m) = 0;
	virtual void visit(Programmer& p) = 0;
};

class Employee
{
protected:
	string m_name;
	double m_salary;
public:
	Employee(string name, double salary) : m_name(name), m_salary(salary) {}

	virtual void operation(IVisitor& v) { v.visit(*this); }

	string getName() const { return m_name; }
	double getSalary() const { return m_salary; }
};


class Manager : public Employee
{
public:
	Manager(string name, double salary) : Employee(name, salary) {}

	virtual void operation(IVisitor& v) override
	{
		v.visit(*this);
	}
};

class Programmer : public Employee
{
public:
	Programmer(string name, double salary) : Employee(name, salary) {}

	virtual void operation(IVisitor& v) override
	{
		v.visit(*this);
	}
};

class DisplayEmployee : public IVisitor {
public:
	virtual void visit(Employee& e) override {}

	virtual void visit(Manager& m) override
	{
		cout << "Manager " << m.getName() << endl;
	}

	virtual void visit(Programmer& p) override
	{
		cout << "Programmer " << p.getName() << endl;
	}
};

int main()
{
	Manager gigi{"Gigi", 100};
	Programmer ionel{"Ionel", 100 };

	getchar();
	return 0;
}
