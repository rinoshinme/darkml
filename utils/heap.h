#ifndef DARKML_HEAP_H
#define DARKML_HEAP_H

namespace darkml
{
	template<typename T>
	class DefaultComparator
	{
	public:
		bool operator()(const T v1, const T v2)
		{
			if (v1 < v2)
				return -1;
			else if (v1 > v2)
				return 1;
			else
				return 0;
		}
	};

	template<typename T, typename Comparator = DefaultComparator<T> >
	class Heap
	{
	private:

	};
}

#endif
