#include <iostream>
#include <atomic>
#include <thread>

using namespace std;


template<typename T>
class stack
{
    struct node
    {
        explicit node(T data, shared_ptr<node> next) :
            m_data(data),
            m_next(next) {}
        
        explicit node(const node& other) :
            m_data(other.m_data),
            m_next(other.m_next) {}

        T m_data;
        shared_ptr<node> m_next;
    };

    shared_ptr<node> m_head {};
    atomic_int m_size{0};

public:
    void push(const T& data)
    {
        auto n = make_shared<node>(data, atomic_load(&m_head));  // local variable
		// compares m_head to m_next (bit-wise) and:
		//     if they match, m_head becomes n, else m_head becomes n->m_next
		// the whole operation is atomic
        while (!atomic_compare_exchange_weak(&m_head, &n->m_next, n)) {}
        ++m_size;
    }

    T pop()
    {
		// atomically load the *value* held by the shared_ptr => returns the raw pointer
        auto old_head{ atomic_load(&m_head) };  // returns the raw pointer
		// if m_head == old_head => m_head = old_head->m_next, else m_head = old_head
        while(old_head && atomic_compare_exchange_weak(&m_head, &old_head, old_head->m_next)) {}

		// here it's not ideal...
        if (old_head) {
            return old_head->m_data;
        } else {
            return -1;  // empty structure... some other solution?
        }
    }
};


int main()
{
    stack<int> s{};
    constexpr auto N{ 50u };

    thread prod{[&s, N]()
    {
        for (auto i = 0u; i < N; i++) {
            s.push(i);
            cout << this_thread::get_id() << " produce " << i << endl;
        }
    } };

    thread cons{[&s, N]()
    {
        for (auto i = 0u; i < N; i++)
            cout << this_thread::get_id() << " consume " << s.pop() << endl;
    } };

    prod.join();
    cons.join();

    getchar();
    return 0;
}
