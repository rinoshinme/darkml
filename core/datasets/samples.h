#ifndef DARKML_SAMPLES_H
#define DARKML_SAMPLES_H

#include "dataset.h"


namespace darkml
{
	/*
	* simple regression data
	* y1 = 1 + 2 * x1 + 3 * x2 + 2 * x3
	* y2 = 2 + 3 * x1 - 5 * x2 + 4 * x3
	*
	*/
	Dataset<float> generateSampleRegression(int num_samples);


}

#endif
