// SmartPointerImplementation.cpp : Defines the entry point for the console application.
//

#include "BaseClass.h"
#include "DerivedClass.h"
#include "SharedPointer.h"

#include <memory>
#include <iostream>

//#define SmartPtr CustomSmartPointer

using std::cout;
using std::endl;

int main (int argc, char** argv)
{
	{
		cout << " ------------- normal pointer -------------" << endl;
		BaseClass* pDerived = new DerivedClass;
		DerivedClass* dClass = dynamic_cast<DerivedClass*>(pDerived);

		cout << " ------------- std::shared_ptr -------------" << endl;
		std::shared_ptr<BaseClass> spDerived(new DerivedClass);
		//spDerived = std::make_shared<DerivedClass>(*pDerived);

		cout << " ------------- custom shared_ptr -------------" << endl;

		cout << "\n\n ------------- destructors: -------------" << endl;

		cout << " ------------- normal pointer -------------" << endl;
		delete pDerived;

		cout << " ------------- custom + std shared_ptr -------------" << endl;
	}

	for(;;);
	return 0;
}

/* Notes:


*/


/*#define SmartPtr CustomSmartPointer
SmartPtr testFunction(SmartPtr* ptr1, SmartPtr& ptr2, SmartPtr ptr3)
{
    SmartPtr internalPtr;
    *ptr1 = ptr2;
    ptr2 = ptr3;
    internalPtr = *ptr1;
    return internalPtr;
}

int main(int argc, char* argv[])
{
    SmartPtr ptr1, ptr2;
    SmartPtr ptr4 = testFunction( &ptr1, ptr2, SmartPtr() );
    return 0;
}*/

