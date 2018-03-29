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
    
    explicit RingBuffer(std::initializer_list<T> elements)
    : RingBuffer(elements.size())
    {
        for ( auto e : elements )
            add( e );
    }


    RingBuffer(const RingBuffer& other) :
        RingBuffer(other.m_size)
    {
        for (auto i = 0u; i < m_size; i++)
            add(other.m_buffer[i]);
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

	void add(T obj)
	{
        if ( m_size == 0u)
        {
            return;
        }
        m_buffer[m_pos++] = obj;
        if (m_pos == m_size)
            m_pos = 0u;
	}

    friend std::ostream& operator<<(std::ostream& out, const RingBuffer& r)
    {
        out << "size=" << r.m_size << ", pos=" << r.m_pos << std::endl;
        for (auto i = 0u; i < r.m_size; i++)
            out << r.m_buffer[i] << " ";
        return out;
    }
    
    class iterator;
    
    iterator begin()
    {
        return iterator(0, *this);
    }
    
    iterator end()
    {
        return iterator(m_size, *this);
    }

private:
    T* m_buffer;
    unsigned int m_size;
    unsigned int m_pos;
};

template <typename T>
class RingBuffer<T>::iterator
{
public:
    iterator(int pos, RingBuffer& ring)
    : m_pos(pos)
    , m_ring(ring) { }
    
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
    
    iterator operator++()
    {
        m_pos++;
        return *this;
    }
    
    iterator operator++(int)
    {
        m_pos++;
        return *this;
    }
    
private:
    int m_pos;
    RingBuffer m_ring;
};
