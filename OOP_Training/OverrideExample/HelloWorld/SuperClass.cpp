//
//  SuperClass.cpp
//  HelloWorld
//
//  Created by Gabriel Oarga on 21/06/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#include "SuperClass.hpp"

SuperClass::SuperClass()
{
    superCount = 1;
    std::cout << "Hello Super Class\n";
}

void SuperClass::printCount()
{
    std::cout << "Super count: " << superCount << std::endl;
}
