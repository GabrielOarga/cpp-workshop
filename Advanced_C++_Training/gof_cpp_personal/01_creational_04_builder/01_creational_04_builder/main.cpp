//
//  main.cpp
//  01_creational_04_builder
//
//  Created by Gabriel Oarga on 16/10/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>

using namespace std;

class Sample
{
public:
    static class SampleBuilder
    {
    public:
        SampleBuilder& i1(int i) { m_i1 = i; return *this; };
        SampleBuilder& i2(int i) { m_i2 = i; return *this; };
        SampleBuilder& i3(int i) { m_i3 = i; return *this; };
        SampleBuilder& i4(int i) { m_i4 = i; return *this; };
        
        int getI1() { return m_i1; }
        int getI2() { return m_i2; }
        int getI3() { return m_i3; }
        int getI4() { return m_i4; }
        Sample build() { return Sample(*this); }
        
    private:
        int m_i1{};
        int m_i2{};
        int m_i3{};
        int m_i4{};
    };
    
    friend ostream &operator<<(ostream& out, const Sample& s);
    
private:
    int m_i1{};
    int m_i2{};
    int m_i3{};
    int m_i4{};

    Sample(SampleBuilder& builder) :
        m_i1( builder.getI1() ),
        m_i2( builder.getI2() ),
        m_i3( builder.getI3() ),
        m_i4( builder.getI4() )
    { }
    
};

ostream &operator<<(ostream& out, const Sample& s)
{
    out << "i1=" << s.m_i1 << ", i2=" << s.m_i2 << ", i3=" << s.m_i3 << ", i4=" << s.m_i4;
    return out;
}


int main()
{
    Sample s1 = Sample::SampleBuilder{}.i1(100).i2(20).i4(40).build();
    Sample s2 = Sample::SampleBuilder{}.i4(20).i1(30).i3(9001).build();
    cout << s1 << endl;
    cout << s2 << endl;
    return 0;
}

