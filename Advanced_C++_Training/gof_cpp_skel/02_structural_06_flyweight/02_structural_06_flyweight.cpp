#include "stdafx.h"
#include <iostream>
#include <string>
#include <array>

using namespace std;

class Node
{
private:
	static int count;
	int id;
	int i;
	float f;

public:
	Node() { id = count++; }

	int getI() const { return i; }
	void setI(int val) { i = val; }
	float getF() const { return f; }
	void setF(float val) { f = val; }
	friend ostream& operator<<(ostream& out, const Node& n);
};

int Node::count = 0;

ostream& operator<<(ostream& out, const Node& n)
{
	out << "id: " << n.id << ", i = " << n.i << ", f = " << n.f;
	return out;
}

class FlyNode
{
private:
	static int count;
	int id;
public:
	FlyNode(int id) : id(id) {}

	static int getI(int id);

	//  static void setI(int id, int i) { FlyNodeFactory.i[id] = i; }
	static float getF(int id);
	//	static void setF(int id, float f) { FlyNodeFactory.f[id] = f; }

	friend ostream& operator<<(ostream& out, const FlyNode& n);
	int getId() const { return id; }
};

class FlyNodeFactory
{
public:
	// this can be 1000 or 1000000 (up to you)
	static const int N{ 1000 };

	// the common state can be immutable or not
	// if not, you'll use some pool and have an update logic
	//	static int[] i;
	//	static float[] f;
	static array<FlyNode*, N> nodes;

	static int getI(int id) {
		return 10; // i[id % N];
	}

	static float getF(int id) {
		return 10.23f; // f[id % N];
	}

	static FlyNode& getFlyNode(int id) {
		if (nodes[id % N] == nullptr) {
			nodes[id % N] = new FlyNode(id);
		}
		return *nodes[id % N];
	}
};

array<FlyNode*, FlyNodeFactory::N> FlyNodeFactory::nodes{};

int FlyNode::getI(int id)
{
	return FlyNodeFactory::getI(id);
}

float FlyNode::getF(int id)
{
	return FlyNodeFactory::getF(id);
}

ostream& operator<<(ostream& out, const FlyNode& n)
{
	out << "id: " << n.id << ", i = " << n.getI(n.id) << ", f = " << n.getF(n.id);
	return out;
}


void problem()
{
	const int N{ 50000 };
	Node nodes[N]{};
	for (int i = 0; i < N; i++) {
		nodes[i].setI(10);
		nodes[i].setF(10.3f);
	}
	cout << nodes[100] << endl;
}

void solution()
{
	cout << FlyNodeFactory::getFlyNode(100) << endl;
}

int main()
{
	problem();
	solution();

	getchar();
	return 0;
}
