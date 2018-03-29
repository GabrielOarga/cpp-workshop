#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void test_braces_CPP98()
{
    // in C++98 curly braces could be used to initialize variables
    // in fairly limited cases. We expose them below:

    // 1. Arrays
    int numbers[] = { 1, 2, 3 };
    cout << numbers[0] << endl;

    // 2. Classes with public members
    class Person
    {
    public:
        std::string name;
        int age;
    } mary = { "Mary", 27 };
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


void test_non_uniform_initialization()
{
    // See Item 7 from Effective Modern C++
    // 3 different ways of initializing in C++:
    int one(0);
    int two = 0;
    int three{ 0 };
    int four = { 0 };  // three and four are equivalent
}


void test_uniform_initialization()
{
    struct Test
    {
    public:
        int age{100}; //Initialise like this in declaration isntead of init syntax in constructor
        std::string name;
    };

    class Test2
    {
        int number;
    };

    // examples:
    
    int a1[2][2]{ {1, 2}, {3, 4} };
    int a2[2][2]{ 1, 2, 3, 4 };
    
    auto a{ 1 }; //This will remain an int not an array
    cout << a << endl;
    
    //auto b{1, 2, 3, 4};

}


int main()
{
    test_braces_CPP98();
    test_non_uniform_initialization();
    test_uniform_initialization();

    getchar();
    return 0;
}
