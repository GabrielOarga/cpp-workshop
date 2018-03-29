#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

//Custom Smart Pointers
//WIP
namespace csp
{
	template <typename T> class SharedPointer
	{
		class ReferenceCounter
		{
		public:
			ReferenceCounter (void)
				: m_refCount(0)
			{
			}

			int refCount()
			{
				return m_refCount;
			}
		private:
			int m_refCount;
		};

	public:
		SharedPointer()
			: reference(new ReferenceCounter)
			, m_pData(0)
		{
		}

		SharedPointer(T* pointer)
			: reference(new ReferenceCounter)
			, m_pData(pointer)
		{
		}

		~SharedPointer()
		{	
		}

	private:
		T* m_pData;
		ReferenceCounter* reference;
	};
}

#endif //SHAREDPOINTER_H