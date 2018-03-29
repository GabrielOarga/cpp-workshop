//
//  main.cpp
//  02_creational_prototype
//
//  Created by Gabriel Oarga on 16/10/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

class Sound {};

class Texture {};

class Node2D
{
public:
    Node2D(int x, int y, string name) :
    m_x(x),
    m_y(y),
    m_name(name)
    {}
    
    Node2D() = default;
    
    virtual Node2D* clone() const
    {
        Node2D* inst = new Node2D{ m_x, m_y, m_name };
        return inst;
    }
    
    virtual void setX(const int x) { m_x = x; }
    virtual void setY(const int y) { m_y = y; }
    virtual void setName(const string name) { m_name = name; }
    
    friend ostream &operator<<(ostream& out, const Node2D& e);
    
protected:
    int m_x{};
    int m_y{};
    string m_name{};
};

class Enemy : public Node2D
{
public:
    Enemy(int x, int y, string name) :
        Node2D(x, y, name)
    {
        loadTexture();
        loadSound();
    }
    virtual Node2D* clone() const override
    {
        Enemy *inst{ new Enemy{ m_x, m_y, m_name } };
        inst->m_texture = m_texture;
        inst->m_sound = m_sound;
        return inst;
    }
    
    void setName(const string name) override
    {
        m_name = name;
    }
private:
    shared_ptr<Sound> m_sound{};
    shared_ptr<Texture> m_texture{};
    
    void loadTexture()
    {
        cout << "Loading texture ... "; fflush(stdout);
        this_thread::sleep_for(500ms);
        cout << "OK" << endl;
        m_texture = make_shared<Texture>();
    }
    
    void loadSound()
    {
        cout << "Loading sound ... "; fflush(stdout);
        this_thread::sleep_for(500ms);
        cout << "OK" << endl;
        m_sound = make_shared<Sound>();
    }
};

ostream &operator<<(ostream& out, const Node2D& e)
{
    out << e.m_name << ": " << e.m_x << ", " << e.m_y;
    return out;
}

int main()
{
    Enemy drEvil{ 10, 10, "Dr Evil" };
    vector<Enemy*> enemies;
    
    for (int i  = 0; i < 10; i++)
    {
        Enemy* en = dynamic_cast<Enemy*>(drEvil.clone());
        if (en != nullptr)
        {
            en->setName("Enemy_" + to_string(i));
            en->setX(10 + i);
            en->setX(10 + i * 2);
            enemies.push_back(en);
        }
    }
    
    for (auto e : enemies)
        cout << *e << endl;
    
    for (auto e : enemies)
        delete e;
    
    
    return 0;
}

