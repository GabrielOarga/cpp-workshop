#include <iostream>
#include <atomic>
#include <thread>

using namespace std;

template<typename T>
class Stack
{
    struct node
    {
        explicit node(T data, shared_ptr<node> next)
        : m_data(data),
        m_next(next)
        {}
        
        T m_data;
        shared_ptr<node> m_next;
    };
    
    atomic_int m_size{ 0 };
    shared_ptr<node> m_head{};
    
public:
    void push(const T& data)
    {
        auto n = make_shared<node>(data, atmoic_load(&m_head));
        //compare m_head with n->m_next;
        //  if equal : m_next becomes n
        //      else: m_head becomes n->m_next
        while(!atomic_compare_exchange_weak(&m_head, &n->m_next, n)) {}
        
        m_size++;
    }
    
    T pop()
    {
        auto old_head{ atomic_load(&m_head) };
        while(old_head && atomic_compare_exchange_weak( &m_head, &old_head, old_head->m_next)) {}
        
        if(old_head)
        {
            return old_head->m_data;
        }
        else
        {
            return -1; //ugly but meh
        }
    }
    
};


int main()
{
    Stack<int> s{};
    constexpr N { 50u };
    //incomplete

	getchar();
	return 0;
}
