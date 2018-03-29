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
        m_name(name),
        m_x(x),
        m_y(y) {}


    virtual ~Shape() = default;

    virtual double area() const = 0;

    virtual double perimeter() const = 0;

	friend ostream& operator<<(ostream& out, const Shape& c)
	{
		out << c.m_name << ": " << c.m_x << ", " << c.m_y;
		return out;
	}

protected:
    string m_name;
    int m_x;
    int m_y;
};


class Circle : public Shape
{
public:
    Circle() = default;


    Circle(int x, int y, double radius) :
        Shape("circle", x, y),
        m_radius(radius)
    {
    }

	Circle(double radius, int color) :
		Circle(0, 0, radius)
	{
		m_color = color;  // can't be placed inside mem-init
	}

    virtual ~Circle() = default;

    // imagine you type arrea() by default
    // having the override specifier the compiler can give us
    // errors if you pretend to override a method which you don't override
    double area() const override
    {
        return std::acos(-1) * m_radius * m_radius;
    }


    double perimeter() const override
    {
        return 2 * std::acos(-1) * m_radius;
    }


    friend ostream& operator<<(ostream& out, const Circle& c)
    {
        out << c.m_name << ", area = " << c.area() << ", perimeter = " << c.perimeter();
        return out;
    }


private:
    double m_radius;
	int m_color;
};


int main()
{
    Circle c1{100, 100, 20.0};
    Circle c2{120, 120, 40};
    cout << c1 << endl << c2 << endl;

    getchar();
    return 0;
}
