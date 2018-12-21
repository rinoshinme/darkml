#include "logistic_regression.h"
#include "../core/math.h"
#include "../core/weight_init.h"

namespace darkml
{
	LogisticRegression::LogisticRegression(int epochs)
		: LinearRegression(epochs) {}

	LogisticRegression::LogisticRegression(int epochs, float lr_w, float lr_b)
		: LinearRegression(epochs, lr_w, lr_b) {}

	void LogisticRegression::train(Dataset<float>& dataset)
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
			dataset.shuffle();
		}
	}

	void LogisticRegression::trainEpoch(Dataset<float>& dataset)
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

	Array<float> LogisticRegression::predict(const Array<float>& x)
	{
		int num_samples = x.rows;
		int num_output = weight.cols;
		throw_assert(num_output == 1, "number of output should be 1 for logistic regression");
		Array<float> result(num_samples, num_output);
		for (int i = 0; i < num_samples; ++i)
		{
			Array<float> mul = matrixMul(x.row(i), weight);
			float activation = mul(0, 0) + bias(0, 0);
			result[i] = sigmoid(activation);
		}
		return result;
	}

	float LogisticRegression::loss(const Dataset<float>& dataset)
	{
		Array<float> pred = predict(dataset.data);
		Array<float> target = dataset.target;
		float loss_value = 0.0f;
		for (int i = 0; i < pred.rows; ++i)
		{
			loss_value += target[i] * std::log(pred[i]) + (1 - target[i]) * std::log(1 - pred[i]);
		}
		return loss_value;
	}

	float LogisticRegression::accuracy(const Dataset<float>& dataset)
	{
		if (dataset.data.rows == 0)
			return 0;
		throw_assert(dataset.data.rows == dataset.target.rows, "unmatched dataset");
		Array<float> pred = predict(dataset.data);
		Array<float> target = dataset.target;

		int num_correct = 0;
		for (int i = 0; i < pred.rows; ++i)
		{
			if (pred[i] > 0.5 && target[i] > 0.5)
				num_correct += 1;
			else if (pred[i] < 0.5 && target[i] < 0.5)
				num_correct += 1;
		}
		return num_correct * 1.0f / pred.rows;
	}

	void LogisticRegression::trainBatch(const Array<float>& x, const Array<float>& y)
	{
		Array<float> pred = predict(x);
		Array<float> error = pred - y;
		// std::cout << error << std::endl;
		int num_input = x.cols;
		int num_samples = x.rows;
		float lr_weight = learn_rate_weight / num_samples;
		float lr_bias = learn_rate_bias / num_samples;
		for (int n = 0; n < num_samples; ++n)
		{
			// update weight
			for (int i = 0; i < num_input; ++i)
			{
				weight[i] -= lr_weight * x(n, i) * error[n];
			}
			// update bias
			bias(0, 0) -= lr_bias * error[n];
		}
	}

	void LogisticRegression::initWeightAndBias(int num_input, int num_output)
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
