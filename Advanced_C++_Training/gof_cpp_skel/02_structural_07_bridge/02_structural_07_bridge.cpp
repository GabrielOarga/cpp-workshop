#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <functional>

using namespace std;

class Platform;

class Image
{
public:
	static Platform& m_platform;

	Image(string name) : m_name(name) {}
	
	static void setPatform(Platform& p);
	virtual void load() = 0;
	virtual void rotate(int angle) = 0;

protected:
	string m_name;
};

class Platform
{
public:
	virtual void open(string name) = 0;
	virtual void render() = 0;
	virtual void rotate(int angle) = 0;
};

class LibOpenGL
{
public:
	void operation1() { cout << "OGL.op1()" << endl; }
	void operation2() { cout << "OGL.op2()" << endl; }
	void operation3() { cout << "OGL.op3()" << endl; }
	void operation4() { cout << "OGL.op4()" << endl; }
};

class Linux : public Platform
{
private:
	LibOpenGL lib{};

public:
	virtual void open(string name) override
	{
		cout << "Linux.open(" << name << ")" << endl;
	}

	virtual void render() override
	{
		cout << "Linux.render()" << endl;
		lib.operation1();
		lib.operation2();
	}

	void rotate(int angle) override
	{
		cout << "Linux.rotate()" << endl;
		lib.operation1();
		lib.operation2();
		lib.operation4();
	}
};

class LibDirectX
{
public:
	void operation1() { cout << "DX.op1()" << endl; }
	void operation2() { cout << "DX.op2()" << endl; }
	void operation3() { cout << "DX.op3()" << endl; }
};

class Windows : public Platform
{
private:
	LibDirectX lib{};
public:
	virtual void open(string name) override
	{
		cout << "Windows.open(" + name + ")" << endl;
	}

	virtual void render() override
	{
		cout << "Windows.render()" << endl;
		lib.operation1();
	}

	void rotate(int angle) override
	{
		cout << "Windows.rotate()" << endl;
		lib.operation2();
		lib.operation3();
	}
};

void Image::setPatform(Platform& p)
{
	Image::m_platform = p;
}

class Png : Image 
{
public:
	Png(string name) : Image(name) {}

	virtual void load() override
	{
		m_platform.open(m_name);
		cout << "png.load()" << endl;
		m_platform.render();
	}

	virtual void rotate(int angle) override
	{
		cout << "pre: png.rotate()" << endl;
		m_platform.rotate(angle);
		cout << "post: png.rotate()" << endl;
	}
};

class Jpg : Image {
public:	
	Jpg(string name) : Image(name) {}

	virtual void load() override
	{
		m_platform.open(m_name);
		cout << "jpg: some specific opetration" << endl;
		cout << "jpg.load()" << endl;
		m_platform.render();
	}

	virtual void rotate(int angle) override
	{
		cout << "pre: jpg.rotate()" << endl;
		m_platform.rotate(angle);
		cout << "post: jpg.rotate()" << endl;
	}
};

Platform& Image::m_platform{ Windows{} };

int main(int argc, char** argv)
{
	Jpg& im1{ Jpg("im1.jpg") };
	Png& im2{ Png("im2.png") };
	im1.load();
	im1.rotate(90);
	im1.load();
	im2.load();
	im2.rotate(90);
	im2.load();

	getchar();
	return 0;
}
