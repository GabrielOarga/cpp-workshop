// override and default implementations

#include <iostream>
#include <string>
#include <cmath>

using namespace std;


class Shape
{
public:
    Shape() {}
    
    explicit Shape(string name, int x, int y) :
    m_name(name),
    m_x(x),
    m_y(y) {}
    
    virtual ~Shape() {}
    
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    
    friend ostream& operator<<(ostream& out, const Shape& c)
    {
        out << c.m_name << ": " << c.m_x << ", " << c.m_y;
        return out;
    }
    
protected:
    string m_name;
    int m_x{};
    int m_y{};
};

class Circle final : public Shape //Circle is Final, can no longer inherit from it
{
public:
    //    Circle() {}
    Circle() : Shape() {}
    
    Circle(int x, int y, double radius)
    : Shape("Circle", x, y) // This must be first thing in init syntax
    , m_radius(radius)
    {
        
    }
    
    Circle(double radius, int color)
    : Circle(0, 0, radius)
    //, m_color(color) Cannot do this, if other constructor is called, it will be only member initialised in the syntax
    {
        m_color = color; // Do this instead
    }
    
    double area() const override final
    {
        return std::acos(-1) * m_radius * m_radius;
    }
    
    double perimeter() const override final
    {
        return 2 * std::acos(-1) * m_radius;
    }
    
private:
    double m_radius{}; //Default value declaration
    int m_color{};
};

/*
class CircleReinvented : public Circle
{
public:
    CircleReinvented() {}
    
    double area() const override
    {
        return 0.0;
    }
    
private:
    
};
*/

int main()
{
    getchar();
    return 0;
}
