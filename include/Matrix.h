#ifndef __MATRIX__
#define __MATRIX__

#include <stdbool.h>
#include "Tuple.h"

typedef struct MatrixStruct * Matrix;

Matrix Matrix_Create(int rows, int columns);
void Matrix_Destroy(Matrix * matrixPtr);
void Matrix_SetValue(Matrix matrix, int row, int column, float value);
float Matrix_ValueAt(Matrix matrix, int row, int column);
int Matrix_GetRows(Matrix matrix);
int Matrix_GetColumns(Matrix matrix);
bool Matrix_Equals(Matrix matrix1, Matrix matrix2);
void Matrix_Assign(Matrix * lhsPtr, Matrix * rhsPtr);
void Matrix_Copy(Matrix destination, Matrix source);
Matrix Matrix_Multiply(Matrix matrix1, Matrix matrix2);
Tuple Matrix_MultiplyTuple(Matrix matrix, Tuple tuple);
Matrix Matrix_Identity(int dimension);
Matrix Matrix_Transpose(Matrix matrix);
Matrix Matrix_Submatrix(Matrix matrix, int row, int column);
float Matrix_Determinant(Matrix matrix);
float Matrix_Minor(Matrix matrix, int row, int column);
float Matrix_Cofactor(Matrix matrix, int row, int column);
Matrix Matrix_Inverse(Matrix matrix);

#endif /* __MATRIX__ */
