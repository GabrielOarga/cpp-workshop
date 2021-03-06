#include "stdafx.h"
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
		SampleBuilder& i1(int i) { m_i1 = i; return *this; }
		SampleBuilder& i2(int i) { m_i2 = i; return *this; }
		SampleBuilder& i3(int i) { m_i3 = i; return *this; }
		SampleBuilder& i4(int i) { m_i4 = i; return *this; }
		Sample build()
		{
			return Sample(*this);
		}

		int getI1() const { return m_i1; }
		int getI2() const { return m_i2; }
		int getI3() const { return m_i3; }
		int getI4() const { return m_i4; }
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
		m_i1(builder.getI1()),
		m_i2(builder.getI2()),
		m_i3(builder.getI3()),
		m_i4(builder.getI4())
	{
		// Empty
	}
};

ostream &operator<<(ostream& out, const Sample& s)
{
	out << "i1=" << s.m_i1 << ", i2=" << s.m_i2 << ", i3=" << s.m_i3 << ", i4=" << s.m_i4;
	return out;
}


int main()
{
	Sample s1 = Sample::SampleBuilder{}.i1(10).i2(20).build();
	Sample s2 = Sample::SampleBuilder{}.i3(20).i1(200).i4(30).build();

	cout << s1 << endl << s2 << endl;

	getchar();
	return 0;
}
