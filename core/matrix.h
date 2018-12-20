/* 2d data container */
#ifndef DARKML_MATRIX_H
#define DARKML_MATRIX_H

// low rank matrices
template<typename T, int Rows, int Cols>
struct Matrix
{
	T data[Rows][Cols];
	Matrix(T fill_value = 0);
	Matrix(std::vector<T>& diag);

public:
	T& operator()(int r, int c) { return data[r][c]; }
	const T& operator()(int r, int c) const { return data[r][c]; }

	T determinant() const;

	// matrix operations
	Matrix<T, Rows, Cols> operator+=(T val);
	Matrix<T, Rows, Cols> operator-=(T val);
	Matrix<T, Rows, Cols> operator+=(const Matrix<T, Rows, Cols>& matrix);
	Matrix<T, Rows, Cols> operator-=(const Matrix<T, Rows, Cols>& matrix);
	
	Matrix<T, Rows, Cols> operator*=(T val);
	Matrix<T, Rows, Cols> operator/=(T val);
};

typedef Matrix<float, 2, 2> Matrixf22;
typedef Matrix<float, 3, 3> Matrixf33;
typedef Matrix<float, 4, 4> Matrixf44;
typedef Matrix<float, 3, 4> Matrixf34;

template<typename T, int R, int K, int C>
Matrix<T, R, C> operator*(const Matrix<T, R, K>& matrix1, const Matrix<T, K, C>& matrix2);

// matrix implementation
template<typename T, int Rows, int Cols>
Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator+=(T val)
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

template<typename T, int Rows, int Cols>
Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator-=(T val)
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

#endif
