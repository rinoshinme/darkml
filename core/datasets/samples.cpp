#include "samples.h"
#include "../random.h"

namespace darkml
{
	Dataset<float> generateSampleRegression(int num_samples)
	{
		Dataset<float> dataset;
		dataset.data.resize(num_samples, 3);
		dataset.target.resize(num_samples, 2);

		Random rng;

		for (int i = 0; i < num_samples; ++i)
		{
			Array<float> row_x = dataset.data.row(i);
			Array<float> row_y = dataset.target.row(i);

			for (int j = 0; j < 3; ++j)
				row_x[j] = rng.randomF<float>();

			row_y[0] = 1 + 2 * row_x[0] + 3 * row_x[1] + 2 * row_x[2] + rng.randomF<float>(0, 0.5);
			row_y[1] = 2 + 3 * row_x[0] - 5 * row_x[1] + 4 * row_x[2] + rng.randomF<float>();
		}
		return dataset;
	}

	Dataset<float> generateGaussianMixture(const std::vector<std::pair<float, float> >& mu, const std::vector<float>& sigma, const std::vector<int>& nums)
	{
		size_t num_mu = mu.size();
		size_t num_sigma = sigma.size();
		size_t num_nums = nums.size();
		throw_assert(num_mu == num_sigma && num_mu == num_nums, "size equal to number of classes");

		int total_number = 0;
		for (size_t k = 0; k < nums.size(); ++k)
			total_number += nums[k];

		Dataset<float> dataset;
		dataset.data.resize(total_number, 2);
		dataset.target.resize(total_number, 1);

		Random rng;
		int index = 0;
		for (size_t k = 0; k < nums.size(); ++k)
		{
			float mu_x = mu[k].first;
			float mu_y = mu[k].second;
			float s = sigma[k];
			for (int i = 0; i < nums[k]; ++i)
			{
				dataset.data(index, 0) = rng.randomGaussian<float>(mu_x, s);
				dataset.data(index, 1) = rng.randomGaussian<float>(mu_y, s);
				dataset.target[index] = static_cast<float>(k);
				index += 1;
			}
		}
		dataset.shuffle();
		return dataset;
	}


}
