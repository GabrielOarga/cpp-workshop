#include "stdafx.h"
#include <iostream>
#include <string>
#include <thread>

using namespace std;

class ActionEvent {};
class ButtonPressed : public ActionEvent {};

class ActionListener  // Not needed in modern C++
{
public:
	virtual void actionPerformed(const ActionEvent& e) = 0;
};

class Button
{
public:
	virtual void addActionListener(void(*listener)(const ActionEvent& e))
	{
		m_listener = listener;
	}


private:
	bool m_pressed{};
	void(*m_listener)(const ActionEvent& e);
	
	// uncomment if you work in old C++
	//ActionListener& m_listener{};
};

int main()
{
	Button b{};
	cout << "Thread %d: register action listener..." << this_thread::get_id() << endl;

	b.addActionListener([](const ActionEvent& e) {
		cout << "Button pressed from thread " << this_thread::get_id() << endl;
	});

	cout << "OK. Resume work..." << endl;

	// this thread doesn't stop its work; actionPerformed() will be called asynchronously
	this_thread::sleep_for(100ms);

	// at some point in time and from another thread, an action occurs:

	this_thread::sleep_for(100ms);
	cout << "Thread " << this_thread::get_id() << ": still working..." << endl;
	t.join();

	getchar();
	return 0;
}
