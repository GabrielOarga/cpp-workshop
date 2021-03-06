#include "stdafx.h"
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
	Decorator(Node2D& w) : m_target(w) { }

	virtual void draw() override { m_target.draw(); }
private:
	Node2D& m_target;
};

class BorderDecorator : public Decorator
{
public:
	BorderDecorator(Node2D &w) : Decorator(w) {}

	void draw()
	{
		// base action + decoration
		Decorator::draw();
		cout << "\twith Border" << endl;
	}
};

class ScrollDecorator : public Decorator
{
public:
	ScrollDecorator(Node2D& w) : Decorator(w) {}

	void draw()
	{
		Decorator::draw();
		cout << "\twith Scrollbar" << '\n';
	}
};

int main()
{
	Node2D& aNode2D{ BorderDecorator{ BorderDecorator{ ScrollDecorator{ TextField(80, 24)}}}};
	aNode2D.draw();

	getchar();
	return 0;
}
