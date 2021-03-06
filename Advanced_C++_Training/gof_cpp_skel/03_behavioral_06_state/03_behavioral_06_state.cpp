#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class State
{
public:
	virtual void controlInjectors() = 0;
	virtual void steer() = 0;
	virtual void brake() = 0;
};

class Car
{
public:
	Car(State& state) : m_state(state) { }
	void controlInjectors() { m_state.controlInjectors(); }
	void steer() { m_state.steer(); }
	void brake() { m_state.brake(); }

private:
	State& m_state;
};


int main()
{
//	Car car{ ComfortState{} };
//	car.brake();
//	car.steer();
//	car.controlInjectors();

	getchar();
	return 0;
}
