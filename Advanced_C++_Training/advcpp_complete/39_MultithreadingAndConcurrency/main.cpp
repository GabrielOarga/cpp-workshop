#include <iostream>
#include <vector>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

#include "RandomUtil.h"

using namespace std;

// global variables used for storing exceptions from threads
mutex g_exceptions_mutex;
vector<exception_ptr> g_exceptions_container;

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
	Resource(const Resource& other) = delete;
	Resource& operator=(const Resource& other) = delete;

    virtual ~Resource()
    {
        delete[] m_buf;
    }

    void add(int val)
    {
        unique_lock<mutex> lock{m_mutex};
        m_not_full.wait(lock, [this]() { return m_size < m_capacity; });

        m_buf[m_size++] = val;

        m_not_empty.notify_all();
    }

    int remove()
    {
        unique_lock<mutex> lock{m_mutex};
        m_not_empty.wait(lock, [this]() { return m_size > 0; });

        auto val = m_buf[--m_size];

        m_not_full.notify_all();
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

    mutex m_mutex{};
    condition_variable m_not_empty{};
    condition_variable m_not_full{};
};


void prod(Resource& common)
{
    using namespace edocti::utils;
    RandomUtil::randomize();
    while (true) {
        auto val{ RandomUtil::nextInt(1, 1000) };
        cout << "Producer-" << std::this_thread::get_id() << " produced " << val << endl;
        common.add(val);
    }
}


void cons(Resource& common)
{
    while(true) {
        auto val = common.remove();
        cout << "Consumer-" << this_thread::get_id() << " consumed " << val << endl;
    }
}


int main()
{
    Resource common(10);
    vector<thread> workers;

    // by default parameters to thread start routine are passed by value
    // in our case we need to pass by reference: there is a single, common resource
    // => we use std::ref
    // this is important, otherwise each thread will block in add() or remove()
    // and no thread will execute the opposite operation *on the same common resource*
    workers.emplace_back(thread(cons, ref(common)));
    workers.emplace_back(thread(prod, ref(common)));

	// ref() returns a reference_wrapper and not a direct reference to common
	// this reference_wrapper instead holds &common
	// ref() is very useful when you want to emulate a reference of an object
	// which can be copied (copy-constructor and copy-assignable)
	// other situations: arrays of reference_wrappers, instead of arr of refs

    for (auto& w : workers) {
        if (w.joinable())
            w.join();
    }  // take reference since thread copy constructor was deleted

    getchar();
    return 0;
}
