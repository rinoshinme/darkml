#ifndef DARKML_STAT_H
#define DARKML_STAT_H

/* statistics functions */
#include "array.h"

namespace darkml
{
	// each row in Array represents a sample vector
	
	template<typename T>
	Array<T> mean(const Array<T>& xs);
	template<typename T>
	Array<T> covarianceMatrixUnbiased(const Array<T>& x);

	template<typename T>
	Array<T> sampleWithReplacement(const Array<T>& x, int n);
	template<typename T>
	Array<T> sampleWithoutReplacement(const Array<T>& x, int n);
	template<typename T>
	Array<T> bootstrapSampling(const Array<T>& data);

	inline int nearestInteger(float v)
	{
		float d = v - floor(v);
		if (d < 0.5f)
			return int(v);
		else
			return int(v + 1);
	}

}


#endif
