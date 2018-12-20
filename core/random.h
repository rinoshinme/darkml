#ifndef DARKML_RANDOM_H
#define DARKML_RANDOM_H

#include "array.h"
#include <ctime>
#include <algorithm>

#define _USE_MATH_DEFINES
#include <math.h>
// why #include <cmath> does not work for M_PI?

namespace darkml
{
	// random number generator
	class Random
	{
	private:
		unsigned int min_val;
		unsigned int max_val;

	public:
		Random()
		{
			// use current time as seed
			time_t t;
			time(&t);
			srand(static_cast<unsigned int>(t));
			min_val = 0;
			max_val = RAND_MAX;
		}

		Random(int seed)
		{
			srand(seed);
			min_val = 0;
			max_val = RAND_MAX;
		}

		// uniform distribution
		int randomI(int low = 0, int high = 1)
		{
			return low + rand() % (high - low + 1);
		}
		
		template<typename T>
		T randomF(T low = T(0), T high = T(1))
		{
			return low + rand() * (high - low) / (max_val - min_val);
		}

		// other distributions
		template<typename T>
		T randomGaussian(T mu = 0, T sigma = 1)
		{
			// using box-muller algorithm
			T u = randomF<T>();
			T v = randomF<T>();
			T z = sqrt(-2 * log(u)) * cos(2 * T(M_PI) * v);
			return mu + sigma * z;
		}

		template<typename T>
		int randomBernoulli(T p = T(0.5))
		{
			T u = randomF<T>();
			if (u < p)
				return 1;
			else
				return 0;
		}



		// permutation of [low ... high - 1]
		std::vector<int> randomPermute(int low, int high)
		{
			std::vector<int> vec(high - low);
			for (size_t k = 0; k < vec.size(); ++k)
				vec[k] = low + int(k);
			std::random_shuffle(vec.begin(), vec.end());
			return vec;
		}
	};
}

#endif
