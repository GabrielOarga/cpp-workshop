#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PaymentMethod
{
public:
	virtual void displayPaymentInformation() = 0;
};

class MyFramework
{
public:
	void establishSecureConnection()
	{
		cout << "Secure connection established" << endl;
	}

	void connectToBank()
	{
		establishSecureConnection();
		cout << "Connecting to bank..." << endl;
	}

	virtual PaymentMethod& getPaymentMethod() = 0;

	void buy(double sum, string shopName, string product)
	{
		cout << "Buying " << product << " from " << shopName << endl;
		PaymentMethod& m = getPaymentMethod();
		m.displayPaymentInformation();
		connectToBank();
		cout << "Payment complete" << endl;
	}
};


class MyPaymentMethod : public PaymentMethod
{
public:
	void displayPaymentInformation()
	{
		cout << "Display MY Payment info" << endl;
	}
};


class MyApplication : public MyFramework
{
public:
	PaymentMethod& getPaymentMethod() {
		return MyPaymentMethod{};
	}
};


int main()
{
	string product{ "Trotineta" };
	string shopName{ "emag" };
	MyFramework& myApp{ MyApplication{} };
	myApp.buy(500, shopName, product);

	getchar();
	return 0;
}
