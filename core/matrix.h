/* 2d data container */
#ifndef DARKML_MATRIX_H
#define DARKML_MATRIX_H

#include <vector>

// low rank matrices
template<typename T, size_t Rows = 1, size_t Cols = 1>
struct Matrix
{
	T data[Rows][Cols];
	Matrix(T fill_value = 0);
	Matrix(std::vector<T>& diag);

	T& operator()(int r, int c) { return data[r][c]; }
	const T& operator()(int r, int c) const { return data[r][c]; }

	T determinant() const;

	// matrix operations
	Matrix<T, Rows, Cols>& operator+=(T val);
	Matrix<T, Rows, Cols>& operator-=(T val);
	Matrix<T, Rows, Cols>& operator+=(const Matrix<T, Rows, Cols>& matrix);
	Matrix<T, Rows, Cols>& operator-=(const Matrix<T, Rows, Cols>& matrix);
	
	Matrix<T, Rows, Cols>& operator*=(T val);
	Matrix<T, Rows, Cols>& operator/=(T val);
};

template<typename T, size_t N>
using Vec = Matrix<T, N, 1>;
template<typename T, size_t N>
using TVec = Matrix<T, 1, N>;

typedef Matrix<float, 2, 2> Matrix22f;
typedef Matrix<float, 3, 3> Matrix33f;
typedef Matrix<float, 4, 4> Matrix44f;
typedef Matrix<float, 3, 4> Matrix34f;

typedef Matrix<float, 2, 1> Vec2f;
typedef Matrix<float, 3, 1> Vec3f;
typedef Matrix<float, 4, 1> Vec4f;

typedef Matrix<float, 1, 2> TVec2f;
typedef Matrix<float, 1, 3> TVec3f;
typedef Matrix<float, 1, 4> TVec4f;

template<typename T, size_t R, size_t K, size_t C>
Matrix<T, R, C> operator*(const Matrix<T, R, K>& matrix1, const Matrix<T, K, C>& matrix2);

//////////////////////////////////////////////////////////////////////////
// matrix implementation
//////////////////////////////////////////////////////////////////////////
template<typename T, size_t Rows = 1, size_t Cols = 1>
Matrix<T, Rows, Cols>::Matrix(T fill_value)
{
	for (int r = 0; r < Rows; ++r)
	{
		for (int c = 0; c < Cols; ++c)
		{
			data[r][c] = fill_value;
		}
	}
}

template<typename T, size_t Rows = 1, size_t Cols = 1>
Matrix<T, Rows, Cols>::Matrix(std::vector<T>& diag)
{
	int size = int(diag.size());
	for (int r = 0; r < Rows; ++r)
		memset(data[r], 0, Cols * sizeof(T));
	for (int i = 0; i < Rows && i < Cols && i < size; ++i)
		data[i][i] = diag[i];
}

template<typename T, size_t Rows = 1, size_t Cols = 1>
Matrix<T, Rows, Cols>& Matrix<T, Rows, Cols>::operator+=(T val)
{
	for (int r = 0; r < Rows; ++r)
	{
		for (int c = 0; c < Cols; ++c)
		{
			data[r][c] += val;
		}
	}
	return *this;
}

template<typename T, size_t Rows = 1, size_t Cols = 1>
Matrix<T, Rows, Cols>& Matrix<T, Rows, Cols>::operator-=(T val)
{
	for (int r = 0; r < Rows; ++r)
	{
		for (int c = 0; c < Cols; ++c)
		{
			data[r][c] -= val;
		}
	}
	return *this;
}

template<typename T, size_t Rows = 1, size_t Cols = 1>
Matrix<T, Rows, Cols>& Matrix<T, Rows, Cols>::operator+=(const Matrix<T, Rows, Cols>& matrix)
{
	for (int r = 0; r < Rows; ++r)
	{
		for (int c = 0; c < Cols; ++c)
		{
			data[r][c] += matrix.data[r][c];
		}
	}
	return *this;
}

template<typename T, size_t Rows = 1, size_t Cols = 1>
Matrix<T, Rows, Cols>& Matrix<T, Rows, Cols>::operator-=(const Matrix<T, Rows, Cols>& matrix)
{
	for (int r = 0; r < Rows; ++r)
	{
		for (int c = 0; c < Cols; ++c)
		{
			data[r][c] -= matrix.data[r][c];
		}
	}
	return *this;
}

template<typename T, size_t Rows = 1, size_t Cols = 1>
Matrix<T, Rows, Cols>& Matrix<T, Rows, Cols>::operator*=(T val)
{
	for (int r = 0; r < Rows; ++r)
	{
		for (int c = 0; c < Cols; ++c)
		{
			data[r][c] *= val;
		}
	}
	return *this;
}

template<typename T, size_t Rows = 1, size_t Cols = 1>
Matrix<T, Rows, Cols>& Matrix<T, Rows, Cols>::operator/=(T val)
{
	for (int r = 0; r < Rows; ++r)
	{
		for (int c = 0; c < Cols; ++c)
		{
			data[r][c] /= val;
		}
	}
	return *this;
}

template<typename T, size_t R = 1, size_t K, size_t C>
Matrix<T, R, C> operator*(const Matrix<T, R, K>& matrix1, const Matrix<T, K, C>& matrix2)
{
	Matrix<T, R, C> result;
	for (int r = 0; r < R; ++r)
	{
		for (int c = 0; c < C; ++c)
		{
			T sum = 0;
			for (int k = 0; k < K; ++k)
				sum += matrix1(r, k) * matrix2(k, c);
			result(r, c) = sum;
		}
	}
	return result;
}

#endif
