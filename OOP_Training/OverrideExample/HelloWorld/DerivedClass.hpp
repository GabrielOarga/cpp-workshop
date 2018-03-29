//
//  DerivedClass.hpp
//  HelloWorld
//
//  Created by Gabriel Oarga on 21/06/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#ifndef DerivedClass_hpp
#define DerivedClass_hpp

#include <stdio.h>

#include "SuperClass.hpp"

class DerivedClass : public SuperClass
{
public:
    DerivedClass();
    void printCount() override;
    
private:
    int derviedCount;
};

#endif /* DerivedClass_hpp */
