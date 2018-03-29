//
//  DerivedClass.cpp
//  HelloWorld
//
//  Created by Gabriel Oarga on 21/06/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#include "DerivedClass.hpp"

DerivedClass::DerivedClass()
{
    derviedCount = 2;
    std::cout << "Hello Derived Class\n";
}

void DerivedClass::printCount()
{
    std::cout << "Derived count: " << derviedCount << std::endl;
}
