#include "Matrix.h"
#include "Utilities.h"
#include <stdlib.h>

typedef struct MatrixStruct {
  float **values;
  int nrows;
  int ncolumns;
} MatrixStruct;

Matrix Matrix_Create(int nrows, int ncolumns) {
  Matrix matrix = malloc(sizeof(MatrixStruct));
  matrix->nrows = nrows;
  matrix->ncolumns = ncolumns;
  matrix->values = (float **)calloc(nrows, sizeof(float *));
  for (int i = 0; i < nrows; i++)
    matrix->values[i] = (float *)calloc(ncolumns, sizeof(float));
  return matrix;
}

static void FreeMatrixValues(Matrix matrix) {
  int rows = matrix->nrows;
  for (int i = 0; i < rows; i++)
    free(matrix->values[i]);
  free(matrix->values);
}

void Matrix_Destroy(Matrix *matrixPtr) {
  if (matrixPtr == NULL || *matrixPtr == NULL)
    return;
  Matrix matrix = *matrixPtr;
  FreeMatrixValues(matrix);
  free(matrix);
  *matrixPtr = NULL;
}

static bool WithinMatrixBounds(Matrix matrix, int row, int column) {
  if (row < 0 || row > (matrix->nrows - 1)) {
    return false;
  }
  if (column < 0 || column > (matrix->ncolumns - 1)) {
    return false;
  }
  return true;
}

void Matrix_SetValue(Matrix matrix, int row, int column, float value) {
  if (!WithinMatrixBounds(matrix, row, column)) {
    /* Error message? */
    return;
  }
  matrix->values[row][column] = value;
}

float Matrix_ValueAt(const Matrix matrix, int row, int column) {
  if (!WithinMatrixBounds(matrix, row, column)) {
    /* Error message? */
    return -1;
  }
  return matrix->values[row][column];
}

int Matrix_GetRows(const Matrix matrix) { return matrix->nrows; }

int Matrix_GetColumns(const Matrix matrix) { return matrix->ncolumns; }

static bool CheckMatrixValuesEqual(Matrix matrix1, Matrix matrix2) {
  for (int i = 0; i < matrix1->nrows; i++) {
    for (int j = 0; j < matrix1->ncolumns; j++) {
      if (!floatsEqual(matrix1->values[i][j], matrix2->values[i][j]))
        return false;
    }
  }

  return true;
}

bool Matrix_Equals(const Matrix matrix1, const Matrix matrix2) {
  bool MatricesSameDimensions = (matrix1->nrows == matrix2->nrows) &
                                (matrix1->ncolumns == matrix2->ncolumns);

  if (!MatricesSameDimensions)
    return false;

  return CheckMatrixValuesEqual(matrix1, matrix2);
}

void Matrix_Assign(Matrix *lhsPtr, Matrix *rhsPtr) {
  Matrix_Destroy(lhsPtr);
  *lhsPtr = *rhsPtr;
  *rhsPtr = NULL;
}

void Matrix_Transfer(Matrix destination, const Matrix source) {
  FreeMatrixValues(destination);
  *destination = *source;
  free(source);
}

static Matrix MultiplyValidMatrices(const Matrix matrix1,
                                    const Matrix matrix2) {
  Matrix matrix = Matrix_Create(matrix1->nrows, matrix2->ncolumns);
  for (int row = 0; row < matrix->nrows; row++) {
    for (int column = 0; column < matrix->ncolumns; column++) {
      float value = 0;
      for (int k = 0; k < matrix1->ncolumns; k++)
        value += Matrix_ValueAt(matrix1, row, k) *
                 Matrix_ValueAt(matrix2, k, column);
      Matrix_SetValue(matrix, row, column, value);
    }
  }
  return matrix;
}

Matrix Matrix_Multiply(const Matrix matrix1, const Matrix matrix2) {
  bool CanMultiplyMatrices = matrix1->ncolumns == matrix2->nrows;
  if (!CanMultiplyMatrices) {
    /* Error message? */
    exit(-1);
  }
  return MultiplyValidMatrices(matrix1, matrix2);
}

Matrix Matrix_DestructiveMultiply(Matrix *lhsPtr, Matrix *rhsPtr) {
  Matrix matrix1 = *lhsPtr;
  Matrix matrix2 = *rhsPtr;
  bool CanMultiplyMatrices = matrix1->ncolumns == matrix2->nrows;
  if (!CanMultiplyMatrices) {
    /* Error message? */
    exit(-1);
  }
  Matrix result = MultiplyValidMatrices(matrix1, matrix2);
  Matrix_Destroy(lhsPtr);
  Matrix_Destroy(rhsPtr);
  return result;
}

static Matrix TupleToMatrix(Tuple tuple) {
  Matrix mtuple = Matrix_Create(4, 1);
  Matrix_SetValue(mtuple, 0, 0, tuple.x);
  Matrix_SetValue(mtuple, 1, 0, tuple.y);
  Matrix_SetValue(mtuple, 2, 0, tuple.z);
  Matrix_SetValue(mtuple, 3, 0, tuple.w);
  return mtuple;
}

static Tuple MatrixToTuple(const Matrix mtuple) {
  float x, y, z, w;
  x = Matrix_ValueAt(mtuple, 0, 0);
  y = Matrix_ValueAt(mtuple, 1, 0);
  z = Matrix_ValueAt(mtuple, 2, 0);
  w = Matrix_ValueAt(mtuple, 3, 0);

  return Tuple_Create(x, y, z, w);
}

Tuple Matrix_MultiplyTuple(const Matrix matrix, Tuple tuple) {
  if ((matrix->nrows != 4) | (matrix->ncolumns != 4)) {
    /* Error message? */
    exit(-1);
  }
  Matrix mtuple = TupleToMatrix(tuple);
  Matrix result = Matrix_Multiply(matrix, mtuple);
  Matrix_Destroy(&mtuple);
  Tuple tResult = MatrixToTuple(result);
  Matrix_Destroy(&result);
  return tResult;
}

static void SetMatrixDiagonal(Matrix matrix, float value) {
  int dimension = matrix->nrows;
  if (matrix->nrows > matrix->ncolumns)
    dimension = matrix->ncolumns;
  for (int k = 0; k < dimension; k++)
    Matrix_SetValue(matrix, k, k, value);
}

Matrix Matrix_Identity(int dimension) {
  Matrix identity = Matrix_Create(dimension, dimension);
  SetMatrixDiagonal(identity, 1);
  return identity;
}

static void FillTransposedMatrix(Matrix transpose, const Matrix matrix) {
  for (int row = 0; row < matrix->nrows; row++)
    for (int column = 0; column < matrix->ncolumns; column++) {
      float value = Matrix_ValueAt(matrix, row, column);
      Matrix_SetValue(transpose, column, row, value);
    }
}

Matrix Matrix_Transpose(const Matrix matrix) {
  Matrix transpose = Matrix_Create(matrix->ncolumns, matrix->nrows);
  FillTransposedMatrix(transpose, matrix);
  return transpose;
}

static void CheckValidSubmatrix(const Matrix matrix, int row, int column) {
  if (!WithinMatrixBounds(matrix, row, column)) {
    /* Error message? */
    exit(-1);
  }
  if (matrix->nrows == 1 || matrix->ncolumns == 1) {
    /* Error message? */
    exit(-1);
  }
}

static void FillSubmatrix(Matrix submatrix, const Matrix matrix, int row,
                          int column) {
  for (int i = 0; i < submatrix->nrows; i++)
    for (int j = 0; j < submatrix->ncolumns; j++) {
      int mrow = i, mcolumn = j;
      if (i >= row)
        ++mrow;
      if (j >= column)
        ++mcolumn;

      float value = Matrix_ValueAt(matrix, mrow, mcolumn);
      Matrix_SetValue(submatrix, i, j, value);
    }
}

Matrix Matrix_Submatrix(const Matrix matrix, int row, int column) {
  CheckValidSubmatrix(matrix, row, column);
  Matrix submatrix = Matrix_Create(matrix->nrows - 1, matrix->ncolumns - 1);
  FillSubmatrix(submatrix, matrix, row, column);
  return submatrix;
}

static void CheckMatrixIsSquare(const Matrix matrix) {
  if (matrix->nrows != matrix->ncolumns) {
    /* Error message? */
    exit(-1);
  }
}

float Matrix_Determinant(const Matrix matrix) {
  CheckMatrixIsSquare(matrix);

  if (matrix->nrows == 1 && matrix->ncolumns == 1)
    return Matrix_ValueAt(matrix, 0, 0);
  if (matrix->nrows == 2 && matrix->ncolumns == 2) {
    float a, b, c, d;
    a = Matrix_ValueAt(matrix, 0, 0);
    b = Matrix_ValueAt(matrix, 0, 1);
    c = Matrix_ValueAt(matrix, 1, 0);
    d = Matrix_ValueAt(matrix, 1, 1);
    return (a * d) - (b * c);
  }

  float determinant = 0;
  for (int j = 0; j < matrix->ncolumns; j++)
    determinant += Matrix_ValueAt(matrix, 0, j) * Matrix_Cofactor(matrix, 0, j);
  return determinant;
}

float Matrix_Minor(const Matrix matrix, int row, int column) {
  Matrix submatrix = Matrix_Submatrix(matrix, row, column);
  float minor = Matrix_Determinant(submatrix);
  Matrix_Destroy(&submatrix);
  return minor;
}

float Matrix_Cofactor(const Matrix matrix, int row, int column) {
  bool FlipMinorSign = ((row + column) % 2 == 1);
  if (FlipMinorSign)
    return -1 * Matrix_Minor(matrix, row, column);
  return Matrix_Minor(matrix, row, column);
}

Matrix Matrix_Inverse(const Matrix matrix) {
  float determinant = Matrix_Determinant(matrix);
  int rows, columns;
  rows = matrix->nrows;
  columns = matrix->ncolumns;
  Matrix inverse = Matrix_Create(rows, columns);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) {
      float value = Matrix_Cofactor(matrix, i, j);
      value /= determinant;
      Matrix_SetValue(inverse, j, i, value);
    }
  return inverse;
}
