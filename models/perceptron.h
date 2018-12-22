#ifndef DARKML_PERCEPTRON_H
#define DARKML_PERCEPTRON_H

#include "estimator.h"

namespace darkml
{
	template<typename T>
	class Perceptron : public Estimator < T >
	{
	private:
		Array<T> weights;
		Array<T> bias;

	public:
		void train(const Dataset& dataset);
		Array<T> predict(const Array<T>& data);
		T loss(const Dataset<T>& dataset);
	};
}

#endif
