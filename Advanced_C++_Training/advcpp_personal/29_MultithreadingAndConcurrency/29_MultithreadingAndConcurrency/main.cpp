#include <iostream>
#include <vector>

#include <string>

#include "RandomUtil.h"
#include <thread>
#include <mutex>

using namespace std;
using namespace edocti::utils;


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
        unique_lock<mutex> lock(m_mutex);
        m_not_full.wait(lock, [this]() { return m_size < m_capacity; });
        
        m_buf[m_size++] = val; //Non atomic , m_size++, can cauze big problems with #1, to fix this we willuse Mutex
        
        m_not_empty.notify_all(); // must notify the remove function, that we have modified the m_size value and it's condition might be true now
    }

    int remove()
    {
        unique_lock<mutex> lock(m_mutex); //This mutex lock dissapears anyway when the function goes out of scope
        m_not_empty.wait(lock, [this]() { return m_size > m_capacity; });
        
        auto val{m_buf[--m_size]}; //#1
        
        m_not_full.notify_all(); // must notify the add function, that we have modified the m_size value and it's condition might be true now
        return val;

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
    std::mutex m_mutex{ };
    std::condition_variable m_not_full{};
    std::condition_variable m_not_empty{};

};


void prod(Resource& common)
{
    RandomUtil::randomize();
    while (true) {
        auto val{RandomUtil::nextInt(1, 200)};
        cout << "Producer " << std::this_thread::get_id() << " produced" << val << endl;
        common.add(val);
    }
}


void cons(Resource& common)
{
    while (true) {
        auto val{ common.remove() };
        cout << "Consumer " << std::this_thread::get_id() << " consumed" << val << endl;
    }
}


int main()
{
    Resource common(10);
    vector<thread> workers;
    workers.emplace_back(thread(cons, ref(common)));
    workers.emplace_back(thread(prod, ref(common)));

    for (auto& w : workers)
    {
        if (w.joinable())
            w.join();
    }

    getchar();
    return 0;
}
