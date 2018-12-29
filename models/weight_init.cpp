#include "weight_init.h"
#include "../core/random.h"

namespace darkml
{
	void zeroInit(Array<float>& array)
	{
		for (int r = 0; r < array.rows; ++r)
		{
			for (int c = 0; c < array.cols; ++c)
			{
				array(r, c) = 0.0f;
			}
		}
	}

	void constantInit(Array<float>& array, float val)
	{
		for (int r = 0; r < array.rows; ++r)
		{
			for (int c = 0; c < array.cols; ++c)
			{
				array(r, c) = val;
			}
		}
	}

	void gaussianInit(Array<float>& array, float mu, float sigma)
	{
		Random rng;
		for (int r = 0; r < array.rows; ++r)
		{
			for (int c = 0; c < array.cols; ++c)
			{
				array(r, c) = rng.randomGaussian<float>(mu, sigma);
			}
		}
	}
}
