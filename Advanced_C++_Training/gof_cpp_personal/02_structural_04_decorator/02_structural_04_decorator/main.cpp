//
//  main.cpp
//  02_structural_04_decorator
//
//  Created by Gabriel Oarga on 16/10/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#include <iostream>

using namespace std;

class Node2D
{
public:
    virtual void draw() = 0;
};

class TextField : public Node2D
{
public:
    TextField(int w, int h) : m_width(w), m_height(h) { }
    
    virtual void draw()
    {
        cout << "TextField: " << m_width << ", " << m_height << '\n';
    }
    
private:
    int m_width{}, m_height{};
};

class Decorator : public Node2D
{
public:
    Decorator(Node2D& target) : m_target(target) {}
    
    virtual void draw() override { m_target.draw(); }
    
private:
    Node2D& m_target;
};

class BorderDecorator : public Decorator
{
public:
    BorderDecorator(Node2D& target) : Decorator(target) {}
    
    void draw() override
    {
        Decorator::draw();
        cout << "\t with border" << endl;
    }
};

class ScrollDecorator : public Decorator
{
public:
    ScrollDecorator(Node2D& target) : Decorator(target) {}
    
    void draw() override
    {
        Decorator::draw();
        cout << "\t with scroll" << endl;
    }
};

int main()
{
    const TextField& text { 10, 10 };
    const Decorator& bdec { text };
    //Node2D& t { BorderDecorator{ ScrollDecorator{ text } } };
    //t.draw();
    
    return 0;
}

