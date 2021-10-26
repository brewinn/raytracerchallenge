#ifndef __MATRIX__
#define __MATRIX__

#include <stdbool.h>
#include "Tuple.h"

typedef struct MatrixStruct * Matrix;

Matrix Matrix_Create(int rows, int columns);
void Matrix_Destroy(Matrix * matrixPtr);
void Matrix_SetValue(Matrix matrix, int row, int column, float value);
float Matrix_ValueAt(const Matrix matrix, int row, int column);
int Matrix_GetRows(const Matrix matrix);
int Matrix_GetColumns(const Matrix matrix);
bool Matrix_Equals(const Matrix matrix1, const Matrix matrix2);
void Matrix_Assign(Matrix * lhsPtr, Matrix * rhsPtr);
void Matrix_Transfer(Matrix destination, const Matrix source);
Matrix Matrix_Multiply(const Matrix matrix1, const Matrix matrix2);
Tuple Matrix_MultiplyTuple(const Matrix matrix, Tuple tuple);
Matrix Matrix_Identity(int dimension);
Matrix Matrix_Transpose(const Matrix matrix);
Matrix Matrix_Submatrix(const Matrix matrix, int row, int column);
float Matrix_Determinant(const Matrix matrix);
float Matrix_Minor(const Matrix matrix, int row, int column);
float Matrix_Cofactor(const Matrix matrix, int row, int column);
Matrix Matrix_Inverse(const Matrix matrix);

#endif /* __MATRIX__ */
