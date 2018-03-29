#include "stdafx.h"
#include "BaseClass.h"

#include <iostream>

using std::cout;
using std::endl;

BaseClass::BaseClass(void)
{
	cout << "Constructing BaseClass object -> " << this << endl;
}

BaseClass::BaseClass(const BaseClass& base)
{
	cout << "Copy Constructor -> " << this << endl;
}

BaseClass::~BaseClass(void)
{
	cout << "Destructing BaseClass object -> " << this << endl;
}
