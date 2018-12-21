#ifndef DARKML_MATH_H
#define DARKML_MATH_H

#include <cmath>

namespace darkml
{
	inline int nearestInteger(float v)
	{
		float d = v - floor(v);
		if (d < 0.5f)
			return int(v);
		else
			return int(v + 1);
	}

	template<typename T>
	inline T sigmoid(T x)
	{
		return 1 / (1 + std::exp(-x));
	}

	template<typename T>
	inline T sigmoidGrad(T y)
	{
		return y * (1 - y);
	}

}

#endif
