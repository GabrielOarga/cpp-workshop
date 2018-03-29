#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


// dummy
bool match3(string text)
{
    return text.size() == 3;
}


bool match4(string text)
{

    return text.size() == 4;
}


int countStrings(vector<string>& texts, bool (*pMatch)(string))
{
    return count_if(texts.begin(), texts.end(), pMatch);
}


int main()
{
    vector<string> texts{"one", "two", "three", "four", "five", "one", "two"};

    cout << match3(texts[0]) << endl;
    auto nr_matches = count_if(texts.begin(), texts.end(), match3);
    cout << "Nr matches in vector: " << nr_matches << endl;

    // same thing here:
    // passing function as function parameter
    nr_matches = countStrings(texts, match3);
    cout << "Nr of 3-sized strings: " << nr_matches << endl;

    nr_matches = countStrings(texts, match4);
    cout << "Nr of 4-sized strings: " << nr_matches << endl;

    getchar();
    return 0;
}
