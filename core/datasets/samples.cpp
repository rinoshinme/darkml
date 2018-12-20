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
}
