#include <iostream>
#include <exception>

using namespace std;


class MyException : public exception
{
public:
    virtual const char* what()
    {
        return "MyException: something wrong happened";
    }
};


class Test
{
public:
    explicit Test(int x) : x(x)
    {
    }


    void goesWrong() throw(MyException)
    {
        x++;
        throw MyException();
    }


private:
    int x;
};


int main()
{
    Test t{10};
    try {
        t.goesWrong();
    } catch (MyException& e) {
        cerr << "Caught " << e.what() << endl;
    }

    getchar();
    return 0;
}
