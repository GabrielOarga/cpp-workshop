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
		// TODO
	}

    friend std::ostream& operator<<(std::ostream& out, const RingBuffer& r)
    {
        out << "size=" << r.m_size << ", pos=" << r.m_pos << std::endl;
        for (auto i = 0u; i < r.m_size; i++)
            out << r.m_buffer[i] << " ";
        return out;
    }

private:
    T* m_buffer;
    unsigned int m_size;
    unsigned int m_pos;
};
