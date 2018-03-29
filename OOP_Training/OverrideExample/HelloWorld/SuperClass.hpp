//
//  SuperClass.hpp
//  HelloWorld
//
//  Created by Gabriel Oarga on 21/06/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#ifndef SuperClass_hpp
#define SuperClass_hpp

#include <stdio.h>
#include <iostream>

class SuperClass
{
public:
    SuperClass();
    virtual void printCount();
    
protected:
    int superCount;
};

#endif /* SuperClass_hpp */
