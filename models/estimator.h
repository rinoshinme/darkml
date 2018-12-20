#ifndef DARKML_ESTIMATOR_H
#define DARKML_ESTIMATOR_H

#include "../core/array.h"
#include "../core/throw_assert.h"
#include "../core/datasets/dataset.h"

namespace darkml
{
	/*
	 * API interface is different from 
	 */
	template<typename T>
	class Estimator
	{
	protected:
		// training epochs
		int num_epochs;

	public:
		Estimator(int epochs = 1) { num_epochs = epochs; }
		virtual ~Estimator() {}

	public:
		// train on dataset
		virtual void train(const Dataset<T>& dataset) {}
		// predict results on given data
		virtual Array<T> predict(const Array<T>& data) { return data; }
		// calculate loss on testset
		virtual T loss(const Dataset<T>& dataset) { return 0; }
		// parameter initialization
		// virtual void initParams() { /* possible parameters initialized */ }

	private:
		virtual void trainEpoch(Dataset<T>& dataset) {}
		virtual void trainBatch(const Array<T>& x, const Array<T>& y) {}
	};
}

#endif
