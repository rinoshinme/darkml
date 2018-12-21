#ifndef DARKML_HEAP_H
#define DARKML_HEAP_H

#include <vector>
#include <algorithm>
#include <iostream>

namespace darkml
{

	// default comparator is operator<(T, T) ?
	// default is max-heap
	template<typename T>
	class Heap
	{
	private:
		std::vector<T> array;

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

	template<typename T>
	Heap<T>::Heap(const std::vector<T>& arr)
	{
		array = arr;
		std::make_heap(array.begin(), array.end());
	}

	template<typename T>
	void Heap<T>::push(const T& val)
	{
		array.push_back(val);
		std::push_heap(array.begin(), array.end());
	}

	template<typename T>
	void Heap<T>::pop()
	{
		if (array.size() == 0)
			return;
		std::pop_heap(array.begin(), array.end());
		array.pop_back();
	}

	template<typename T>
	void Heap<T>::show(std::ostream& os)
	{
		for (size_t k = 0; k < array.size(); ++k)
			os << array[k] << ", ";
		os << std::endl;
	}

	template<typename T>
	std::vector<T> Heap<T>::getTopK(int k)
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
