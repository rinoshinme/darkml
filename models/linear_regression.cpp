#include "linear_regression.h"
#include "../core/weight_init.h"

namespace darkml
{
	LinearRegression::LinearRegression(int epochs)
	{
		num_epochs = epochs;
		learn_rate_weight = 0.1f;
		learn_rate_bias = 0.05f;
	}

	LinearRegression::LinearRegression(int epochs, float lr_w, float lr_b)
	{
		num_epochs = epochs;
		learn_rate_weight = lr_w;
		learn_rate_bias = lr_b;
	}

	void LinearRegression::train(Dataset<float>& dataset)
	{
		throw_assert(dataset.data.rows == dataset.target.rows, "data and target should have same number of rows");
		int num_samples = dataset.data.rows;
		int num_input = dataset.data.cols;
		int num_output = dataset.target.cols;
		
		initWeightAndBias(num_input, num_output);

		for (int i = 0; i < num_epochs; ++i)
		{
			trainEpoch(dataset);
			dataset.reset();
		}
	}

	void LinearRegression::trainEpoch(Dataset<float>& dataset)
	{
		int num_batch = dataset.data.rows / dataset.batch_size;
		Array<float> batch_x;
		Array<float> batch_y;
		for (int i = 0; i < num_batch; ++i)
		{
			dataset.getBatch(batch_x, batch_y);
			trainBatch(batch_x, batch_y);
		}
	}

	void LinearRegression::trainBatch(const Array<float>& x, const Array<float>& y)
	{
		int num_samples = x.rows;
		Array<float> error = predict(x) - y;

		int num_input = weight.rows;
		int num_output = weight.cols;

		float lr_weight = learn_rate_weight / num_samples;
		float lr_bias = learn_rate_bias / num_samples;

		for (int n = 0; n < num_samples; ++n)
		{
			Array<float> error_n = error.row(n);
			Array<float> x_n = x.row(n);
			for (int j = 0; j < num_output; ++j)
			{
				// update weight
				for (int i = 0; i < num_input; ++i)
				{
					weight(i, j) -= lr_weight * error_n[j] * x_n[i];
				}
				// update bias
				bias[j] -= lr_bias * error_n[j];
			}
		}
	}

	Array<float> LinearRegression::predict(const Array<float>& x)
	{
		int num_samples = x.rows;
		int num_out = weight.cols;
		Array<float> result(num_samples, num_out);
		for (int i = 0; i < num_samples; ++i)
		{
			Array<float> mul = matrixMul(x.row(i), weight);
			result.row(i).copyDataFrom(mul + bias);
		}
		return result;
	}

	float LinearRegression::loss(const Dataset<float>& dataset)
	{
		throw_assert(dataset.data.rows == dataset.target.rows, "data should have same number of samples");

		int num_samples = dataset.data.rows;
		int num_input = dataset.data.cols;
		int num_output = dataset.target.cols;
		initWeightAndBias(num_input, num_output);

		Array<float> y_pred = predict(dataset.data);
		Array<float> diff = y_pred - dataset.target;
		float sum2 = diff.squareSum();
		return sum2 / (diff.rows);
	}

	void LinearRegression::initWeightAndBias(int num_input, int num_output)
	{
		if (weight.rows != num_input || weight.cols != num_output)
		{
			weight.resize(num_input, num_output);
			gaussianInit(weight, 0, 0.01f);
		}
			
		if (bias.rows != 1 || bias.cols != num_output)
		{
			bias.resize(1, num_output);
			constantInit(bias, 0.1f);
		}
	}
}

