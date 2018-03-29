#include "stdafx.h"
#include "DerivedClass.h"

#include <iostream>

using std::cout;
using std::endl;

DerivedClass::DerivedClass(void)
{
	cout << "Constructing DerivedClass object -> " << this << endl;
	test = 1;
}

DerivedClass::~DerivedClass(void)
{
	cout << "Destructing DerivedClass object -> " << this << endl;
}
