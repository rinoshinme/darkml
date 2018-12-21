#ifndef DARKML_LOGISTIC_REGRESSION_H
#define DARKML_LOGISTIC_REGRESSION_H

#include "linear_regression.h"

namespace darkml
{
	// binary classifier, target values should be either 1 or 0
	class LogisticRegression : public LinearRegression
	{
	public:
		LogisticRegression(int epochs);
		LogisticRegression(int epochs, float lr_w, float lr_b);
		~LogisticRegression() {}

		void train(Dataset<float>& dataset);
		Array<float> predict(const Array<float>& x);

		float loss(const Dataset<float>& dataset);
		float accuracy(const Dataset<float>& dataset);
	private:
		void trainEpoch(Dataset<float>& dataset);
		void trainBatch(const Array<float>& x, const Array<float>& y);
		void initWeightAndBias(int num_input, int num_output);
	};
}

#endif
