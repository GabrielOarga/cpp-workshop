//
//  main.cpp
//  03_behavioral_07_strategy
//
//  Created by Gabriel Oarga on 17/10/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

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
    SpeedMode& m_speedMode;
    DrivingMode& m_drivingMode;
    
public:
    StrategyCar() : m_speedMode(LessThen60::getInstance())
    {
    }
    
    void accelerate(double delta)
    {
        m_speed += delta;
        if (m_speed >= 60)
        {
            m_speedMode = Over60::getInstance();
        }
        else
        {
            m_speedMode = LessThen60::getInstance();
        }
    }
    
    void setSpeedMode(SpeedMode& m) { m_speedMode = m; }
    
    void setDrivingMode(DrivingMode& m) { m_drivingMode = m; }
    
    void constrolInjectors() { m_drivingMode.controlInjectors() }
    void steer() { m_drivingMode.steer(); }
    void brake() { m_drivingMode.brake(); }
    void LKAS() { m_speedMode.LKAS(); }
    void ACC() { m_speedMode.ACC(); }
    
};


int main()
{
    StrategyCar car {};
    
    DrivingMode mode;
    
    car.setDrivingMode(mode)
    car.brake();
    car.steer();
    car.controlInjectors();
    car.LKAS();
    car.ACC();
    
    car.accelerate(100);
    car.controlInjectors();
    car.LKAS();
    car.ACC();
    car.setDrivingMode(ComfortMode{});
    car.brake();
    car.steer();
    car.controlInjectors();
    
    return 0;
}

