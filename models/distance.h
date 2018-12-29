#ifndef DARKML_DISTANCE_H
#define DARKML_DISTANCE_H

#include "../core/array.h"
#include <cmath>

namespace darkml
{
	template<typename T>
	class BaseDistance
	{
	public:
		BaseDistance() {}
		virtual ~BaseDistance() {}
		virtual T operator()(const Array<T>& a1, const Array<T>& a2)
		{
			throw_assert(a1.rows == a2.rows && a1.cols == a2.cols, "two arrays should have same shape");
			return 0;
		}
	};

	template<typename T>
	class EuclidDistance : public BaseDistance<T>
	{
	public:
		EuclidDistance() {}
		~EuclidDistance() {}

		T operator()(const Array<T>& a1, const Array<T>& a2)
		{
			throw_assert(a1.rows == a2.rows && a1.cols == a2.cols, "two inputs should have same shape");
			// pairse difference
			T sum = 0;
			for (int r = 0; r < a1.rows; ++r)
			{
				for (int c = 0; c < a1.cols; ++c)
				{
					T diff = a1(r, c) - a2(r, c);
					sum += diff * diff;
				}
			}
			return std::sqrt(sum);
		}
	};

	template<typename T>
	class L1Distance : public BaseDistance<T>
	{
	public:
		L1Distance() {}
		~L1Distance() {}
		T operator()(const Array<T>& a1, const Array<T>& a2)
		{
			throw_assert(a1.rows == a2.rows && a1.cols == a2.cols, "two inputs should have same shape");
			T max_diff = T(0);
			for (int r = 0; r < a1.rows; ++r)
			{
				for (int c = 0; c < a1.cols; ++c)
				{
					T diff = a1(r, c) - a2(r, c);
					if (diff > max_diff)
						max_diff = diff;
				}
			}
			return max_diff;
		}
	};

	// sum of distances in all element positions
	template<typename T>
	class ManhattanDistance : public BaseDistance < T >
	{
	public:
		ManhattanDistance() {}
		~ManhattanDistance() {}
		T operator()(const Array<T>& a1, const Array<T>& a2)
		{
			throw_assert(a1.rows == a2.rows && a1.cols == a2.cols, "two inputs should have same shape");
			T dist = 0;
			for (int r = 0; r < a1.rows; ++r)
			{
				for (int c = 0; c < a1.cols; ++c)
				{
					T diff = a1(r, c) - a2(r, c);
					dist += std::abs(diff);
				}
			}
			return dist;
		}
	};
}

#endif
