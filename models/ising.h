#ifndef DARKML_ISING_H
#define DARKML_ISING_H

#include "../core/array.h"

namespace darkml
{
	// ising model simulation using simulated annealing
	// both stochastic and deterministic algorithms shoudl be implemented.
	class IsingModel
	{
	private:
		Array<int> states;
		float temperature;
		float energy;

	public:
		IsingModel(int nrows, int ncols);

		void updateSingle();

	private:

	};
}

#endif
