//
//  main.cpp
//  02_structural_07_bridge
//
//  Created by Gabriel Oarga on 16/10/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <functional>

using namespace std;

class Image
{
public:
    Image(string name) : m_name(name) {}
    
    virtual void load() = 0;
    virtual void rotate(int angle) = 0;
    
protected:
    string m_name;
};

class Png : Image
{
public:
    Png(string name) : Image(name) {}
    
    virtual void load() override
    {
        // ...
        cout << "png.load()" << endl;
        // ...
    }
    
    virtual void rotate(int angle) override
    {
        cout << "pre: png.rotate()" << endl;
        // ...
        cout << "post: png.rotate()" << endl;
    }
};

class Jpg : Image {
public:
    Jpg(string name) : Image(name) {}
    
    virtual void load() override
    {
        // ...
        cout << "jpg: some specific opetration" << endl;
        cout << "jpg.load()" << endl;
        // ...
    }
    
    virtual void rotate(int angle) override
    {
        cout << "pre: jpg.rotate()" << endl;
        // ...
        cout << "post: jpg.rotate()" << endl;
    }
};

int main(int argc, char** argv)
{
    Jpg* im1 = new Jpg("im1.jpg");
    Png* im2 = new Png("im2.png");
    im1->load();
    im1->rotate(90);
    im1->load();
    im2->load();
    im2->rotate(90);
    im2->load();
    
    getchar();
    return 0;
}

