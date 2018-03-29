#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

void test_curly_braces_CPP98()
{
    // in C++98 braces {} could be used to initialize variables
    // in fairly limited cases. We expose them below:

    // 1. Arrays
    int numbers[] = { 1, 2, 3 };
    cout << numbers[0] << endl;

    // 2. Classes with public members
    class Person
    {
    public:
        string name;
        int age;
    } a_person = { "Dumitru", 27 };
    Person ion = { "Ion", 20 }, vasile = { "Vasile", 40 };
    cout << ion.name << endl;

    // 3. structs (which are more natural than classes with all members public)
    struct StrPerson
    {
        string name;
        int age;
    } the_person = { "Superman", 45 };  // we can also declare a variable right after struct definition
    StrPerson p1 = { "Liviu", 30 }, p2 = { "Bogdan", 24 };
    cout << p1.name << endl;

    // 4. anonymous structs
    struct  // anonimous structure
    {
        string name;
        int age;
    } paul = { "Paul", 20 }, maria = { "Maria", 44 };
    cout << paul.name << endl;

}


void non_uniform_initialization()
{
    // See Item 7 from Effective Modern C++
    // 3 different ways of initializing in C++:
    auto one(0);
    auto two = 0;
    auto three{ 0 };
    int four = { 0 };  // three and four are equivalent and possible in almost all cases

    // the preffered way of initialization is braces-only initialization: {}
    // this has some advantages:
    // int x{ 999999999999999999 };      // this doesn't compile: long-to-int narrowing conversion
    // int xx = 999999999999999999;      // this compiles: some compilers might give warnings

//    int x0{ 5.5f };       // error: narrowing conversion required
    double d{ 7 };          // this is ok: compiler doesn't need to narrow 7 in order to fit a double
//    int x2{ d };            // error: conversion from double to int requires narrowing
//    char c2{ 512 };         // error: conversion from int to char requires narrowing
//    int x3{ 7.0 };          // Attention: double / float to int is **always** considered narrowing (even for 7.0)!

    // Now you can choose a single, uniform, way of initializing
}


void test_uniform_initialization()
{
    // c++11 generalizes the use of curly braces for initialization
    int number{ 10 };    // no need for equal sign;
    auto another_number{ 5 };
    // we can use this for (almost) everything:
    string greet{ "Hello" };

    int numbers[]{ 1, 2, 3, 4, 5 };  // similar to 98, but without the equal sign
    int *pInts = new int[4]{ 1, 2, 3, 4 };  // we need to specify the size of the array
    cout << pInts[1] << endl;
    delete[] pInts;

    int *pNumber{ &number };
    cout << *pNumber << endl;

    int *anotherPointer{};   // initializes the pointer to nullptr
    int *another{ nullptr }; // same effect as above
    cout << anotherPointer << endl;
    cout << another << endl;

    int other_numbers[5]{};  // initializes the array with zero values

    int a1[2][2]{ { 1, 2 }, { 2, 3 } };
    int a2[2][2]{ 1, 2, 2, 3 };  // equivalent to the one above

    struct
    {
        string name;
        int age;
    } razvan{ "Razvan", 26 };
    cout << razvan.name << endl;

    vector<string> names{ "Ana", "Maria", "Liviu", "Bogdan" };
    for (auto name : names) cout << name << " ";
    cout << endl;

    map<string, int> test{
        { "ion", 30 },
        { "vasile", 40 },
        { "maria", 100 }
    };

	// queue and stack don't have an initializer list constructor: note the "(" and ")":
	queue<int> q({1, 2, 3, 4});
}


int main()
{
    test_curly_braces_CPP98();
    test_uniform_initialization();

    getchar();
    return 0;
}
