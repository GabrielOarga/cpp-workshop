#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


bool match3(string text)
{
    return text.size() == 3;
}


bool match4(string text)
{
    return text.size() == 4;
}


int main()
{
    vector<string> texts{ "one", "two", "three", "four", "five", "one", "two" };

    getchar();
    return 0;
}
