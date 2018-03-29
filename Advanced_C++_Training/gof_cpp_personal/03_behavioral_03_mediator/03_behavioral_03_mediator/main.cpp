//
//  main.cpp
//  03_behavioral_03_mediator
//
//  Created by Gabriel Oarga on 17/10/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Model
{
public:
    double getValue() const { return m_value; }
    void add(double delta) { m_value += delta; }
private:
    double m_value{};
};


class View
{
public:
    virtual void show(const Model& m) = 0;
};

class Controller
{
public:
    virtual string process(Model& m, double val) = 0;
};


class Dispatcher {  // this is the mediator
public:
    string processRequest(string request, double value)
    {
        // fill in controller action
        cerr << "No suitable controller for the given request: " << request << endl;
        return "error";
    }
    
    void showView(string viewName) {
    }
    
private:
    // add controller
    Model m_model{};
    
};

int main()
{
    
    getchar();
    return 0;
}
