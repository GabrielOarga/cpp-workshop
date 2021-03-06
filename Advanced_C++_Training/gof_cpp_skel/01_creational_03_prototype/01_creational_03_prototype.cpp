#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

class Sound {};

class Texture {};

class Node2D;

class Node2D
{
public:
	Node2D(int x, int y, string name) :
		m_x(x),
		m_y(y),
		m_name(name)
	{
		// Empty
	}
	
	Node2D() = default;

	virtual Node2D* clone() const
	{
		Node2D* inst{ new Node2D{} };
		inst->m_x = m_x;
		inst->m_y = m_y;
		inst->m_name = m_name;
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
		// the constructor is expensive
		loadTexture();
		loadSound();
	}

	Enemy() {}

	virtual Node2D* clone() const override
	{
		Enemy* inst{ new Enemy{} };
		inst->m_x = m_x;
		inst->m_y = m_y;
		inst->m_name = m_name;
		inst->m_texture = m_texture;
		inst->m_sound = m_sound;
		return inst;
	}

private:
	shared_ptr<Sound> m_sound{};
	shared_ptr<Texture> m_texture{};

	void loadTexture()
	{
		cout << "Loading texture...";
		fflush(stdout);
		this_thread::sleep_for(500ms);
		cout << "OK" << endl;
		m_texture = make_shared<Texture>();
	}

	void loadSound()
	{
		cout << "Loading sound...";
		fflush(stdout);
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
	Enemy drEvil{ 10, 10, "drEvil" };
	vector<Enemy*> enemies;
	for (int i = 0; i < 100; i++) {
		Enemy* en = dynamic_cast<Enemy*>(drEvil.clone());
		if (en != nullptr) {
			en->setName("Enemy_" + to_string(i));
			en->setX(i * 2);
			en->setY(100);
			enemies.emplace_back(en);
		}
	}

	for (auto e : enemies)
		cout << *e << endl;

	// be nice and clean up
	for (Enemy* e : enemies)
		delete e;
	enemies.clear();

	getchar();
	return 0;
}
