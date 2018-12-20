#ifndef DARKML_ARRAY_H
#define DARKML_ARRAY_H

#include <memory>
#include <vector>
#include <ostream>
#include "common.h"
#include "throw_assert.h"

namespace darkml
{
	/* 2d data container
	* basic data type for ml algorithms, so as convenient and powerful as possible */
	template<typename T>
	class Array
	{
	private:
		std::shared_ptr<Data<T> > data_ptr;
		int start;
		int stride; // row stride
	public:
		// set array size as public, but not intended to be modified easily
		int rows;	// number of samples
		int cols;	// number of attributes per sample

	public:
		Array(); // initialize an empty array
		// Array(const Shape<2>& shape);
		Array(int rows, int cols);
		Array(const Array<T>& array);
		Array(const T* data, int rows, int cols);
		Array(const std::vector<T>& vec, int row_or_col = 1);
		Array(const std::vector<std::vector<T> >& vec2);
		// only copy data
		Array<T>& operator=(const Array<T>& array);
		~Array() {}

		void copyDataFrom(const Array<T>& array);

		Array<T> row(int r);
		const Array<T> row(int r) const;
		Array<T> col(int c);
		const Array<T> col(int c) const;
		Array<T> batch(int start, int offset);
		const Array<T> batch(int start, int offset) const;

		T& operator()(int r, int c);
		const T& operator()(int r, int c) const;
		// only for single row or column
		T& operator[](int index);
		const T& operator[](int index) const;

		int intLabel(int r, int c) const; // return integer label values for 0.0f or 1.0f in classification
		// Shape<2> shape() { return Shape<2>{rows, cols}; }

		template<typename T2>
		Array<T2> convert();

		// allocate new memory
		void makePrivate(); 
		// rather expensive operations due to memory allocation
		void resize(int nrows, int ncols);

		Array<T> subArray(const Rectangle& rect);
		const Array<T> subArray(const Rectangle& rect) const;
		Array<T> subArray(int r, int c, int height, int width);
		const Array<T> subArray(int r, int c, int height, int width) const;

		// only meaningful for float and double values...
		T sum();
		T squareSum();
		T mean();
		T variance();
		void meanVar(T& mean, T& var);
		// Array<T> rowAverage();
		// Array<T> colAverage();
		// Array<T> rowVariance();
		// Array<T> colVariance();

		// simple thresholding, positive = false for inverted thresholding
		Array<bool> threshold(T thresh, bool positive = true);

		// operator overloading
		Array<T> operator+=(const Array<T>& array);
		Array<T> operator-=(const Array<T>& array);
		Array<T> operator*=(T val);
		Array<T> operator/=(T val);
		Array<T> operator*=(const Array<T>& array);
		// consider broadcasting when doing arithmetics, e.g. += and -=

		void shuffle(const std::vector<int>& data);

	private:
		void copyMetaDataFrom(const Array<T>& array);
	};

	template<typename T>
	Array<T>::Array()
	{
		data_ptr = std::make_shared<Data<T> >();
		start = 0;
		stride = 0;
		rows = 0;
		cols = 0;
	}

	/*
	template<typename T>
	Array<T>::Array(const Shape<2>& shape)
		: Array(shape[0], shape[1]) {}
	*/

	template<typename T>
	Array<T>::Array(int rows, int cols)
	{
		data_ptr = std::make_shared<Data<T> >(rows * cols);
		start = 0;
		stride = cols;
		this->rows = rows;
		this->cols = cols;
	}

	template<typename T>
	Array<T>::Array(const Array<T>& array)
	{
		copyMetaDataFrom(array);
	}

	template<typename T>
	Array<T>& Array<T>::operator=(const Array<T>& array)
	{
		copyMetaDataFrom(array);
		return *this;
	}

	template<typename T>
	void Array<T>::copyDataFrom(const Array<T>& array)
	{
		throw_assert(rows == array.rows && cols == array.cols, "Array dimensions should match");
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				(*this)(r, c) = array(r, c);
			}
		}
	}

	template<typename T>
	Array<T> Array<T>::row(int r)
	{
		Array<T> arr;
		arr.data_ptr = data_ptr;
		arr.start = start + r * stride;
		arr.stride = stride;
		arr.rows = 1;
		arr.cols = cols;
		return arr;
	}

	template<typename T>
	const Array<T> Array<T>::row(int r) const
	{
		Array<T> arr;
		arr.data_ptr = data_ptr;
		arr.start = start + r * stride;
		arr.stride = stride;
		arr.rows = 1;
		arr.cols = cols;
		return arr;
	}

	template<typename T>
	Array<T> Array<T>::col(int c)
	{
		Array<T> arr;
		arr.data_ptr = data_ptr;
		arr.start = start + c;
		arr.stride = stride;
		arr.rows = rows;
		arr.cols = 1;
		return arr;
	}

	template<typename T>
	const Array<T> Array<T>::col(int c) const
	{
		Array<T> arr;
		arr.data_ptr = data_ptr;
		arr.start = start + c;
		arr.stride = stride;
		arr.rows = rows;
		arr.cols = 1;
		return arr;
	}

	template<typename T>
	Array<T> Array<T>::batch(int start, int offset)
	{
		return subArray(start, 0, offset, cols);
	}

	template<typename T>
	const Array<T> Array<T>::batch(int start, int offset) const
	{
		return subArray(start, 0, offset, cols);
	}

	template<typename T>
	Array<T> Array<T>::subArray(int r, int c, int height, int width)
	{
		throw_assert(r >= 0 && c >= 0 && (r + height) <= rows && (c + width) <= cols, "Invalid dimensions");
		Array<T> res(*this);
		res.start = start + r * stride + c;
		res.stride = stride;
		res.rows = height;
		res.cols = width;
		return res;
	}

	template<typename T>
	const Array<T> Array<T>::subArray(int r, int c, int height, int width) const
	{
		throw_assert(r >= 0 && c >= 0 && (r + height) < rows && (c + width) < cols, "Invalid dimensions");
		Array<T> res(*this);
		res.start = start + r * stride + c;
		res.stride = stride;
		res.rows = height;
		res.cols = width;
		return res;
	}

	template<typename T>
	Array<T> Array<T>::subArray(const Rectangle& rect)
	{
		return subArray(rect.y, rect.x, rect.height, rect.width);
	}

	template<typename T>
	const Array<T> Array<T>::subArray(const Rectangle& rect) const
	{
		return subArray(rect.y, rect.x, rect.height, rect.width);
	}

	template<typename T>
	T& Array<T>::operator()(int r, int c)
	{
		return data_ptr->data[start + r * stride + c];
	}

	template<typename T>
	const T& Array<T>::operator()(int r, int c) const
	{
		return data_ptr->data[start + r * stride + c];
	}

	template<typename T>
	T& Array<T>::operator[](int index)
	{
		throw_assert((rows == 1) || (cols == 1),
			"Array<T>::operator[] only valid for row or column arrays");
		if (rows == 1)
			return (*this)(0, index);
		else
			return (*this)(index, 0);
	}

	template<typename T>
	const T& Array<T>::operator[](int index) const
	{
		throw_assert((rows == 1) || (cols == 1),
			"Array<T>::operator[] only valid for row or column arrays");
		if (rows == 1)
			return (*this)(0, index);
		else
			return (*this)(index, 0);
	}

	template<typename T>
	int Array<T>::intLabel(int r, int c) const
	{
		T val = (*this)(r, c);
		throw_assert(typeid(T) == typeid(float) || typeid(T) == typeid(double), "Array type should be float or double");
		return nearestInteger(val);
	}

	template<typename T>
	template<typename T2>
	Array<T2> Array<T>::convert()
	{
		int size = rows * cols;
		Array<T2> arr(rows, cols);
		// copy data
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				arr(r, c) = (T2)(*this)(r, c);
			}
		}
		return arr;
	}

	template<typename T>
	void Array<T>::makePrivate()
	{
		if (data_ptr.use_count() == 1)
			return;
		Array<T> res = convert<T>();
		*this = res;
	}

	template<typename T>
	void Array<T>::resize(int nrows, int ncols)
	{
		makePrivate();
		if (data_ptr->size == nrows * ncols)
		{
			// data is reused
			start = 0;
			stride = ncols;
			rows = nrows;
			cols = ncols;
		}
		else
		{
			Array<T> res(nrows, ncols);
			*this = res;
		}
	}

	template<typename T>
	T Array<T>::sum()
	{
		T s = T(0);
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				s += (*this)(r, c);
			}
		}
		return s;
	}

	template<typename T>
	T Array<T>::squareSum()
	{
		T s = T(0);
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				T val = (*this)(r, c);
				s += val * val;
			}
		}
		return s;
	}

	template<typename T>
	T Array<T>::mean()
	{
		return sum() / (rows * cols);
	}

	template<typename T>
	T Array<T>::variance()
	{
		T m = mean();
		T var = T(0);
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				T val = (*this)(r, c);
				var += (val - m) * (val - m);
			}
		}
		return var;
	}

	template<typename T>
	void Array<T>::meanVar(T& mean, T& var)
	{
		T sum1 = T(0);
		T sum2 = T(0);
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				T val = (*this)(r, c);
				sum1 += val;
				sum2 += val * val;
			}
		}
		mean = sum1 / (rows * cols);
		var = sum2 / (rows * cols) - mean * mean;
	}

	template<typename T>
	Array<bool> Array<T>::threshold(T thresh, bool positive)
	{
		Array<bool> arr(rows, cols);
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				bool higher = (*this)(r, c) > thresh;
				if (higher == positive)
					arr(r, c) = true;
				else
					arr(r, c) = false;
			}
		}
		return arr;
	}

	template<typename T>
	void Array<T>::copyMetaDataFrom(const Array<T>& array)
	{
		data_ptr = array.data_ptr;
		start = array.start;
		stride = array.stride;
		rows = array.rows;
		cols = array.cols;
	}

	template<typename T>
	Array<T> Array<T>::operator+=(const Array<T>& array)
	{
		throw_assert(rows == array.rows && cols == array.cols, "Two arrays should have same shape");
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				(*this)(r, c) += array(r, c);
			}
		}
		return *this;
	}

	template<typename T>
	Array<T> Array<T>::operator-=(const Array<T>& array)
	{
		throw_assert(rows == array.rows && cols == array.cols, "Two arrays should have same shape");
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				(*this)(r, c) -= array(r, c);
			}
		}
		return *this;
	}

	template<typename T>
	Array<T> Array<T>::operator*=(const Array<T>& array)
	{
		throw_assert(rows == array.rows && cols == array.cols, "Two arrays should have same shape");
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				(*this)(r, c) *= array(r, c);
			}
		}
		return *this;
	}

	template<typename T>
	Array<T> Array<T>::operator*=(T val)
	{
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				(*this)(r, c) *= val;
			}
		}
		return *this;
	}

	template<typename T>
	Array<T> Array<T>::operator/=(T val)
	{
		throw_assert(val != 0, "divisor should not be 0");
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				(*this)(r, c) /= val;
			}
		}
		return *this;
	}

	template<typename T>
	void Array<T>::shuffle(const std::vector<int>& data)
	{
		throw_assert(data.size() == rows, "Dimension should match");
		Array<T> temp(rows, cols);
		for (size_t k = 0; k < data.size(); ++k)
		{
			int index = data[k];
			temp.row(int(k)).copyDataFrom(row(index));
		}
		copyDataFrom(temp);
	}

	// global functions
	// operator overloading
	template<typename T>
	inline Array<T> operator+(const Array<T>& arr1, const Array<T>& arr2)
	{
		Array<T> res(arr1);
		return res += arr2;
	}

	template<typename T>
	inline Array<T> operator-(const Array<T>& arr1, const Array<T>& arr2)
	{
		Array<T> res(arr1);
		return res -= arr2;
	}

	template<typename T>
	inline Array<T> operator*(const Array<T>& arr1, const Array<T>& arr2)
	{
		Array<T> res(arr1);
		return res *= arr2;
	}

	template<typename T>
	inline Array<T> operator*(const Array<T>& arr, T val)
	{
		Array<T> res(arr);
		return arr *= val;
	}

	template<typename T>
	inline Array<T> operator*(T val, const Array<T>& arr)
	{
		Array<T> res(arr);
		return arr *= val;
	}

	template<typename T>
	inline Array<T> operator/(const Array<T>& arr, T val)
	{
		Array<T> res(arr);
		return arr /= val;
	}

	template<typename T>
	inline float dot(const Array<T>& arr1, const Array<T>& arr2)
	{
		throw_assert(arr1.rows == 1 && arr2.rows == 1, "Dot only meaningful for 1d arrays");
		throw_assert(arr1.cols == arr2.cols, "input arrays should have same size");
		float sum = 0;
		for (int i = 0; i < arr1.cols; ++i)
			sum += arr1[i] * arr2[i];
		return sum;
	}

	template<typename T>
	inline Array<T> matrixMul(const Array<T>& arr1, const Array<T>& arr2)
	{
		throw_assert(arr1.cols == arr2.rows, "Dimensions should match");
		int N = arr1.rows;
		int M = arr2.cols;
		int K = arr1.cols;
		Array<T> result(N, M);
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				T sum = 0;
				for (int k = 0; k < K; ++k)
				{
					sum += arr1(i, k) * arr2(k, j);
				}
				result(i, j) = sum;
			}
		}
		return result;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Array<T>& array)
	{
		for (int r = 0; r < array.rows; ++r)
		{
			for (int c = 0; c < array.cols; ++c)
				os << array(r, c) << ", ";
			os << "\n";
		}
		return os;
	}
}

#endif
