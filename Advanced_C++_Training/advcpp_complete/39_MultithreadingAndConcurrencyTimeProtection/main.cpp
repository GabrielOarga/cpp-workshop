#include <iostream>
#include <vector>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

#include "RandomUtil.h"


using namespace std;

static const unsigned int TIMEOUT_MS = 1;

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
        m_capacity(capacity)
    {
        m_buf = new int[m_capacity];
    }

    virtual ~Resource()
    {
        delete[] m_buf;
    }

    Resource(const Resource& other) = delete;

    Resource& operator=(const Resource& other) = delete;

    void add(int val)
    {
        if (!m_mutex.try_lock_for(std::chrono::milliseconds(TIMEOUT_MS))) {
            cout << "Cannot lock while adding" << endl;
            return;
        }
        if (!m_not_full.wait_for(m_mutex, chrono::milliseconds(TIMEOUT_MS), [this]() { return m_size < m_capacity; })) {
            cout << "Producer: waited to much for consumer" << endl;
            m_mutex.unlock();
            return;
        }

        m_buf[m_size++] = val;

        m_not_empty.notify_all();
        m_mutex.unlock();
    }

    int remove()
    {
        if (!m_mutex.try_lock_for(std::chrono::milliseconds(TIMEOUT_MS))) {
            cout << "Cannot lock while removing" << endl;
            return -1;
        }
        if (!m_not_empty.wait_for(m_mutex, chrono::milliseconds(TIMEOUT_MS), [this]() { return m_size > 0; })) {
            cout << "Consumer: waited too much for producer" << endl;
            m_mutex.unlock();
            return -1;
        }

        auto val = m_buf[--m_size];

        m_not_full.notify_all();
        m_mutex.unlock();
        return val;
    }

    unsigned int get_size() const { return m_size; }

    friend ostream& operator<<(ostream& out, const Resource& obj)
    {
        out << "size = " << obj.m_size;
        return out;
    }


private:
    int* m_buf{};
    const unsigned int m_capacity;
    unsigned int m_size{};

    recursive_timed_mutex m_mutex{};
    condition_variable_any m_not_empty{};
    condition_variable_any m_not_full{};
};


void prod(Resource& common)
{
    using namespace edocti::utils;
    RandomUtil::randomize();
    while (true) {
        auto val{ RandomUtil::nextInt(1, 1000) };
        // cout << "Producer-" << std::this_thread::get_id() << " produced " << val << endl;
        common.add(val);
    }
}


void cons(Resource& common)
{
    while (true) {
        auto val{ common.remove() };
        // cout << "Consumer-" << this_thread::get_id() << " consumed " << val << endl;
    }
}


int main()
{
    Resource common(10);
    vector<thread> workers;

    // by default parameters to thread start routine are passed by value
    // in our case we need to pass by reference: there is a single, common resource
    // => we use std::ref or std::cref
    // this is important, otherwise each thread will block in add() or remove()
    // and no thread will execute the opposite operation *on the same common resource*
    workers.emplace_back(thread(cons, ref(common)));
    workers.emplace_back(thread(prod, ref(common)));

    for (auto& w : workers) { w.join(); }  // take reference since thread copy constructor was deleted

    // WHY are these exceptions important? VS2015 has all sorts of mechanisms
    // for avoiding deadlocks => when deadlock is detected, am exception is thrown!
    // => your application doesn't stall: it goes into the exception handler

    getchar();
    return 0;
}
