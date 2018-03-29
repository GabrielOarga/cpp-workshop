//
//  main.cpp
//  HelloWorld
//
//  Created by Gabriel Oarga on 21/06/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#include <iostream>

#include "SuperClass.hpp"
#include "DerivedClass.hpp"

int main(int argc, const char * argv[])
{
    SuperClass* super = new DerivedClass();
    
    super->printCount();
    static_cast<DerivedClass*>(super)->printCount();
    
    return 0;
}
