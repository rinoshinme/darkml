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
		BaseDistance();
		virtual ~BaseDistance();

		virtual T operator()(const Array<T>& a1, const Array<T>& a2);
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
					sum += (a1(r, c) - a2(r, c));
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

}

#endif
