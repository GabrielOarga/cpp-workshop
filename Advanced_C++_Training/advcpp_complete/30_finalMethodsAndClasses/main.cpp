// override and default implementations

#include <iostream>
#include <string>
#include <cmath>

using namespace std;


class Shape
{
public:
    Shape() = default;


    Shape(string name, int x, int y) :
        name(name),
        x(x),
        y(y)
    {
    }


    virtual ~Shape() = default;

    virtual double area() const = 0;

    virtual double perimeter() const = 0;

protected:
    string name;
    int x;
    int y;
};


class Circle final : public Shape
{
public:
    Circle() = default;


    Circle(int x, int y, double radius) :
        Shape("circle", x, y),
        radius(radius)
    {
    }


    virtual ~Circle() = default;

    // imagine you type arrea() by default
    // having the override specifier the compiler can give us
    // errors if you pretend to override a method which you don't override
    virtual double area() const override final
    {
        return std::acos(-1) * radius * radius;
    }


    virtual double perimeter() const override final
    {
        return 2 * std::acos(-1) * radius;
    }


    friend ostream& operator<<(ostream& out, const Circle& c)
    {
        out << c.name << ", area = " << c.area() << ", perimeter = " << c.perimeter();
        return out;
    }


protected:
    double radius;
};


// Not possible if Circle is final
//class ReinventedCircle : public Circle
//{
//};


int main()
{
    Circle c1{ 100, 100, 20.0 };
    Circle c2{ 120, 120, 40 };
    // ReinventedCircle rc{120, 100, 40.0};

    cout << c1 << endl << c2 << endl;

    getchar();
    return 0;
}
