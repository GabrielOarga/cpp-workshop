#include <iostream>
#include <string>
#include <cctype>  // for toupper() and tolower()
#include <algorithm>

using namespace std;


/**
* A functor is a class / struct which
* overrides the round brackets () operator
*
* It can then be passed to functions as argument.
*/
struct TextOperation
{
    virtual string operator()(string& input) = 0;
    virtual ~TextOperation() {}
};


int main()
{
    string something{"something"};

    getchar();
    return 0;
}
