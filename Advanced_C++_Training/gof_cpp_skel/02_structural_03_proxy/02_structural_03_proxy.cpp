#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class ProxyBase
{
public:
	virtual void op1() = 0;
	virtual void op2() = 0;
	virtual string op3() = 0;
};

class SimpleProxy : public ProxyBase
{
private:
	ProxyBase& m_target;
public:
	SimpleProxy(ProxyBase& target) : m_target(target) {}
	void op1() override { m_target.op1(); }
	void op2() override { m_target.op2(); }
	string op3() override { return m_target.op3(); }
};

class SimpleImplementation : public ProxyBase
{
	void op1() override { cout << "SimpleImpl::op1()" << endl; }
	void op2() override { cout << "SimpleImpl::op1()" << endl; }
	string op3() override { return "SimpleImpl::op3()"; }
};

int main()
{
	SimpleProxy proxy{ SimpleImplementation{} };
	proxy.op1();
	proxy.op2();
	cout << proxy.op3() << endl;

	getchar();
	return 0;
}
