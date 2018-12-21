/*
 * preprocessing functionalities
 */
#ifndef DARKML_PREPROCESSING_H
#define DARKML_PREPROCESSING_H

#include "array.h"
#include "stat.h"

namespace darkml
{
	// normalization, T == float or double
	template<typename T>
	Array<T> normalize(const Array<T>& data)
	{
		Array<T> mean = featureMean(data);
		Array<T> var = featureVariance(data, mean);
		Array<T> sigma(var.shape());
		for (int i = 0; i < data.cols; ++i)
			sigma[i] = sqrt(var[i]);

		Array<T> norm(data.shape());
		for (int r = 0; r < data.rows; ++r)
		{
			for (int c = 0; c < data.cols; ++c)
				norm(r, c) = (data(r, c) - mean[c]) / sigma[c];
		}
		return norm;
	}

}

#endif
