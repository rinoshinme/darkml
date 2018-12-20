#ifndef DARKML_THRESHOLDER_H
#define DARKML_THRESHOLDER_H

#include "estimator.h"

namespace darkml
{
	/* simplist algorithm for binary classifier */
	class Thresholder : public Estimator < float >
	{
	private:
		int attribute_index;
		// (y = 1 for x > threshold) if positive = true, else (y = 0 for x > threshold)
		bool positive;
		float threshold;

	public:
		Thresholder(int attr_idx, bool positive = true);

		void fit(const Array<float>& x, const Array<float>& y);
		Array<float> predict(const Array<float>&);
	};
}

#endif
