// override and default implementations

#include <iostream>
#include <string>
#include <cmath>

using namespace std;


class Shape
{
public:
    explicit Shape(string name, int x, int y) :
        m_name(name),
        m_x(x),
        m_y(y) {}

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual double perimeter() = 0;
    virtual ~Shape() {}

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



int main()
{

    getchar();
    return 0;
}
