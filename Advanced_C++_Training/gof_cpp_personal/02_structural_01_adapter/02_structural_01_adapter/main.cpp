//
//  main.cpp
//  02_structural_01_adapter
//
//  Created by Gabriel Oarga on 16/10/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#include <iostream>

using namespace std;

class AmericanPlug;
class AmericanSocket;
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

class RomanianPlug;
class RomanianSocket
{
public:
    void accept(RomanianPlug& plug);
};

class RomanianPlug
{
public:
    void plug(RomanianSocket& socket);
};

void RomanianPlug::plug(RomanianSocket& socket)
{
    socket.accept(*this);
}

void RomanianSocket::accept(RomanianPlug &plug)
{
    cout << "Romanian plug inserted into Rom. socket" << endl;
}

class AmericanToRomanianAdapter
{
public:
    void plug(RomanianSocket& socket)
    {
        socket.accept(m_roPlug);
    }
    
    AmericanSocket getSocket() const { return m_amSocket; }
    
private:
    AmericanSocket m_amSocket{};
    RomanianPlug m_roPlug{};
};

ostream &operator<<(ostream &out, const AmericanSmartPhone &s)
{
    out << s.m_name;
    return out;
}

int main()
{
    AmericanSmartPhone iphone{"7"};
    RomanianSocket wallSocket{};
    AmericanToRomanianAdapter adapter{};
    
    adapter.plug(wallSocket);
    iphone.charge(adapter.getSocket());
}

