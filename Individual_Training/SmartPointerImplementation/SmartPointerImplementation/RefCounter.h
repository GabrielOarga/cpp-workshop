#ifndef REFCOUNTER_H
#define REFCOUNTER_H

template <class T>
class RefCounter //This supports intrusive and non intrusive reference counting
{
public:
	enum { destructiveCopy = false};

	RefCounter()
		: m_pCount(new unsigned int(1))
	{
	}

	T clone(const T& val)
	{
		++*m_pCount;
		return val;
	}

	bool release(const T&)
	{
		if(!--*m_pCount)
		{
			delete m_pCount;
			return true;
		}
		return false;
	}

private:
	unsigned int* m_pCount;
};

#endif //REFCOUNTER_H