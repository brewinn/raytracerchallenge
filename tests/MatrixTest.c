#include "unity_fixture.h"
#include "Matrix.h"
#include "TestUtilities.h"
#include <stdio.h>

static Matrix matrix, matrix1, matrix2;

static void FillMatrixValues(Matrix matrix,float (*FillOperation)(int, int))
{
    for(int i = 0; i < Matrix_GetRows(matrix); i++)
    {
        for(int j = 0; j < Matrix_GetColumns(matrix); j++)
        {
            float value = (*FillOperation)(i,j);
            Matrix_SetValue(matrix, i, j, value);
        }
    }
}

static float FillAdd(int i, int j)
{
    return (float) i + j;
}

static float FillSubtract(int i, int j)
{
    return (float) i - j;
}

static float FillCellNumber(int i, int j)
{
    return (float) 4 * i + j;
}

TEST_GROUP(MatrixInit);

TEST_SETUP(MatrixInit)
{
}

TEST_TEAR_DOWN(MatrixInit)
{
}


TEST(MatrixInit, MatricesCanHaveAnySize)
{
    int rows = 5, columns = 7;
    matrix = Matrix_Create(rows,columns);
    TEST_ASSERT_EQUAL_INT(rows, Matrix_GetRows(matrix));
    TEST_ASSERT_EQUAL_INT(columns, Matrix_GetColumns(matrix));
    Matrix_Destroy(&matrix);
}

TEST_GROUP(Matrix);

TEST_SETUP(Matrix)
{
    matrix = Matrix_Create(4, 4);
}

TEST_TEAR_DOWN(Matrix)
{
    Matrix_Destroy(&matrix);
}

TEST(Matrix, MatrixStoresFloats)
{
    Matrix_SetValue(matrix, 0, 0, 1);
    Matrix_SetValue(matrix, 2, 1, 2.5);
    Matrix_SetValue(matrix, 3, 3, 3.0);
    TEST_ASSERT_EQUAL_FLOAT(1, Matrix_ValueAt(matrix, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(2.5, Matrix_ValueAt(matrix, 2, 1));
    TEST_ASSERT_EQUAL_FLOAT(3.0, Matrix_ValueAt(matrix, 3, 3));
}

TEST(Matrix, MatrixDefaultValuesAreZero)
{
    TEST_ASSERT_EQUAL_INT(0, Matrix_ValueAt(matrix, 1, 1));
}

TEST(Matrix, MatrixSetValueChangesMatrixValues)
{
    float value = 1;
    int row = 0, column = 0;
    Matrix_SetValue(matrix, row, column, value);
    TEST_ASSERT_EQUAL_FLOAT(value, Matrix_ValueAt(matrix, row, column));
}

TEST(Matrix, MatrixValueAtReturnsFloat)
{
    Matrix_SetValue(matrix, 1, 3, 0.25);
    float value = Matrix_ValueAt(matrix, 1, 3);
    TEST_ASSERT_EQUAL_FLOAT(0.25, value);
}

TEST(Matrix, MatrixAssignSetsOneMatrixEqualToAnother)
{
    Matrix identity = Matrix_Identity(3);
    Matrix_Assign(&matrix, &identity);
    TEST_ASSERT_EQUAL_FLOAT(1, Matrix_ValueAt(matrix, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(0, Matrix_ValueAt(matrix, 1, 0));
    TEST_ASSERT_EQUAL_FLOAT(1, Matrix_ValueAt(matrix, 2, 2));
}

TEST(Matrix, MatrixAssignDestroysRightHandSide)
{
    Matrix identity = Matrix_Identity(3);
    Matrix_Assign(&matrix, &identity);
    TEST_ASSERT_NULL(identity);
}

TEST(Matrix, MatrixCopySetsOneMatrixEqualToAnother)
{
    Matrix identity = Matrix_Identity(3);
    Matrix_Transfer(matrix, identity);
    TEST_ASSERT_EQUAL_FLOAT(1, Matrix_ValueAt(matrix, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(0, Matrix_ValueAt(matrix, 1, 0));
    TEST_ASSERT_EQUAL_FLOAT(1, Matrix_ValueAt(matrix, 2, 2));
}

TEST(Matrix, MatrixCopyCanTakeAnRValue)
{
    Matrix_Transfer(matrix, Matrix_Identity(2));
    TEST_ASSERT_EQUAL_FLOAT(1, Matrix_ValueAt(matrix, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(0, Matrix_ValueAt(matrix, 1, 0));
    TEST_ASSERT_EQUAL_FLOAT(1, Matrix_ValueAt(matrix, 1, 1));
}

TEST(Matrix, MultiplicationOfMatrixAndTuple)
{
    Tuple tuple = Tuple_Create(1, 1.5, 2, 2.5);
    FillMatrixValues(matrix, FillAdd);
    tuple = Matrix_MultiplyTuple(matrix, tuple);

    TEST_ASSERT_EQUAL_FLOAT(13, tuple.x);
    TEST_ASSERT_EQUAL_FLOAT(20, tuple.y);
    TEST_ASSERT_EQUAL_FLOAT(27, tuple.z);
    TEST_ASSERT_EQUAL_FLOAT(34, tuple.w);
}

TEST(Matrix, IdentityReturnsNXNDimensionalIdentityMatrix)
{
    Matrix_Transfer(matrix, Matrix_Identity(4));
    TEST_ASSERT_EQUAL_FLOAT(1, Matrix_ValueAt(matrix, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(0, Matrix_ValueAt(matrix, 2, 0));
    TEST_ASSERT_EQUAL_FLOAT(1, Matrix_ValueAt(matrix, 3, 3));
    TEST_ASSERT_EQUAL_FLOAT(0, Matrix_ValueAt(matrix, 2, 3));
}

TEST(Matrix, SubmatrixRemovesOneRowAndOneColumn)
{
    Matrix_Transfer(matrix, Matrix_Submatrix(matrix, 2, 3));
    TEST_ASSERT_EQUAL_INT(3, Matrix_GetRows(matrix));
    TEST_ASSERT_EQUAL_INT(3, Matrix_GetColumns(matrix));
}

TEST(Matrix, SubmatrixRemovesValuesFromSpecifiedRowAndColumn)
{
    FillMatrixValues(matrix, FillCellNumber);
    Matrix_Transfer(matrix, Matrix_Submatrix(matrix, 3, 2));
    TEST_ASSERT_EQUAL_FLOAT(0, Matrix_ValueAt(matrix, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(5, Matrix_ValueAt(matrix, 1, 1));
    TEST_ASSERT_EQUAL_FLOAT(11, Matrix_ValueAt(matrix, 2, 2));
}

static void FillNonsingular2X2(Matrix matrix)
{
    Matrix_SetValue(matrix, 0, 0, 1);
    Matrix_SetValue(matrix, 0, 1, 2);
    Matrix_SetValue(matrix, 1, 0, 2);
    Matrix_SetValue(matrix, 1, 1, 3);
}

TEST(Matrix, DeterminantOf2X2Matrix)
{
    Matrix_Transfer(matrix, Matrix_Create(2, 2));
    FillNonsingular2X2(matrix);
    float determinant = Matrix_Determinant(matrix);
    TEST_ASSERT_EQUAL_FLOAT(-1.0, determinant);
}

static void FillNonsingular3X3(Matrix matrix)
{
    Matrix_SetValue(matrix, 0, 0, 3);
    Matrix_SetValue(matrix, 0, 1, 5);
    Matrix_SetValue(matrix, 0, 2, 0);

    Matrix_SetValue(matrix, 1, 0, 2);
    Matrix_SetValue(matrix, 1, 1, -1);
    Matrix_SetValue(matrix, 1, 2, -7);

    Matrix_SetValue(matrix, 2, 0, 6);
    Matrix_SetValue(matrix, 2, 1, -1);
    Matrix_SetValue(matrix, 2, 2, 5);
}

TEST(Matrix, MinorOf3X3Matrix)
{
    Matrix_Transfer(matrix, Matrix_Create(3, 3));
    FillNonsingular3X3(matrix);
    float minor = Matrix_Minor(matrix, 1, 0);
    TEST_ASSERT_EQUAL_FLOAT(25, minor);
}

TEST(Matrix, CofactorOf3X3Matrix)
{
    Matrix_Transfer(matrix, Matrix_Create(3, 3));
    FillNonsingular3X3(matrix);
    float cofactor = Matrix_Cofactor(matrix, 0, 0);
    float minor = Matrix_Minor(matrix, 0, 0);
    TEST_ASSERT_EQUAL_FLOAT(minor, cofactor);
    cofactor = Matrix_Cofactor(matrix, 1, 0);
    minor = Matrix_Minor(matrix, 1, 0);
    TEST_ASSERT_EQUAL_FLOAT(-1 * minor, cofactor);
}

static void FillNonsingular4X4(Matrix matrix)
{
    Matrix_SetValue(matrix, 0, 0, -2);
    Matrix_SetValue(matrix, 0, 1, -8);
    Matrix_SetValue(matrix, 0, 2, 3);
    Matrix_SetValue(matrix, 0, 3, 5);

    Matrix_SetValue(matrix, 1, 0, -3);
    Matrix_SetValue(matrix, 1, 1, 1);
    Matrix_SetValue(matrix, 1, 2, 7);
    Matrix_SetValue(matrix, 1, 3, 3);

    Matrix_SetValue(matrix, 2, 0, 1);
    Matrix_SetValue(matrix, 2, 1, 2);
    Matrix_SetValue(matrix, 2, 2, -9);
    Matrix_SetValue(matrix, 2, 3, 6);

    Matrix_SetValue(matrix, 3, 0, -6);
    Matrix_SetValue(matrix, 3, 1, 7);
    Matrix_SetValue(matrix, 3, 2, 7);
    Matrix_SetValue(matrix, 3, 3, -9);
}

TEST(Matrix, DeterminantCalculatesDeterminantOfNDimensionalSquareMatrix)
{
    FillNonsingular4X4(matrix);
    float determinant = Matrix_Determinant(matrix);
    TEST_ASSERT_EQUAL_FLOAT(-4071, determinant);
}

TEST(Matrix, SingularMatrixHasDeterminantOfZero)
{
    FillMatrixValues(matrix, FillAdd);
    float determinant = Matrix_Determinant(matrix);
    TEST_ASSERT_EQUAL_FLOAT(0, determinant);
}

TEST(Matrix, MatrixInverseReturnsInverseForNonsingularMatrix)
{
    Matrix_Transfer(matrix, Matrix_Create(2, 2));
    FillNonsingular2X2(matrix);
    Matrix_Transfer(matrix, Matrix_Inverse(matrix));

    TEST_ASSERT_EQUAL_FLOAT(-3, Matrix_ValueAt(matrix, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(2, Matrix_ValueAt(matrix, 0, 1));
    TEST_ASSERT_EQUAL_FLOAT(2, Matrix_ValueAt(matrix, 1, 0));
    TEST_ASSERT_EQUAL_FLOAT(-1, Matrix_ValueAt(matrix, 1, 1));
}

TEST_GROUP(MatrixOperations);

TEST_SETUP(MatrixOperations)
{
    matrix1 = Matrix_Create(4, 4);
    matrix2 = Matrix_Create(4, 4);
}

TEST_TEAR_DOWN(MatrixOperations)
{
    Matrix_Destroy(&matrix1);
    Matrix_Destroy(&matrix2);
}

TEST(MatrixOperations, MatrixEqualsReturnsTrueForIdenticalMatrices)
{
    FillMatrixValues(matrix1, FillAdd);
    FillMatrixValues(matrix2, FillAdd);
    TEST_ASSERT(Matrix_Equals(matrix1, matrix2));
}

TEST(MatrixOperations, MatrixEqualsReturnsFalseForDifferentMatrices)
{
    FillMatrixValues(matrix1, FillAdd);
    FillMatrixValues(matrix2, FillSubtract);
    TEST_ASSERT_FALSE(Matrix_Equals(matrix1, matrix2));
}



TEST(MatrixOperations, MultiplicationOfTwoMatrices)
{
    FillMatrixValues(matrix1, FillAdd);
    FillMatrixValues(matrix2, FillSubtract);
    Matrix result = Matrix_Multiply(matrix1, matrix2);
    Matrix_Assign(&matrix1, &result);
    TEST_ASSERT_EQUAL_FLOAT(14, Matrix_ValueAt(matrix1, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(0, Matrix_ValueAt(matrix1, 1, 2));
    TEST_ASSERT_EQUAL_FLOAT(-4, Matrix_ValueAt(matrix1, 3, 2));
}

TEST(MatrixOperations, MultiplcationByIdentityReturnsIdenticalMatrix)
{
    FillMatrixValues(matrix1, FillAdd);
    Matrix identity = Matrix_Identity(4);
    Matrix_Transfer(matrix2, Matrix_Multiply(matrix1, identity));
    Matrix_Destroy(&identity);
    AssertMatricesEqual(matrix1, matrix2);
}

TEST(MatrixOperations, DestructiveMultiplicationOfTwoMatrices)
{
    Matrix temp1 = Matrix_Create(4,4);
    Matrix temp2 = Matrix_Create(4,4);
    FillMatrixValues(temp1, FillAdd);
    FillMatrixValues(temp2, FillSubtract);
    Matrix result = Matrix_DestructiveMultiply(&temp1, &temp2);
    Matrix_Assign(&matrix1, &result);

    TEST_ASSERT_EQUAL_FLOAT(14, Matrix_ValueAt(matrix1, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(0, Matrix_ValueAt(matrix1, 1, 2));
    TEST_ASSERT_EQUAL_FLOAT(-4, Matrix_ValueAt(matrix1, 3, 2));
}

static void AssertDimensionsTransposed(Matrix matrix1, Matrix matrix2)
{
    if(Matrix_GetRows(matrix1) != Matrix_GetColumns(matrix2))
        TEST_FAIL();
    if(Matrix_GetColumns(matrix1) != Matrix_GetRows(matrix2))
        TEST_FAIL();
}

static void AssertMatrixTransposed(Matrix matrix1, Matrix matrix2)
{
    AssertDimensionsTransposed(matrix1, matrix2);
    for(int i = 0; i < Matrix_GetRows(matrix1); i++)
    {
        for(int j = 0; j < Matrix_GetColumns(matrix1); j++)
        {
            TEST_ASSERT_EQUAL_FLOAT(Matrix_ValueAt(matrix1, j, i), Matrix_ValueAt(matrix2, i, j));
        }
    }
}

TEST(MatrixOperations, MatrixTransposeSwapsRowsAndColumns)
{
    FillMatrixValues(matrix1, FillSubtract);
    Matrix_Transfer(matrix2, Matrix_Transpose(matrix1));
    AssertMatrixTransposed(matrix1, matrix2);
}

TEST(MatrixOperations, MatrixTimesInverseGivesIdentity)
{
    FillNonsingular4X4(matrix1);
    Matrix_Transfer(matrix2, Matrix_Inverse(matrix1));
    Matrix_Transfer(matrix2, Matrix_Multiply(matrix1, matrix2));
    Matrix_Transfer(matrix1, Matrix_Identity(4));
    TEST_ASSERT(Matrix_Equals(matrix1, matrix2));
}
