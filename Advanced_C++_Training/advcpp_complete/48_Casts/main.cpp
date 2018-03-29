#include <iostream>
#include <string>
#include <atomic>

using namespace std;

/**
 * In the following projects we will talk about perfect forwarding,
 * but first we'll have a look at casts in C++
 */

class Animal
{
public:
    Animal() : Animal("") {}
    explicit Animal(string name) : name(name) {}
    virtual ~Animal() {}
    virtual void speak() const {}  // we don't make it pure virtual
protected:
    string name;
};


class Dog : public Animal
{
public:
    Dog() : Dog("Cutu") {}
    explicit Dog(string name) :
        Animal(name) {}
    void bark() const { cout << name << ": Ham!" << endl; }
};


class Cat : public Animal
{
public:
    Cat(string name, string surname, double age) :
        Animal(name),
        m_surname(surname),
        m_age(age) {}
    virtual void relax() const { 
        cout << name << ", " << m_surname << ", " << m_age << ": relaxing..." << endl;
    }
private:
    string m_surname;  // this is an aristocat :)
    double m_age{};
};


struct Another
{
    double a{ 7.1 };
    double b{ 1.2 };
    double c{ 10.101 };
};


void test_static_cast()
{
    cout << "test static_cast(begin)" << endl;
    // C++ inherits C-style casts from C:
    auto float_value{ 7.11f };
    cout << (int)float_value << endl;
    // they are legal, but the compiler or static analysis tools will
    // give us warnings when encountering C-like casts

    // C++ gives us also the following syntax:
    cout << int(float_value) << endl;  // looks like an int() constructor

    // C++ gives us a more powerful construct for casting:
    cout << static_cast<int>(float_value) << endl;  // you can use static_cast<target_type> in most situations

    // static_cast is a compile-time cast.
    // Why is it more powerful? Because it can make checks like this:
    // int* pi1 = static_cast<int*>(&float_value);   // compilation error
    int* pi2 = (int*)(&float_value);  // compiler doesn't complain => static_cast is safer!!!!
    cout << "Converted ptr to " << float_value << " into int pointer => " << *pi2 << endl;

    Animal animal{ "Animal" };
    Dog nero{ "Nero" };

    Animal *p_animal{ &nero };  // works
    // If you uncomment => compiler error:
    // Dog *p_dog = &animal;  // doesn't work: we need to cast

    // this is UNSAFE: we see that the address is the same as for the parent object:
    Dog *p_dog{ static_cast<Dog*>(&animal) };
    cout << "Animal address: " << &animal << ", Dog address: " << p_dog << endl;

    // normally you want this:
    Animal *pa = &nero;
    Dog *dog = static_cast<Dog*>(pa);   // now this is safe, because we know pa is pointing to a Dog
    // this kind of casts is not suitable for this kind of cast => it is a compile-time cast

    // you might encounter void* to non-void* casts:
    // no need to reinterpret_cast! Just do:
    void* p_void = static_cast<void*>(&float_value);  // that's fine: upcast
    void* p_void2 = static_cast<void*>(dog);
    int* p_int1 = static_cast<int*>(p_void2);
    cout << "casting a dog ptr (masked as void*) to an int* ptr and dereference: " <<
        *p_int1 << endl;  // sure, in this case I point out that you must be sure of the real type!

    // int* p_int2 = static_cast<int*>(dog);  // it doesn't work directly!!! This is why we masked it as void* :)
    // the above example shows the power of static_cast!

    int* p_int3 = (int*)dog;  // this works, NOT OK! Use static_cast instead of C-casts!

    cout << "test static_cast(end)" << endl << endl;
}


void test_dynamic_cast()
{
    // dynamic cast is specially designed for related types
    // it will give us the desired pointer, or nullptr in case
    // the cast cannot be safely performed:
    cout << "test dynamic_cast(begin)" << endl;
    Dog nero("Nero");
    Animal *p_animal = &nero;
    Dog *p_dog{ dynamic_cast<Dog*>(p_animal) };
    if (p_dog == nullptr) {
        cout << "Cannot cast animal into dog" << endl;
    } else {
        p_dog->bark();
    }

    Cat *p_cat = dynamic_cast<Cat*>(p_animal);
    if (p_cat == nullptr) {
        cout << "Cannot cast animal into cat" << endl;
    } else {
        p_cat->relax();
    }
    cout << "test dynamic_cast(end)" << endl << endl;
}


void test_reinterpret_cast()
{
    // this should be rarely (if at all) performed. It's potentially unsafe
    cout << "test reinterpret_cast(begin)" << endl;
    Dog nero{"Nero"};
    auto p_dog{ &nero };
    cout << reinterpret_cast<Another*>(p_dog)->c << endl;

    // reinterpret_cast for primitive types
    auto f{123.63412e-10f};
    auto fp{ &f };
    auto ip{ reinterpret_cast<int*>(fp) };
    cout << *ip << endl;
    auto rfp{ reinterpret_cast<float*>(ip) };
    cout << *rfp << endl;

    // reinterpret_cast for pointers to objects
    Cat* p_cat{ reinterpret_cast<Cat*>(p_dog) };
    p_cat->relax();  // this will CRASH the program!

    // relax() is correctly solved from vtable (class-related, not object-related)
    // m_name is the same as for Dog, because it's inherited from Animal => relative address matches
    // but relax uses some Cat members => program might crash when trying
    // to understand some bytes as string bytes for instance
    // NOTE: if relax() is not virtual => no crash, but no output for Cat members

    cout << "test reinterpret_cast(end)" << endl << endl;
}


int main()
{
    test_static_cast();
    test_dynamic_cast();
    test_reinterpret_cast();

    getchar();
    return 0;
}
