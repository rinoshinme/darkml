#ifndef DARKML_GEOMETYR_H
#define DARKML_GEOMETRY_H

#include "matrix.h"

namespace darkml
{
	Matrixf22 getRotationMatrix2(float angle);
	Matrixf33 getRotationMatrix3(float angle_x, float angle_y, float angle_z);

}

#endif
