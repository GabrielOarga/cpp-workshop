#include <iostream>
#include <stack>
#include <queue>
#include <array>
using namespace std;


class Person
{
public:
    Person() :
        name(),
        age()
    {
    }


    Person(string name, int age) :
        name(name),
        age(age)
    {
    }


    void print() const
    {
        cout << name.c_str() << ", " << age << endl;
    }


    virtual ~Person()
    {
        cout << "Object " << name.c_str() << " destroyed" << endl;
    }


private:
    string name;
    int age;
};


int main()
{
    stack<Person> persons; // cannot be initialized with initializer list
    // each added object is immediatelly destroyed after insertion!
    // and a copy of the object is added to the stack (using the copy constructor)
    persons.push(Person("Gheorghe", 40));
    persons.push(Person("Vasile", 30));
    persons.push(Person("Gigi", 50));

    // this is invalid code!!!!
    // Object is destroyed before being used
    //    Person& p1 = persons.top();
    //    persons.pop();
    //    p1.print();

    Person& p1 = persons.top();
    p1.print();
    persons.pop();

    Person p2 = persons.top(); // p2 is a copy of stack object
    persons.pop(); // => I can remove object from stack anytime
    p2.print();

    // each added object is immediatelly destroyed after insertion!
    // and a copy of the object is added to the stack (using the copy constructor)
    queue<Person> queuedPersons({Person("Ana", 40), Person("Ion", 40), Person("Vasile", 40)});
    queuedPersons.push(Person("Gheo", 40));
    queuedPersons.push(Person("Vasi", 30));
    queuedPersons.push(Person("Gigi", 50));

    // this is invalid code!!!!
    // Object is destroyed before being used
    //    Person& p3 = queuedPersons.top();
    //    queuedPersons.pop();
    //    p3.print();

    Person& p3 = queuedPersons.front();
    p3.print();
    queuedPersons.pop();

    Person p4 = queuedPersons.front(); // p2 is a copy of stack object
    queuedPersons.pop(); // => I can remove object from stack anytime
    p4.print();

    deque<Person> deqPersons;
    deqPersons.push_back(Person("Paul", 34));
    deqPersons.push_front(Person("Ioana", 31));
    deqPersons.push_back(Person("Ioan", 50));

    // Ioana will be the first (begin()), and Ioan will be the last (end())
    for (auto it = deqPersons.begin(); it != deqPersons.end(); ++it) {
        it->print();
    }

    deque<int> mydeque;

    mydeque.push_back(10);

    while (mydeque.back() != 0)
        mydeque.push_back(mydeque.back() - 1);

    cout << "mydeque contains:";

    for (auto it = mydeque.begin(); it != mydeque.end(); ++it)
        cout << ' ' << *it;

    cout << '\n';

    getchar();
    return 0;
}
