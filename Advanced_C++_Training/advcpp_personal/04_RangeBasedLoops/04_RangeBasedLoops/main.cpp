#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main()
{
    auto texts = { "one", "two", "three" }; //init list, NOT a vector
    cout << typeid(texts).name() << endl;
    

    for (auto t : texts)
        cout << t << endl;

    int numbers[]{1, 2, 3};  // notice that we cannot use auto. why?
    for (auto &n : numbers) //Asta merge pe orice a[] array type, compilator magic, normally only works if iterators are implemented
        n++;

    for (auto n : numbers)
        cout << n << endl;

    getchar();
    return 0;
}
