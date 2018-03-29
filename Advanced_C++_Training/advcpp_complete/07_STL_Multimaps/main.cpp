#include <iostream>
#include <map>

using namespace std;


int main()
{
    // a multimap lets you store values with duplicate keys
    multimap<int, string> lookup{
        {10, "Ion"},
        {20, "Gheorghe"},
        {30, "Marioara"},
        {40, "Ileana"},
        {10, "Vasile"}
    };

    cout << "List all multimap values:" << endl;
    for (auto entry : lookup) {
        cout << entry.first << ": " << entry.second.c_str() << endl;
    }
    cout << endl;

    cout << "Wrong way of finding a key (20) in a multimap:" << endl;
    for (auto it = lookup.find(20); it != lookup.end(); ++it) {
        cout << it->first << ": " << it->second.c_str() << endl;
    }
    cout << endl;

    cout << "Correct way of finding a key (10) in a multimap:" << endl;
    pair<multimap<int, string>::iterator, multimap<int, string>::iterator> findPair = lookup.equal_range(10);
    for (auto it = findPair.first; it != findPair.second; ++it) {
        cout << it->first << ": " << it->second.c_str() << endl;
    }

    getchar();
    return 0;
}
