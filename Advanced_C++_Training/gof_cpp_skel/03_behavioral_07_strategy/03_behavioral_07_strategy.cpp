#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class DrivingMode
{
public:
	virtual void controlInjectors() = 0;
	virtual void steer() = 0;
	virtual void brake() = 0;
};

class SportMode : public DrivingMode
{
public:
	void controlInjectors() { cout << "Sport injection" << endl; }
	void steer() { cout << "Sport steering" << endl; }
	void brake() { cout << "Sport braking" << endl; }
};

class ComfortMode : public DrivingMode
{
public:
	void controlInjectors() { cout << "Comfort injection" << endl; }
	void steer() { cout << "Comfort steering" << endl; }
	void brake() { cout << "Comfort braking" << endl; }
};


class SpeedMode
{
public:
	virtual void LKAS() = 0;
	virtual void ACC() = 0;
};


class Over60 : public SpeedMode
{
public:
	static Over60& getInstance()
	{
		static Over60 m;
		return m;
	}
	void LKAS() { cout << "LKAS activated" << endl; }
	void ACC() { cout << "ACC activated" << endl; }
private:
	Over60() = default;
	Over60& operator=(const Over60& o) = delete;
	Over60(const Over60& o) = delete;
};

class LessThen60 : public SpeedMode
{
public:
	static LessThen60& getInstance()
	{
		static LessThen60 m{};
		return m;
	}

	void LKAS() { cout << "LKAS deactivated" << endl; }
	void ACC() { cout << "ACC deactivated" << endl; }
private:
	LessThen60(const LessThen60& o) = delete;
	LessThen60& operator=(const LessThen60& o) = delete;
	LessThen60() = default;
};

class StrategyCar
{
private:
	// add needed members
	double m_speed;

public:
	StrategyCar(DrivingMode& mode)
		// add init
	{
	}

	void accelerate(double delta) {
		// implement
	}

//	void setSpeedMode(SpeedMode& m) { m_speedMode = m; }

//	void setDrivingMode(DrivingMode& m) { m_drivingMode = m; }

};


int main()
{
//	StrategyCar car{ SportMode{} };
//	car.brake();
//	car.steer();
//	car.controlInjectors();
//	car.LKAS();
//	car.ACC();

//	car.accelerate(100);
//	car.controlInjectors();
//	car.LKAS();
//	car.ACC();
//	car.setDrivingMode(ComfortMode{});
//	car.brake();
//	car.steer();
//	car.controlInjectors();

	getchar();
	return 0;
}
