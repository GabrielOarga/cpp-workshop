#include <iostream>
#include <vector>

using namespace std;


// Polymorphism in C++ works IF we declare the called method as virtual
// in the parent class AND
// if we use pointers or references instead of objects
// because object creation means calling the parent copy constructor
// parent copy constructor cannot initialize child members!
// this is called object slicing


class Parent
{
public:
    Parent(const Parent& other) { cout << "Parent copy constructor... "; }


    Parent()
    {
    }


    virtual void print() { cout << endl << "Parent" << endl; }


    virtual ~Parent()
    {
    }
};


class Child : public Parent
{
public:
    void print() override { cout << endl << "Child" << endl; }
};


int main()
{
    // if you have a reference (pointer) to a parent class
    // you can assign any sub-type to it.
    Child child;
    Parent& parent = child;
    parent.print();
    cout << endl << endl;

    // the following won't work because p2 is sliced
    // copy constructor is called (the default one)

    // the copy constructor only knows about the Parent class
    // it has no idea about the child class (actual type)
    // => it has insufficient information about the actual type!
    // <=> copy constructor will "slice away" part of the Child object
    // this is actually an up-cast
    Parent p2 = Child();
    p2.print();
    cout << endl << endl;

    // the same thing applies to vectors:
    cout << "Object slicing when using vectors:" << endl;
    vector<Parent> parents;
    // every push_back means **copying** the original object into the vector!
    parents.push_back(Child());
    parents.push_back(Child());
    for (auto it = parents.begin(); it != parents.end(); ++it) {
        it->print();
    }

    // in order to solve this we need to use vector of pointers to Parent:
    cout << "Using vector of pointers:" << endl;
    vector<Parent*> parents2;
    parents2.push_back(new Child());
    parents2.push_back(new Child());
    parents2.push_back(new Parent());
    for (auto i = 0u; i < parents2.size(); i++) {
        parents2[i]->print();
    }

    // Conclusion:
    // polymorphism works with references or pointers to base class!
    // and only if we have the base class method declared as ***virtual***
    getchar();
    return 0;
}
