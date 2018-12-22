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
	Array<T> onehotEncoding(const Array<T>& data, int num_classes = -1);

	// base class for array pre-processing functions, input and output arrays have same data type.
	template<typename T>
	class ArrayProcessor
	{
	public:
		ArrayProcessor() { /* no operations */ }
		// process given array, calculate internal states if needed
		virtual Array<T> operator()(const Array<T>& array) { return array; }
		// apply processing function on more arrays, using calculated internal states
		virtual Array<T> apply(const Array<T>& array) { return array; }
		// update internal states
		// virtual void update(const Array<T>& array) {}
	};

	template<typename T>
	class Normalizer : public ArrayProcessor<T>
	{
	private:
		Array<T> mean;
		Array<T> sigma;
		int num_features;

	public:
		Normalizer() : ArrayProcessor() { num_features = -1; }
		Array<T> operator()(const Array<T>& array)
		{
			num_features = array.cols;
			mean = featureMean(array);
			Array<T> var = featureVariance(array);
			sigma.resize(var.shape());
			for (int i = 0; i < var.length(); ++i)
				sigma[i] = sqrt(var[i]);

			return process(array);
		}

		Array<T> apply(const Array<T>& array)
		{
			if (num_features == -1 || num_features != array.cols)
				return (*this)(array);
			return process(array);
		}
	private:
		Array<T> process(const Array<T>& array)
		{
			Array<T> norm(array.shape());
			for (int r = 0; r < array.rows; ++r)
			{
				for (int c = 0; c < array.cols; ++c)
					norm(r, c) = (array(r, c) - mean[c]) / sigma[c];
			}
			return norm;
		}
	};

	template<typename T>
	class FeatureScaler : public ArrayProcessor < T >
	{
	private:
		std::vector<float> scales;
	public:
		FeatureScaler(const std::vector<float>& s) : ArrayProcessor() { scales = s; }
		Array<T> operator()(const Array<T>& array) { return apply(array); }
		Array<T> apply(const Array<T>& array)
		{
			throw_assert(data.cols == scales.size(), "feature number does not match");
			Array<T> data2(data.shape());
			for (int c = 0; c < data.cols; ++c)
				data2.col(c).copyDataFrom(data.col(c) * scales[c]);
			return data2;
		}
	};

	template<typename T>
	class MeanSubtractor : public ArrayProcessor<T>
	{
	private:
		Array<T> mean;
	public:
		MeanSubtractor() : ArrayProcessor() {}
		Array<T> operator()(const Array<T>& array)
		{
			mean = featureMean(array);
			return process(array);
		}

		Array<T> apply(const Array<T>& array)
		{
			if (array.cols != mean.cols)
				return (*this)(array);
			return process(array);
		}

	private:
		Array<T> process(const Array<T>& array)
		{
			Array<T> arr2(array.shape());
			for (int r = 0; r < array.rows; ++r)
				arr2.row(r).copyDataFrom(array.row(r) - mean);
			return arr2;
		}
	};

	template<typename T>
	class Binarizer : public ArrayProcessor < T >
	{
	private:
		std::vector<T> feature_thresholds;
	public:
		Binarizer(T thresh) : ArrayProcessor() { feature_thresholds.push_back(thresh); }
		Binarizer(const std::vector<T>& thresholds) : ArrayProcessor() { feature_thresholds = thresholds; }
		Array<T> operator()(const Array<T>& array) { return process(array); }
		Array<T> apply(const Array<T>& array) { return process(array); }
	private:
		Array<T> process(const Array<T>& array)
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
	};

	template<typename T>
	class OnehotEncoder : public ArrayProcessor < T >
	{
	private:
		int num_classes;
	public:
		OnehotEncoder(int nclassess = -1) : ArrayProcessor() { num_classes = nclassess; }
		Array<T> operator()(const Array<T>& array)
		{
			if (num_classes == -1)
				num_classes = getNumClasses(array);
			return process(array);
		}

		Array<T> apply(const Array<T>& array) { return process(array); }

	private:
		int getNumClasses(const Array<T>& array)
		{
			throw_assert(array.cols == 1, "input should have 1 column");
			int max_val = 0;
			for (int i = 0; i < array.length(); ++i)
			{
				int v = int(array[i]);
				if (v > max_val)
					max_val = v;
			}
			return max_val + 1;
		}

		Array<T> process(const Array<T>& array)
		{
			throw_assert(array.cols == 1, "input should have 1 column");
			Array<T> arr(array.rows, num_classes);
			zeroInit(arr, T(0));
			for (int i = 0; i < arr.rows; ++i)
			{
				int v = int(array[i]);
				if (v >= 0 && v < num_classes)
					arr(i, v) = T(1);
			}
			return arr;
		}
	};

	//////////////////////////////////////////////////////////////////////////
	// function implementations
	//////////////////////////////////////////////////////////////////////////
	template<typename T>
	Array<T> normalize(const Array<T>& data)
	{
		/*
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
		*/
		Normalizer<T> normalizer;
		return normalizer(data);
	}

	template<typename T>
	Array<T> featureScaling(const Array<T>& data, const std::vector<T>& scales)
	{
		/*
		throw_assert(data.cols == scales.size(), "feature number does not match");
		Array<T> data2(data.shape());
		for (int c = 0; c < data.cols; ++c)
			data2.col(c).copyDataFrom(data.col(c) * scales[c]);
		return data2;
		*/
		FeatureScaler<T> scaler(scales);
		return scaler(data);
	}

	template<typename T>
	Array<T> meanSubtraction(const Array<T>& data)
	{
		/*
		Array<T> mean = featureMean(data);
		Array<T> data2(data.shape());
		for (int r = 0; r < data.rows; ++r)
			data2.row(r).copyDataFrom(data.row(r) - mean);
		return data2;
		*/
		MeanSubtractor<T> subtractor;
		return subtractor(data);
	}

	template<typename T>
	Array<T> binarization(const Array<T>& data, const std::vector<T>& feature_thresholds)
	{
		/*
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
		*/
		Binarizer<T> bin;
		return bin(data);
	}
	
	template<typename T>
	Array<T> onehotEncoding(const Array<T>& data, int num_classes)
	{
		OnehotEncoder<T> encoder(num_classes);
		return encoder(data);
	}

}

#endif
