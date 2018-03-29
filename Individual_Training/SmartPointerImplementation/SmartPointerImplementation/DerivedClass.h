#ifndef DERIVEDCLASS_H
#define DERIVEDCLASS_H

#include "BaseClass.h"

class DerivedClass : public BaseClass
{
public:
	DerivedClass(void);
	~DerivedClass(void); //No override for ease of testing with/without virtual
private:
	int test;
};

#endif //DERIVEDCLASS_H
