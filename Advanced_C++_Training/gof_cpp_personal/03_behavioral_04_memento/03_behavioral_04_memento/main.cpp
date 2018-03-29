//
//  main.cpp
//  03_behavioral_04_memento
//
//  Created by Gabriel Oarga on 17/10/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Memento
{
public:
    Memento(vector<string> state) : m_state(state) {}
    
    vector<string>& getState() { return m_state; }
    
    void setState(vector<string>& state)
    {
        m_state.clear();
        m_state.insert(m_state.begin(), state.begin(), state.end());
    }
private:
    vector<string> m_state{};
};


class Notepad  // Originator
{
private:
    vector<string> m_lines{};
public:
    Memento exportState()  // createMemento
    {
        return Memento(m_lines);
    }
    
    void restoreState(Memento m)  // setMemento
    {
        m_lines.clear();
        m_lines.insert(m_lines.begin(), m.getState().begin(), m.getState().end());
    }
    
    Notepad& addLine(string line)
    {
        m_lines.push_back(line);
        return *this;
    }
    
    friend ostream& operator<<(ostream& out, const Notepad& n);
};


ostream& operator<<(ostream& out, const Notepad& n)
{
    stringstream ss;
    for (auto line : n.m_lines)
        ss << line << "\n";
    out << ss.str();
    return out;
}


class UndoManager  // Caretaker
{
private:
    vector<Memento> history{};
    vector<string> ids{};
public:
    // addMemento
    void addState(string id, Memento m)
    {
        history.push_back(m);
        ids.push_back(id);
    }
    
    // getMemento
    Memento getState(string id)
    {
        int idx = -1;
        for (int i = 0; i < ids.size(); i++) {
            if (ids[i] == id)
                idx = i;
        }
        if (idx != -1) {
            return history[idx];
        }
        return Memento(vector<string>{});  // empty memento TODO change this
    }
};

int main()
{
    Notepad myDoc{};
    UndoManager mgr{};
    myDoc.addLine("cucu").addLine("rigu");
    cout << myDoc << endl;
    mgr.addState("1", myDoc.exportState());  // createMemento
    
    myDoc.addLine("boieri").addLine("mari");
    cout << myDoc << endl;
    mgr.addState("2", myDoc.exportState());  // createMemento
    
    cout << "UNDO:" << endl;
    myDoc.restoreState(mgr.getState("1"));
    cout << myDoc << endl;
    
    return 0;
}

