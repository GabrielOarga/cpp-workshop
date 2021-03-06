#include "stdafx.h"
#include <iostream>

using namespace std;

class AmericanPlug;
class AmericanSocket;
class RomanianPlug;
class RomanianSocket;
class AmericanSocket;

class AmericanPlug
{
public:
	void plug(AmericanSocket& socket);
};

class AmericanSocket
{
public:
	void accept(AmericanPlug& plug);
};

void AmericanPlug::plug(AmericanSocket& socket)
{
	socket.accept(*this);
}

void AmericanSocket::accept(AmericanPlug& plug)
{
	cout << "American plug inserted" << endl;
}

class AmericanSmartPhone
{
public:
	AmericanSmartPhone(string name) : m_name(name) {}

	void charge(AmericanSocket &socket)
	{
		socket.accept(m_plug);
	}

	friend ostream &operator<<(ostream& out, const AmericanSmartPhone &s);
private:
	string m_name{};
	AmericanPlug m_plug{};
};

ostream &operator<<(ostream &out, const AmericanSmartPhone &s)
{
	out << s.m_name;
	return out;
}


class RomanianPlug
{
public:
	void plug(RomanianSocket& socket);
};

class RomanianSocket
{
public:
	void accept(RomanianPlug& plug);
};

void RomanianPlug::plug(RomanianSocket& socket)
{
	socket.accept(*this);
}

void RomanianSocket::accept(RomanianPlug& plug)
{
	cout << "Romanian plug inserted" << endl;
}

class RomanianToAmericanAdapter
{
public:
	void plug(RomanianSocket socket)
	{
		socket.accept(m_romPlug);
	}

	AmericanSocket getSocket() const { return m_amSocket; }

private:
	AmericanSocket m_amSocket{};
	RomanianPlug m_romPlug{};
};

int main()
{
	AmericanSmartPhone galaxy{ "Galaxy" };
	RomanianSocket wallSocket{};
	RomanianToAmericanAdapter adapter{};
	adapter.plug(wallSocket);
	galaxy.charge(adapter.getSocket());

	getchar();
	return 0;
}
