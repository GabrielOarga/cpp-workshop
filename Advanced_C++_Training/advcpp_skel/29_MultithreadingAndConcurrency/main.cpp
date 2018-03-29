#include <iostream>
#include <vector>

#include <string>

#include "RandomUtil.h"
#include <thread>
#include <mutex>

using namespace std;


/**
* Many concurrency applications follow the producer/consumer pattern.
* In this pattern there is a common resource (a class / struct)
* which exposes at least two operations which are usually complementary:
* e.g. add() and remove()
* <p>
* At least two threads try to work concurrently on the same *instance*
* of this common resource class => we need to synchronize the access to
* the common resource.
* <p>
* In our example class Resource is the common resource and we have several threads
* which continuously add() and remove() from the common resource.
*/
class Resource {
public:
    explicit Resource(const unsigned int capacity) :
        m_capacity(capacity),
        m_size(0)
    {
        m_buf = new int[m_capacity]{};
    }

    virtual ~Resource()
    {
        delete[] m_buf;
    }

    Resource(const Resource& other) = delete;

    Resource& operator=(const Resource& other) = delete;

    void add(int val)
    {
    }

    int remove()
    {
        return -1;
    }

    unsigned int get_size() const { return m_size; }

    friend ostream& operator<<(ostream& out, const Resource& obj)
    {
        out << "size = " << obj.m_size;
        return out;
    }

private:
    int* m_buf;
    const unsigned int m_capacity;
    unsigned int m_size;
};


void prod(Resource& common)
{
}


void cons(Resource& common)
{
}


int main()
{
    Resource common(10);


    getchar();
    return 0;
}
