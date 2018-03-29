#ifndef DEFAULTSPSTORAGE_H
#define DEFAULTSPSTORAGE_H

template <class T>
class DefaultSPStorage
{
protected:
	typedef T* StoredType; //the type of the pointee_ object 
	typedef T* PointerType; //type returned by operator-> 
	typedef T& ReferenceType; //type returned by operator* 

public:
	DefaultSPStorage()
		: m_pointee(Default())
	{
	}

	DefaultSPStorage(const StoredType& pObj)
		: m_pointee(pObj)
	{
	}

	PointerType operator->() const
	{
		return m_pointee;
	}

	ReferenceType operator*() const
	{
		return *m_pointee;
	}

	friend inline PointerType GetImpl(const DefaultSPStorage& sp)
	{
		return sp.m_pointee;
	}

	friend inline const StoredType& GetImplRef(const DefaultSPStorage& sp)
	{
		return sp.m_pointee;
	}

	friend inline StoredType& GetImplRef(DefaultSPStorage& sp)
	{
		return sp.m_pointee;
	}

protected:
	void Destroy()
	{
		delete m_pointee;
	}

	static StoredType Default()
	{
		return 0;
	}

private:
	StoredType m_pointee;
};

#endif //DEFAULTSPSTORAGE_H