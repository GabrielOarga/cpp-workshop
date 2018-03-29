#include <iostream>
#include <vector>

using namespace std;


class Empty {};

class NotEmpty
{
public:
    NotEmpty() = default;
    NotEmpty(const NotEmpty& other) = default;
    NotEmpty& operator=(const NotEmpty& other) = delete;
    
    virtual void sayHello()
    {
        cout << "NotEmpty::hello!" << endl;
    }
    
    virtual void sayGoodbye() = delete;
    
};

class Another : public NotEmpty
{
public:
//    void sayHello() = delete;
//    virtual void sayGoodbye(); //explore this example further
};

int main()
{

    getchar();
    return 0;
}
