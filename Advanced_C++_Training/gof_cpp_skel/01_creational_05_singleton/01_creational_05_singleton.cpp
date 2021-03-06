#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

class Widget
{
public:
	static Widget& instance()
	{
		static Widget w{"singleWidget", 10, 20};
		return w;
	}

	friend ostream &operator<<(ostream &out, const Widget &w);

	Widget operator=(Widget& o) = delete;
	Widget(const Widget& o) = delete;
	virtual ~Widget() { cout << ":dtor:" << endl; }

private:
	string m_name{};
	int m_x, m_y;

	Widget(string name, int x, int y) :
		m_name(name),
		m_x(x),
		m_y(y)
	{
		cout << ":ctor:" << endl;
	}
};


ostream &operator<<(ostream &out, const Widget &w)
{
	out << w.m_name << ", x=" << w.m_x << ", y=" << w.m_y;
	return out;
}


class WidgetDoubleChecked
{
public:
	static WidgetDoubleChecked* instance()
	{
		WidgetDoubleChecked* inst = m_inst;
		if (inst == nullptr) {
			unique_lock<mutex> lock{ m_mutex };
			cout << "me too" << endl;
			inst = m_inst;
			if (inst == nullptr) {
				cout << "ONLY ME" << endl;
				m_inst = new WidgetDoubleChecked{ "singleWidget", 10, 20 };
				inst = m_inst;
			}
		}
		return inst;
	}

	friend ostream &operator<<(ostream &out, const WidgetDoubleChecked &w);

	WidgetDoubleChecked operator=(WidgetDoubleChecked& o) = delete;
	WidgetDoubleChecked(const WidgetDoubleChecked& o) = delete;
	virtual ~WidgetDoubleChecked() { cout << ":dtor:" << endl; }

private:
	static WidgetDoubleChecked* m_inst; // shared_ptr also solves this
	static mutex m_mutex;
	string m_name{};
	int m_x, m_y;

	WidgetDoubleChecked(string name, int x, int y) :
		m_name(name),
		m_x(x),
		m_y(y)
	{
		cout << ":ctor:" << endl;
	}
};

WidgetDoubleChecked* WidgetDoubleChecked::m_inst{ nullptr };
mutex WidgetDoubleChecked::m_mutex{};

ostream &operator<<(ostream &out, const WidgetDoubleChecked &w)
{
	out << w.m_name << ", x=" << w.m_x << ", y=" << w.m_y;
	return out;
}


int main()
{
	vector<thread> workers{};
	for (int i = 0; i < 10; i++) {
		// you'll see output mixed from multiple threads. That's fine for our case
		workers.emplace_back(thread{ []() { cout << *WidgetDoubleChecked::instance() << endl; } });
	}

	for (auto& w : workers)
		if (w.joinable()) w.join();

	getchar();
	return 0;
}
