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
	Array<T> normalize(const Array<T>& data);
	// feature scaling
	template<typename T>
	Array<T> featureScaling(const Array<T>& data, const std::vector<T>& scales);
	// mean subtraction
	template<typename T>
	Array<T> meanSubtraction(const Array<T>& data);
	// binarization
	template<typename T>
	Array<T> binarization(const Array<T>& data, const std::vector<T>& feature_thresholds);
	// one-hot encoding
	template<typename T>
	Array<T> oneHotEncodint(const Array<T>& data, int num_classes = -1);

	//////////////////////////////////////////////////////////////////////////
	// implementations
	//////////////////////////////////////////////////////////////////////////
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

	template<typename T>
	Array<T> featureScaling(const Array<T>& data, const std::vector<T>& scales)
	{
		throw_assert(data.cols == scales.size(), "feature number does not match");
		Array<T> data2(data.shape());
		for (int c = 0; c < data.cols; ++c)
			data2.col(c).copyDataFrom(data.col(c) * scales[c]);
		return data2;
	}

	template<typename T>
	Array<T> meanSubtraction(const Array<T>& data)
	{
		Array<T> mean = featureMean(data);
		Array<T> data2(data.shape());
		for (int r = 0; r < data.rows; ++r)
			data2.row(r).copyDataFrom(data.row(r) - mean);
		return data2;
	}

	template<typename T>
	Array<T> binarization(const Array<T>& data, const std::vector<T>& feature_thresholds)
	{
		throw_assert(feature_thresholds.size() == 1 || feature_thresholds.size() == data.cols, "feature number does not match");
		Array<T> data2;
		if (feature_thresholds.size() == 1)
		{
			data2 = data - feature_thresholds[0];
		}
		else
		{
			data2.resize(data.rows, data.cols);
			for (int c = 0; c < data.cols; ++c)
				data2.col(c).copyDataFrom(data.col(c) - feature_thresholds[c]);
		}

		for (int r = 0; r < data2.rows; ++r)
		{
			for (int c = 0; c < data2.cols; ++c)
			{
				T val = data2(r, c);
				if (val > 0)
					data2(r, c) = T(1);
				else
					data2(r, c) = T(0);
			}
		}
		return data2;
		
	}
}

#endif
