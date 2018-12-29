#ifndef DARKML_COMMON_H
#define DARKML_COMMON_H

#include <initializer_list>
#include <memory>

namespace darkml
{
	enum class Phase
	{
		Train,
		Test,
	};

	enum class Regularizer
	{
		None,
		L1,
		L2,
	};

	template<typename T>
	struct Data
	{
		T* data;
		int size;
		Data() : data(nullptr), size(0) {}
		Data(int s) 
		{ 
			size = s; 
			data = new T[size]; 
			memset(data, 0, size * sizeof(T));
		}
		~Data() { if (data) delete[] data; }
	};

	struct Rectangle
	{
		int x;
		int y;
		int width;
		int height;

		Rectangle()
			: x(0), y(0), width(0), height(0) {}

		Rectangle(int x, int y, int w, int h)
			: x(x), y(y), width(w), height(h) {}
	};

	template<int N>
	struct Shape
	{
		int dims[N];

		Shape()
		{
			for (int i = 0; i < N; ++i)
				dims[i] = 0;
		}

		Shape(const int* d)
		{
			for (int i = 0; i < N; ++i)
				dims[i] = d[i];
		}

		int& operator[](int index) { return dims[index]; }
		const int& operator[](int index) const { return dims[index]; }

		bool operator==(const Shape<N>& shape)
		{
			for (int i = 0; i < N; ++i)
				if (dims[i] != shape.dims[i])
					return false;
			return true;
		}
	};
}


#endif
