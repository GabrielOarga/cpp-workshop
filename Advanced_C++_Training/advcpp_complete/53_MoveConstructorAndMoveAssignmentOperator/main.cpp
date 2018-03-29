#include <iostream>
#include <vector>

#include "RingBuffer.h"

using namespace std;

template<typename T>
RingBuffer<T> getBuffer(unsigned int size)
{
    return RingBuffer<T>(size);
}


int main()
{
    cout << "Test push_back solution:" << endl;
    vector<RingBuffer<int>> vec;
    vec.push_back(RingBuffer<int>(10));
    vec.push_back(RingBuffer<int>(5));
    vec.push_back(RingBuffer<int>(3));

    // compare the result above with the one below:
    cout << "Test initializer list:" << endl;
    vector<RingBuffer<int>> vec2{
        RingBuffer<int>(10), RingBuffer<int>(100), RingBuffer<int>(2)
    };

    // test the move assignment operator:
    cout << "Test move assignment operator: " << endl;
    auto buf = getBuffer<int>(5);
    buf = getBuffer<int>(10);       // we assign to a rValue => move assignment operator called

    getchar();
    return 0;
}
