#include "unity_fixture.h"

TEST_GROUP_RUNNER(MatrixInit) {
  RUN_TEST_CASE(MatrixInit, MatricesCanHaveAnySize);
}
TEST_GROUP_RUNNER(Matrix) {
  RUN_TEST_CASE(Matrix, MatrixStoresFloats);
  RUN_TEST_CASE(Matrix, MatrixDefaultValuesAreZero);
  RUN_TEST_CASE(Matrix, MatrixValueAtReturnsFloat);
  RUN_TEST_CASE(Matrix, MatrixSetValueChangesMatrixValues);
  RUN_TEST_CASE(Matrix, MatrixAssignSetsOneMatrixEqualToAnother);
  RUN_TEST_CASE(Matrix, MatrixAssignDestroysRightHandSide);
  RUN_TEST_CASE(Matrix, MatrixCopySetsOneMatrixEqualToAnother);
  RUN_TEST_CASE(Matrix, MatrixCopyCanTakeAnRValue);
  RUN_TEST_CASE(Matrix, MultiplicationOfMatrixAndTuple);
  RUN_TEST_CASE(Matrix, IdentityReturnsNXNDimensionalIdentityMatrix);
  RUN_TEST_CASE(Matrix, SubmatrixRemovesOneRowAndOneColumn);
  RUN_TEST_CASE(Matrix, SubmatrixRemovesValuesFromSpecifiedRowAndColumn);
  RUN_TEST_CASE(Matrix, DeterminantOf2X2Matrix);
  RUN_TEST_CASE(Matrix, MinorOf3X3Matrix);
  RUN_TEST_CASE(Matrix, CofactorOf3X3Matrix);
  RUN_TEST_CASE(Matrix,
                DeterminantCalculatesDeterminantOfNDimensionalSquareMatrix);
  RUN_TEST_CASE(Matrix, SingularMatrixHasDeterminantOfZero);
  RUN_TEST_CASE(Matrix, MatrixInverseReturnsInverseForNonsingularMatrix);
}

TEST_GROUP_RUNNER(MatrixOperations) {
  RUN_TEST_CASE(MatrixOperations, MatrixEqualsReturnsTrueForIdenticalMatrices);
  RUN_TEST_CASE(MatrixOperations, MatrixEqualsReturnsFalseForDifferentMatrices);
  RUN_TEST_CASE(MatrixOperations, MultiplicationOfTwoMatrices);
  RUN_TEST_CASE(MatrixOperations,
                MultiplcationByIdentityReturnsIdenticalMatrix);
  RUN_TEST_CASE(MatrixOperations, DestructiveMultiplicationOfTwoMatrices);
  RUN_TEST_CASE(MatrixOperations, MatrixTransposeSwapsRowsAndColumns);
  RUN_TEST_CASE(MatrixOperations, MatrixTimesInverseGivesIdentity);
}
