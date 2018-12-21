#include "geometry.h"
#include <cmath>

namespace darkml
{
	Matrix22f getRotationMatrix2(float a)
	{
		Matrix22f mat;
		float cosa = std::cos(a);
		float sina = std::sin(a);
		mat(0, 0) = cosa;
		mat(0, 1) = -sina;
		mat(1, 0) = sina;
		mat(1, 1) = cosa;
		return mat;
	}

	Matrix33f getRotationMatrixX(float a)
	{
		Matrix33f mat;
		float cosa = std::cos(a);
		float sina = std::sin(a);

		mat(0, 0) = 1.0f;
		mat(1, 1) = cosa;
		mat(1, 2) = sina;
		mat(2, 1) = -sina;
		mat(2, 2) = cosa;
		return mat;
	}

	Matrix33f getRotationMatrix3(float alpha, float beta, float gamma)
	{
		return Matrix33f();
	}

}
