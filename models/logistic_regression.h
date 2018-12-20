#ifndef DARKML_LOGISTIC_REGRESSION_H
#define DARKML_LOGISTIC_REGRESSION_H

#include "estimator.h"

namespace darkml
{
	// binary classifier
	class LogisticRegression : public Estimator<float>
	{ 
	private:
		Array<float> weight;
		Array<float> bias;

	public:
		LogisticRegression();
		~LogisticRegression() {}

		void fit(const Array<float>& x, const Array<float>& y);


	};
}

#endif
