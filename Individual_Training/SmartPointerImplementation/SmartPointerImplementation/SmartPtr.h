#ifndef SMARTPTR_H
#define SMARTPTR_H

template
<
	typename T,
	template <class> class OwnershipPolicy = RefCounted,
	class ConversionPolicy = DisallowConversion,
	template <class> class CheckingPolicy = AssertCheck,
	template <class> class StoragePolicy = DefaultSPStorage
>
class SmartPtr;

#endif //SMARTPTR_H

