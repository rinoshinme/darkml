#include "thresholder.h"
#include <vector>
#include <algorithm>

namespace darkml
{
	Thresholder::Thresholder(int attr_idx, bool positive)
	{
		this->attribute_index = attr_idx;
		this->positive = positive;
	}

	void Thresholder::fit(const Array<float>& x, const Array<float>& y)
	{
		throw_assert(x.rows == y.rows, "inputs x and y should have same number of samples");
		
		int num_samples = x.rows;
		std::vector<float> samples(num_samples);
		std::vector<int> labels(num_samples);
		for (int n = 0; n < num_samples; ++n)
		{
			samples[n] = x(n, attribute_index);
			labels[n] = int(y(n, 0));
		}

		// copy attributes
		std::vector<float> sorted_samples = samples;
		std::sort(sorted_samples.begin(), sorted_samples.end());

		// generate thresholds -> 1 thresh between each consective values
		std::vector<float> thresholds(sorted_samples.size() - 1);
		for (int i = 0; i < num_samples; ++i)
			thresholds[i] = (sorted_samples[i + 1] + sorted_samples[i]) / 2;

		// choose best threshold
		float best_accuracy = 0;
		float best_thresh = thresholds[0];
		for (size_t i = 0; i < thresholds.size(); ++i)
		{
			float thresh = thresholds[i];

			// calculate error on training data
			int num_correct = 0;
			int num_total = 0;
			for (int k = 0; k < num_samples; ++k)
			{
				bool b1 = samples[k] > threshold;
				bool b2 = labels[k] == (positive ? 1 : 0);
				if (b1 == b2)
					num_correct += 1;
				num_total += 1;
			}

			float acc = (num_correct)* 1.0f / num_total;
			if (acc > best_accuracy)
			{
				best_accuracy = acc;
				best_thresh = thresh;
			}
		}

		// final result
		threshold = best_thresh;
	}

	Array<float> Thresholder::predict(const Array<float>& x)
	{
		int num_samples = x.rows;
		Array<float> result(num_samples, 1);
		for (int i = 0; i < num_samples; ++i)
		{
			if (x(i, attribute_index) > threshold == positive)
				result(i, 0) = 1.0f;
			else
				result(i, 0) = 0.0f;
		}
		return result;
	}

}

