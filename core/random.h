#ifndef DARKML_RANDOM_H
#define DARKML_RANDOM_H

#include "array.h"
#include <ctime>
#include <algorithm>

#define _USE_MATH_DEFINES
#include <math.h>
// why #include <cmath> does not work for M_PI?

// #define CPP0x

#ifdef CPP0x
#include <random>
#include <chrono>
#endif

namespace darkml
{
	// random number generator
	// should be implemented as Singleton
	class Random
	{
	private:
		unsigned int min_val;
		unsigned int max_val;
#ifdef CPP0x
		std::default_random_engine engine;
#endif

	public:
		Random()
		{
#ifndef CPP0x
			// use current time as seed
			time_t t;
			time(&t);
			srand(static_cast<unsigned int>(t));
			min_val = 0;
			max_val = RAND_MAX;
#else
			engine.seed(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
			min_val = engine.min();
			max_val = engine.max();
#endif
		}

		Random(int seed)
		{
#ifndef CPP0x
			srand(seed);
			min_val = 0;
			max_val = RAND_MAX;
#else
			min_val = engine.min();
			max_val = engine.max();
			engine.seed(seed);
#endif
		}

		// uniform distribution
		int randomI(int low = 0, int high = 1)
		{
			auto r = getRandomInt();
			return low + r % (high - low + 1);
		}
		
		template<typename T>
		T randomF(T low = T(0), T high = T(1))
		{
			auto r = getRandomInt();
			return low + r * (high - low) / (max_val - min_val);
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

	private:
		inline unsigned int getRandomInt()
		{
#ifndef CPP0x
			return rand();
#else
			return engine();
#endif
		}
	};
}

#endif
