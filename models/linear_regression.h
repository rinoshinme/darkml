#ifndef DARKML_LINEAR_REGRESSION_H
#define DARKML_LINEAR_REGRESSION_H

#include "estimator.h"

namespace darkml
{
	/*
	 * data shape:		num_samples x num_features_input
	 * label shape:		num_samples x num_features_output
	 * weight shape:	num_input x num_output
	 * bias shape:		1 x num_output
	 * y = xw+b
	 */
	class LinearRegression : public Estimator<float>
	{
	public:
		Array<float> weight;
		Array<float> bias;
		float learn_rate_weight;
		float learn_rate_bias;

	public:
		LinearRegression(int epochs = 1);
		LinearRegression(int epochs, float lr_w, float lr_b);
		~LinearRegression() {}

		virtual void train(Dataset<float>& dataset);
		virtual Array<float> predict(const Array<float>& x);
		virtual float loss(const Dataset<float>& dataset);

	protected:
		virtual void trainEpoch(Dataset<float>& dataset);
		virtual void trainBatch(const Array<float>& x, const Array<float>& y);
		virtual void initWeightAndBias(int num_input, int num_output);
	};
}

#endif
