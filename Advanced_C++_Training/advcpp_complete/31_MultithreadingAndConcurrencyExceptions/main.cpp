#include <iostream>
#include <vector>

#include <string>

#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

const int TIMEOUT_MS = 2;


// global vector for holding exception objects
vector<exception_ptr> g_exceptions;

// global mutex used for atomic insert / retrieve of exception_ptr
mutex g_mutex;


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
        m_buf = new int[m_capacity] {};
    }

    virtual ~Resource()
    {
        delete[] m_buf;
    }

    Resource(const Resource& other) = delete;

    Resource& operator=(const Resource& other) = delete;

    void add(int val)
    {
        if (!m_mutex.try_lock_for(chrono::milliseconds(TIMEOUT_MS))) {
            throw string("Producer: cannot obtain lock");
        }
        if (!m_not_full.wait_for(m_mutex, chrono::milliseconds(TIMEOUT_MS), [this]() { return m_size < m_capacity; })) {
            m_mutex.unlock();
            throw string("Producer: waited to much for consumer");
        }

        m_buf[m_size++] = val;

        m_not_empty.notify_all();

        m_mutex.unlock();
    }

    void print()
    {
        if (!m_mutex.try_lock_for(chrono::milliseconds(TIMEOUT_MS))) {
            cout << "print: Cannot obtain lock" << endl;
            return;
        }
        if (m_size == 0u) { cout << "empty"; }
        for (auto i = 0u; i < m_size; i++)
            cout << m_buf[i] << " ";
        cout << endl;

        m_mutex.unlock();
    }

    int remove()
    {
        int val;
        if (!m_mutex.try_lock_for(chrono::milliseconds(TIMEOUT_MS))) {
            throw string("Consumer: cannot obtain lock");
        }
        if (!m_not_empty.wait_for(m_mutex, chrono::milliseconds(TIMEOUT_MS), [this]() { return m_size > 0; })) {
            m_mutex.unlock();
            throw string("Consumer: waited too long for producer");
        }

        val = m_buf[--m_size];
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
    int* m_buf;
    const unsigned int m_capacity;
    unsigned int m_size;

    recursive_timed_mutex m_mutex{};
    condition_variable_any m_not_empty{};
    condition_variable_any m_not_full{};
};


void prod(Resource& common)
{
    try {
        for (auto i = 0; i < 5; i++) {
            common.add(i);
        }
    }
    catch (...) {
        unique_lock<mutex> lock{ g_mutex };
        g_exceptions.emplace_back(current_exception());
    }
}


void cons(Resource& common)
{
    try {
        for (auto i = 0; i < 5; i++) {
            cout << this_thread::get_id() << ": consumed " << common.remove() << endl;
        }
    }
    catch (...) {
        unique_lock<mutex>lock{ g_mutex };
        g_exceptions.emplace_back(current_exception());
    }
}


int main()
{
    Resource common(10);
    thread producers[] {
        thread{ prod, ref(common) }, thread{ prod, ref(common) },
        thread{ prod, ref(common) }, thread{ prod, ref(common) },
        thread{ prod, ref(common) }, thread{ prod, ref(common) }
    };

    thread consumers[] {
        thread{ cons, ref(common) }, thread{ cons, ref(common) },
        thread{ cons, ref(common) }, thread{ cons, ref(common) },
        thread{ cons, ref(common) }, thread{ cons, ref(common) }
    };

    for (auto &p : producers) p.join();
    for (auto &c : consumers) c.join();

    // not quite necessary (we join all threads), but just in case
    lock_guard<mutex> lock{ g_mutex };
    for (auto e : g_exceptions) {
        try {
            rethrow_exception(e);
        } catch (string& rethrown) {
            cout << "Something is wrong: " << rethrown << endl;
        }
    }

    cout << "final content: ";
    common.print();

    getchar();
    return 0;
}
