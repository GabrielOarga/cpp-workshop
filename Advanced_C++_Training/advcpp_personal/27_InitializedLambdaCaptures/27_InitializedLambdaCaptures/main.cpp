#include <iostream>
#include <memory>

using namespace std;


int main()
{
    auto pwr2 = [value = 10]() { return value * value; }; //Init values in capture field
    cout << pwr2() << endl;
    
    shared_ptr<int> outer_int;
    auto inner_int = outer_int = make_shared<int>(2);
    
    auto pwr3 = [val = std::move(inner_int)]() { //moved shared ptr to val from inner_int. NOTE: this sould be usefull if instead of 'int' you would have a huge class or something, so you don't copy
        *val = *val * *val * *val;
        return val;
    };
    
    cout << "pwr3: inner_int = " << *pwr3() << endl;
    cout << "pwr3: inner_int = " << *pwr3() << endl;

    cout << "outer_int = " << *outer_int << endl;
//    cout << "inner_int = " << *inner_int << endl; //can no longer access shared ptr that has been moved (lambda decl)
    
    getchar();
    return 0;
}
