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


    virtual ~TextOperation()
    {
    }
};


struct Append : public TextOperation
{
    explicit Append(const string& suffix) : suffix(suffix)
    {
    }


    string operator()(string& input) override
    {
        return input + suffix;
    }


    virtual ~Append()
    {
    }


private:
    string suffix;
};


struct Prepend : public TextOperation
{
    explicit Prepend(const string& prefix) : prefix(prefix)
    {
    }


    string operator()(string& input) override
    {
        return prefix + input;
    }


    virtual ~Prepend()
    {
    }


private:
    string prefix;
};


// look how the functor is passed as an argument to a function
string process(string& text, TextOperation& operation)
{
    return operation(text);
}


int main()
{
    Append append("_SUFFIX");
    Prepend prepend("PREFIX_");
    string text;
    cout << "Enter some text: ";
    cin >> text;
    cout << process(text, append) << endl;
    cout << process(text, prepend) << endl;

    getchar();
    getchar();
    return 0;
}
