#ifndef DARKML_STAT_H
#define DARKML_STAT_H

/* statistics functions */
#include "array.h"
#include <random>

namespace darkml
{
	// each row in Array represents a sample vector
	
	template<typename T>
	Array<T> featureMean(const Array<T>& xs)
	{
		Array<T> m(1, xs.cols);
		for (int i = 0; i < xs.rows; ++i)
			m += xs.row(i);
		return m / (xs.rows);
	}

	template<typename T>
	Array<T> featureVariance(const Array<T>& x, const Array<T>& mean_x = Array<T>())
	{
		Array<T> m;
		if (mean_x.empty())
			m = mean(x);
		else
			m = mean_x;

		Array<T> m2(1, x.cols);
		// calculate variance
		for (int r = 0; r < x.rows; ++r)
		{
			for (int c = 0; c < x.cols; ++c)
			{
				m2[c] += x(r, c) * x(r, c);
			}
		}

		Array<T> var(1, x.cols);
		for (int i = 0; i < x.cols; ++i)
			var[i] = m2[i] - m[i] * m[i];
		return var;
	}

	template<typename T>
	Array<T> sampleWithReplacement(const Array<T>& x, int n)
	{
		Array<T> result(n, x.cols);
		int num_samples = x.rows;
		Random rng;
		for (int i = 0; i < n; ++i)
		{
			int idx = rng.randomI(0, num_samples - 1);
			result.row(i).copyDataFrom(x.row(idx));
		}
		return result;
	}

	template<typename T>
	Array<T> sampleWithoutReplacement(const Array<T>& x, int n)
	{
		throw_assert(x.rows >= n, "total number of samples should be larger than n");
		Random rng;
		std::vector<int> indices = rng.randomPermute(0, x.rows - 1);
		Array<T> x1(n, x.cols);
		for (int i = 0; i < n; ++i)
			x1.row(i).copyDataFrom(x.row(indices[i]));
		return x1;
	}

	template<typename T>
	Array<T> bootstrapSampling(const Array<T>& data)
	{
		int n = data.rows;
		return sampleWithReplacement(data, n);
	}

	inline int nearestInteger(float v)
	{
		float d = v - floor(v);
		if (d < 0.5f)
			return int(v);
		else
			return int(v + 1);
	}

}


#endif
