#include <iostream>
#include <map>

using namespace std;


class Test
{
public:
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


    Test(const Test& other) :
        id(other.id),
        name(other.name)
    {
        // this is called 3 times per map insert!
        // cout << "Copy constructor called" << endl;
    }


    void print() const
    {
        cout << id << ": " << name.c_str();
    }


    bool operator<(const Test& other) const
    {
        if (name == other.name) {
            return id < other.id;
        }
        return name < other.name;
    }


    bool operator==(const Test& other) const
    {
        return (name == other.name) && (id == other.id);
    }


    // only operator< is mandatory; the other are "nice to have" (consistency)
    bool operator>(const Test& other) const
    {
        return !operator<(other) && !operator==(other);
    }


private:
    int id;
    string name;
};


int main()
{
    map<Test, int> tests{
        {Test(10, "Gigi"), 10},
        {Test(20, "Cucu"), 10},
        {Test(31, "Ioana"), 31},
        {Test(7, "Lorena"), 7}
    };

    tests.insert(make_pair(Test(10, "Gigi"), 10));
    tests.insert(make_pair(Test(20, "Cucu"), 20));
    tests[Test(31, "Ioana")] = 31;
    tests[Test(555, "AAA")] = 555;

    for (auto el : tests) {
        el.first.print();
        cout << " = " << el.second << endl;
    }

    getchar();
    return 0;
}
