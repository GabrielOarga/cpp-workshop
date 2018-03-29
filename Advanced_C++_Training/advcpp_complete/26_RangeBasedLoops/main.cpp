#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main()
{
    auto texts = {"one", "two", "three"};  // beware, this is an initializer_list!
    for (auto text : texts)
        cout << text << endl;
	cout << typeid(texts).name() << endl;

	initializer_list<int> numbers{ 1, 2, 3 };
	cout << typeid(numbers).name() << endl;

	// auto numbers{ 1, 2, 3 };     // doesn't work!
	// auto numbers2{ {1, 2, 3} };  // also doesn't work

    // same thing with STL containers:
    vector<string> names{"Liviu", "Florin", "Gheorghe"};

    for (auto name : names)
        cout << name << endl;

    // iterating over a string char by char:
    string hello = "Hello";
    for (auto c : hello)
        cout << c << endl;

    vector<int> numbers{1, 2, 3};
    for (auto& n : numbers)
        n++;

    for (auto n : numbers)
        cout << n << " ";

    getchar();
    return 0;
}
