#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main()
{
    auto texts = { "one", "two", "three" };

    for (auto t : texts)
        cout << t << endl;

    int numbers[]{1, 2, 3};  // notice that we cannot use auto. why?
    for (auto &n : numbers)
        n++;

    for (auto n : numbers)
        cout << n << endl;

    getchar();
    return 0;
}
