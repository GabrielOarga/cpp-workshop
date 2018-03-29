//
//  main.cpp
//  03_behavioral_06_state
//
//  Created by Gabriel Oarga on 17/10/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

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

class SportState : public State
{
public:
    void controlInjectors() override
    {
        cout << "Sport injection" << endl;
    }
    
    void steer() override
    {
        cout << "Sport steering" << endl;
    }
    
    void brake() override
    {
        cout << "Sport braking" << endl;
    }
};

class ComfortState : public State
{
public:
    void controlInjectors() override
    {
        cout << "Comfort injection" << endl;
    }
    
    void steer() override
    {
        cout << "Comfort steering" << endl;
    }
    
    void brake() override
    {
        cout << "Comfort braking" << endl;
    }
};

class Car
{
public:
    void setState(State *state) { m_state = state; }
    void controlInjectors() { m_state->controlInjectors(); }
    void steer() { m_state->steer(); }
    void brake() { m_state->brake(); }
    
private:
    State* m_state;
};


int main()
{
    ComfortState *cstate = new ComfortState();
    SportState *sstate = new SportState();
    
    Car *car = new Car();
    car->setState(cstate);
    car->brake();
    car->setState(sstate);
    car->steer();
    car->setState(cstate);
    car->controlInjectors();

    return 0;
}
