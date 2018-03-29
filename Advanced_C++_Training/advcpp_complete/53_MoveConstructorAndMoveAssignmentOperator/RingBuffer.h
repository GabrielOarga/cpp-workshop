#pragma once

#include <string>
#include <ostream>


template <typename T>
class RingBuffer
{
public:
    explicit RingBuffer(unsigned int size) :
        m_buffer(),
        m_size(size),
        m_pos(0u)
    {
        m_buffer = new T[size];
    }


    explicit RingBuffer(std::initializer_list<T> elements) :
        RingBuffer(elements.size())
    {
        for (auto e : elements) {
            add(e);
        }
    }

    RingBuffer(const RingBuffer& other) :
        RingBuffer(other.m_size)
    {
        std::cout << "RingBuffer: copy constructor called" << std::endl;
        for (auto i = 0; i < m_size; i++)
            add(other.m_buffer[i]);
    }


    //////// START modification
    RingBuffer(RingBuffer&& other) noexcept  // not const!!
    {
        std::cout << "RingBuffer: move constructor called" << std::endl;
        m_size = other.m_size;
        m_pos = other.m_pos;
        m_buffer = other.m_buffer;
        other.m_buffer = nullptr;   // this is important: we don't want other's destructor to delete[] our m_buffer!
                                    // since c++11 it is safe to delete nullptr (See destructor)
    }

    RingBuffer& operator=(RingBuffer&& other) noexcept  // not const!!
    {
        std::cout << "RingBuffer: move assignment operator called" << std::endl;
        // this object (this) already has allocated memory
        delete[] m_buffer;
        m_buffer = other.m_buffer;
        m_size = other.m_size;
        m_pos = other.m_pos;
        other.m_buffer = nullptr;   // we already know why
        return *this;
    }

    //////// END modification


    RingBuffer& operator=(std::initializer_list<T> elements)
    {
        std::cout << "RingBuffer: assignment operator called" << std::endl;
        m_size = 0;
        delete[] m_buffer;
        m_buffer = new T[elements.size()];
        for (auto e : elements) {
            add(e);
        }
        return *this;
    }


    virtual ~RingBuffer()
    {
        delete[] m_buffer;
    }


    T get(unsigned int i)
    {
        if (i > m_size) {
            throw std::string("RingBuffer::get: given index is bigger than size");
        }
        return m_buffer[i];
    }


    void add(T obj) // we add a copy of the original object (just like vectors do)
    {
        if (m_size == 0u) {
            return;
        }
        m_buffer[m_pos++] = obj;
        if (m_pos == m_size) {
            m_pos = 0u;
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const RingBuffer& r)
    {
        out << "size=" << r.m_size << ", pos=" << r.m_pos << std::endl;
        for (auto i = 0; i < r.m_size; i++)
            out << r.m_buffer[i] << " ";
        return out;
    }

    class iterator;

    iterator begin()  // a new instance of the iterator
    {
        return iterator(0, *this);
    }


    iterator end()  // a new instance of the iterator
    {
        return iterator(m_size, *this);
    }


private:
    T* m_buffer{nullptr};
    unsigned int m_size{};
    unsigned int m_pos{};
};


template <typename T>
class RingBuffer<T>::iterator
{
public:
    iterator(int pos, RingBuffer& a_ring) :
        m_pos(pos),
        m_ring(a_ring) { }


    virtual ~iterator() { }


    bool operator!=(const iterator& other) const
    {
        return m_pos != other.m_pos;
    }


    bool operator==(const iterator& other) const
    {
        return !operator!=(other);
    }


    T operator*()
    {
        return m_ring.get(m_pos);
    }


    iterator& operator++(int)
    {
        m_pos++;
        return *this;
    }


    iterator& operator++()
    {
        m_pos++;
        return *this;
    }


private:
    unsigned int m_pos;
    RingBuffer& m_ring;
};
