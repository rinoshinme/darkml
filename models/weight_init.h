#ifndef DARKML_WEIGHT_INIT_H
#define DARKML_WEIGHT_INIT_H

#include "../core/array.h"

namespace darkml
{
	// weight initialization
	void zeroInit(Array<float>& array);
	void constantInit(Array<float>& array, float val);
	void gaussianInit(Array<float>& array, float mu, float sigma);
	void XavierInit(Array<float>& array);
}

#endif
