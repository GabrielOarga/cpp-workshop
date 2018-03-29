#include <iostream>
#include <map>

using namespace std;


class Test
{
public:
    // required by a_map[20] = Test(10, "cucu");
    Test() :
        id(),
        name()
    {
    }


    Test(int id, string name) :
        id(id),
        name(name)
    {
    }


    // called 3 times per map insert!
    Test(const Test& other) :
        id(other.id),
        name(other.name)
    {
        cout << "Copy constructor" << endl;
    }


    void print() const
    {
        cout << id << ": " << name.c_str();
    }


private:
    int id;
    string name;
};


int main()
{
    map<int, Test> tests;
    Test t(10, "gigi");
    tests.insert(make_pair(10, Test(10, "Gigi")));
    tests.insert(make_pair(20, Test(20, "Jiji")));
    tests[30] = Test(30, "Joe"); // this line requires a no-arg constructor

    for (auto it = tests.begin(); it != tests.end(); ++it) {
        cout << it->first << " = ";
        it->second.print();
        cout << endl;
    }

    getchar();
    return 0;
}
