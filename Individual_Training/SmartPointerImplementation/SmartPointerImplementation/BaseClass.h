#ifndef BASECLASS_H
#define BASECLASS_H

class BaseClass
{
public:
	BaseClass(void);
	BaseClass(const BaseClass& base);
	virtual ~BaseClass(void);
};

#endif //BASECLASS_H