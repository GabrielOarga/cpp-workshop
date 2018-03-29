#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;


// sometimes it makes sense to derive of your related classes from
// the same type, but at the same type it makes no sense to give
// implementation to methods from the base class

class Animal
{
public:
    // careful: if you define a no-arg constructor, the compiler won't generate
    // a no-arg constructor for you
    // BUT: the first call from any constructor is a call to super() => super() doesn't exist
    // if you declare only an non-no-arg constructor => explicitly call super(name) from your
    // derived classes
    Animal(/*string cucu*/)
    {
        cout << "Animal constructor" << endl;
    }

    virtual void speak() = 0;

    virtual void run() = 0;

    virtual ~Animal()
    {
    }
};


// if Dog implements all methods from Animal => Dog is not abstract
// otherwise Dog is abstract
class Dog : public Animal
{
public:
    explicit Dog(const string& name) :
        name(name)
    {
        cout << "Dog constructor, " << flush;  // remember: super() is called automatically
    }


    virtual void speak() override
    {
        cout << name << " says Ham!" << endl;
    }


    virtual ~Dog()
    {
        // Empty
    }


    virtual string getName() const { return name; }
    void setName(const string& name) { this->name = name; }

private:
    string name;
};


class Rottweiler : public Dog
{
public:
    Rottweiler(const string& name) :
        Dog(name)
    {
        cout << "Rottweiler constructor, " << flush;
    }

    virtual ~Rottweiler()
    {
        // Empty
    }

    virtual void run() override
    {
        cout << getName() << " is running" << endl;
    }
};


int main()
{
    // when we create an array of objects,
    // the default constructor for all the objects gets called
    // and we cannot instantiate an abstract class
    array<Rottweiler, 3> rottweilers{
        Rottweiler("Nero"),
        "Leika", // this is possible, because we didn't make the constructor explicit =>
        "Spike" // constructor(string) is also a conversion constructor, and it's called
    };

    for (auto rottweiler : rottweilers)
        rottweiler.run();

    // instead, we can create an array of pointers to the base class
    // => work in a polymorphic manner
    array<Animal*, 3> animals{&rottweilers[0], &rottweilers[1], &rottweilers[2]};
    for (auto animal : animals)
        animal->speak();

    getchar();
    return 0;
}
