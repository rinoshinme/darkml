#ifndef DARKML_HEAP_H
#define DARKML_HEAP_H

#include <vector>
#include <algorithm>
#include <iostream>

namespace darkml
{
	// default comparator is less<T>() ?
	// default is max-heap, by changing to greater<T>(), min-heap is achieved.
	// specialize less<T>(T, T) or greater<T>(T, T) for specific type T
	template<typename T, typename Comparator = std::less<T> >
	class Heap
	{
	private:
		std::vector<T> array;
		Comparator comparator;

	public:
		Heap() {}
		Heap(const std::vector<T>& arr);

		void push(const T& val);
		void pop();
		T& max() { return array[0]; }
		const T& max() const { return array[0]; }
		void show(std::ostream& os = std::cout);

		std::vector<T> getTopK(int k);
	};

	// template<typename T>
	// class MaxHeap : public Heap < T, std::greater<T> > {};

	template<typename T, typename Comparator = less<T> >
	Heap<T, Comparator>::Heap(const std::vector<T>& arr)
	{
		array = arr;
		std::make_heap(array.begin(), array.end(), comparator);
	}

	template<typename T, typename Comparator = less<T> >
	void Heap<T, Comparator>::push(const T& val)
	{
		array.push_back(val);
		std::push_heap(array.begin(), array.end(), comparator);
	}

	template<typename T, typename Comparator = less<T> >
	void Heap<T, Comparator>::pop()
	{
		if (array.size() == 0)
			return;
		std::pop_heap(array.begin(), array.end(), comparator);
		array.pop_back();
	}

	template<typename T, typename Comparator = less<T> >
	void Heap<T, Comparator>::show(std::ostream& os)
	{
		for (size_t k = 0; k < array.size(); ++k)
			os << array[k] << ", ";
		os << std::endl;
	}

	template<typename T, typename Comparator = less<T> >
	std::vector<T> Heap<T, Comparator>::getTopK(int k)
	{
		std::vector<T> results;
		for (int i = 0; i < k; ++i)
		{
			results.push_back(max());
			pop();
		}
		return results;
	}
}

#endif
