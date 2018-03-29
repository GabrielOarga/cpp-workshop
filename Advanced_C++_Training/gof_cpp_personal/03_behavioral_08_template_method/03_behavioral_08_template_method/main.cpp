//
//  main.cpp
//  03_behavioral_08_template_method
//
//  Created by Gabriel Oarga on 17/10/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PaymentMethod
{
public:
    virtual void displayPaymentInformation() const = 0;
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
    
    virtual const PaymentMethod& getPaymentMethod() = 0;
    
    void buy(double sum, string shopName, string product)
    {
        cout << "Buying " << product << " from " << shopName << endl;
        const PaymentMethod& m = getPaymentMethod();
        m.displayPaymentInformation();
        connectToBank();
        cout << "Payment complete" << endl;
    }
};


class MyPaymentMethod : public PaymentMethod
{
public:
    void displayPaymentInformation() const
    {
        cout << "Display MY Payment info" << endl;
    }
};


class MyApplication : public MyFramework
{
public:
    const PaymentMethod& getPaymentMethod() override
    {
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

