#include <iostream>
#include <set>
using namespace std;


int main()
{
    set<int> numbers{10, 5, 3, 3, 3, 10, 11};

    numbers.insert(23);
    numbers.insert(-10);

    for (auto number : numbers) {
        cout << number << " ";
    }
    cout << endl;

    auto key = 3;
    if (numbers.find(key) != numbers.end()) {
        cout << key << " is there" << endl;
    } else {
        cout << key << " is not there" << endl;
    }

    key = 15;
    if (numbers.count(key)) {
        cout << key << " is there" << endl;
    } else {
        cout << key << " is not there" << endl;
    }

    getchar();
    return 0;
}
