#ifndef DARKML_GEOMETYR_H
#define DARKML_GEOMETRY_H

#include "matrix.h"

namespace darkml
{
	Matrix22f getRotationMatrix2(float a);

	Matrix33f getRotationMatrixX(float a);
	Matrix33f getRotationMatrixY(float a);
	Matrix33f getRotationMatrixZ(float a);
	Matrix33f getRotationMatrix3(float alpha, float beta, float gamma);

}

#endif
