#include "Transformations.h"
#include "TestUtilities.h"
#include "Utilities.h"
#include "unity_fixture.h"

static Tuple point, expected, actual;
static Matrix transformation;

TEST_GROUP(Transformations);

TEST_SETUP(Transformations) {}

TEST_TEAR_DOWN(Transformations) { Matrix_Destroy(&transformation); }

TEST(Transformations, TranslationMovesAPoint) {
  point = Tuple_CreatePoint(-3, 4, 5);
  transformation = Transformation_Translation(5, -3, 2);
  actual = Matrix_MultiplyTuple(transformation, point);
  expected = Tuple_CreatePoint(2, 1, 7);
  AssertTuplesEqual(expected, actual);
}

TEST(Transformations, InverseTranslationMovesPointInOtherDirection) {
  point = Tuple_CreatePoint(-3, 4, 5);
  Matrix translation = Transformation_Translation(5, -3, 2);
  transformation = Matrix_Inverse(translation);
  actual = Matrix_MultiplyTuple(transformation, point);
  Matrix_Destroy(&translation);
  expected = Tuple_CreatePoint(-8, 7, 3);
  AssertTuplesEqual(expected, actual);
}

TEST(Transformations, TranslationDoesNotAffectVectors) {
  Tuple vector = Tuple_CreateVector(-3, 4, 5);
  transformation = Transformation_Translation(5, -3, 2);
  actual = Matrix_MultiplyTuple(transformation, vector);
  expected = Tuple_CreateVector(-3, 4, 5);
  AssertTuplesEqual(expected, actual);
}

TEST(Transformations, ScalingMultipliesComponents) {
  point = Tuple_CreatePoint(-4, 6, 8);
  transformation = Transformation_Scale(2, 3, 4);
  actual = Matrix_MultiplyTuple(transformation, point);
  expected = Tuple_CreatePoint(-8, 18, 32);
  AssertTuplesEqual(expected, actual);
}

TEST(Transformations, ScalingAffectsVectors) {
  point = Tuple_CreateVector(-4, 6, 8);
  transformation = Transformation_Scale(2, 3, 4);
  actual = Matrix_MultiplyTuple(transformation, point);
  expected = Tuple_CreateVector(-8, 18, 32);
  AssertTuplesEqual(expected, actual);
}

TEST(Transformations, InverseScalingDividesComponents) {
  point = Tuple_CreateVector(-4, 6, 8);
  Matrix scale = Transformation_Scale(2, 3, 4);
  transformation = Matrix_Inverse(scale);
  actual = Matrix_MultiplyTuple(transformation, point);
  Matrix_Destroy(&scale);
  expected = Tuple_CreateVector(-2, 2, 2);
  AssertTuplesEqual(expected, actual);
}

TEST(Transformations, NegativeScalingReflects) {
  point = Tuple_CreateVector(2, 3, 4);
  transformation = Transformation_Scale(-1, 1, 1);
  actual = Matrix_MultiplyTuple(transformation, point);
  expected = Tuple_CreateVector(-2, 3, 4);
  AssertTuplesEqual(expected, actual);
}

TEST(Transformations, RotationAboutXAxisMovesPoint) {
  point = Tuple_CreatePoint(0, 1, 0);
  transformation = Transformation_RotationX(M_PI / 4);
  actual = Matrix_MultiplyTuple(transformation, point);
  expected = Tuple_CreatePoint(0, sqrtf(2) / 2, sqrtf(2) / 2);
  Matrix_Destroy(&transformation);
  AssertTuplesEqual(expected, actual);
  transformation = Transformation_RotationX(M_PI / 2);
  actual = Matrix_MultiplyTuple(transformation, point);
  expected = Tuple_CreatePoint(0, 0, 1);
  AssertTuplesEqual(expected, actual);
}

TEST(Transformations, InverseXRotationRotatesInOppositeDirection) {
  point = Tuple_CreatePoint(0, 1, 0);
  Matrix rotation = Transformation_RotationX(M_PI / 4);
  transformation = Matrix_Inverse(rotation);
  actual = Matrix_MultiplyTuple(transformation, point);
  expected = Tuple_CreatePoint(0, sqrtf(2) / 2, -sqrtf(2) / 2);
  Matrix_Destroy(&rotation);
  AssertTuplesEqual(expected, actual);
}

TEST(Transformations, RotationAboutYAxisMovesPoint) {
  point = Tuple_CreatePoint(0, 0, 1);
  transformation = Transformation_RotationY(M_PI / 4);
  actual = Matrix_MultiplyTuple(transformation, point);
  expected = Tuple_CreatePoint(sqrtf(2) / 2, 0, sqrtf(2) / 2);
  Matrix_Destroy(&transformation);
  AssertTuplesEqual(expected, actual);
  transformation = Transformation_RotationY(M_PI / 2);
  actual = Matrix_MultiplyTuple(transformation, point);
  expected = Tuple_CreatePoint(1, 0, 0);
  AssertTuplesEqual(expected, actual);
}

TEST(Transformations, RotationAboutZAxisMovesPoint) {
  point = Tuple_CreatePoint(0, 1, 0);
  transformation = Transformation_RotationZ(M_PI / 4);
  actual = Matrix_MultiplyTuple(transformation, point);
  expected = Tuple_CreatePoint(-sqrtf(2) / 2, sqrtf(2) / 2, 0);
  Matrix_Destroy(&transformation);
  AssertTuplesEqual(expected, actual);
  transformation = Transformation_RotationZ(M_PI / 2);
  actual = Matrix_MultiplyTuple(transformation, point);
  expected = Tuple_CreatePoint(-1, 0, 0);
  AssertTuplesEqual(expected, actual);
}

static Matrix expectedTransformation;
TEST_GROUP(ViewTransformation);

TEST_SETUP(ViewTransformation) {}

TEST_TEAR_DOWN(ViewTransformation) {
  Matrix_Destroy(&transformation);
  Matrix_Destroy(&expectedTransformation);
}

TEST(ViewTransformation, DefaultOrientation) {
  Tuple from = Tuple_CreatePoint(0, 0, 0);
  Tuple to = Tuple_CreatePoint(0, 0, -1);
  Tuple up = Tuple_CreateVector(0, 1, 0);
  transformation = Transformation_ViewTransform(from, to, up);
  expectedTransformation = Matrix_Identity(4);
  AssertMatricesEqual(expectedTransformation, transformation);
}

TEST(ViewTransformation, PositiveZDirection) {
  Tuple from = Tuple_CreatePoint(0, 0, 0);
  Tuple to = Tuple_CreatePoint(0, 0, 1);
  Tuple up = Tuple_CreateVector(0, 1, 0);
  transformation = Transformation_ViewTransform(from, to, up);
  expectedTransformation = Transformation_Scale(-1, 1, -1);
  AssertMatricesEqual(expectedTransformation, transformation);
}

TEST(ViewTransformation, TransformMovesTheWorld) {
  Tuple from = Tuple_CreatePoint(0, 0, 8);
  Tuple to = Tuple_CreatePoint(0, 0, 0);
  Tuple up = Tuple_CreateVector(0, 1, 0);
  transformation = Transformation_ViewTransform(from, to, up);
  expectedTransformation = Transformation_Translation(0, 0, -8);
  AssertMatricesEqual(expectedTransformation, transformation);
}

static void SetArbitraryViewTransform() {
  expectedTransformation = Matrix_Create(4, 4);
  Matrix_SetValue(expectedTransformation, 0, 0, -0.50709);
  Matrix_SetValue(expectedTransformation, 0, 1, 0.50709);
  Matrix_SetValue(expectedTransformation, 0, 2, 0.67612);
  Matrix_SetValue(expectedTransformation, 0, 3, -2.36643);

  Matrix_SetValue(expectedTransformation, 1, 0, 0.76772);
  Matrix_SetValue(expectedTransformation, 1, 1, 0.60609);
  Matrix_SetValue(expectedTransformation, 1, 2, 0.12122);
  Matrix_SetValue(expectedTransformation, 1, 3, -2.82843);

  Matrix_SetValue(expectedTransformation, 2, 0, -0.35857);
  Matrix_SetValue(expectedTransformation, 2, 1, 0.59761);
  Matrix_SetValue(expectedTransformation, 2, 2, -0.71714);
  Matrix_SetValue(expectedTransformation, 2, 3, 0);

  Matrix_SetValue(expectedTransformation, 3, 0, 0);
  Matrix_SetValue(expectedTransformation, 3, 1, 0);
  Matrix_SetValue(expectedTransformation, 3, 2, 0);
  Matrix_SetValue(expectedTransformation, 3, 3, 1);
}

TEST(ViewTransformation, ArbitraryViewTransformation) {
  Tuple from = Tuple_CreatePoint(1, 3, 2);
  Tuple to = Tuple_CreatePoint(4, -2, 8);
  Tuple up = Tuple_CreateVector(1, 1, 0);
  transformation = Transformation_ViewTransform(from, to, up);
  SetArbitraryViewTransform();
  AssertMatricesEqual(expectedTransformation, transformation);
}

TEST_GROUP(Shears);

TEST_SETUP(Shears) { point = Tuple_CreatePoint(2, 3, 4); }

TEST_TEAR_DOWN(Shears) {
  actual = Matrix_MultiplyTuple(transformation, point);
  Matrix_Destroy(&transformation);
  AssertTuplesEqual(expected, actual);
}

TEST(Shears, ShearXInProportionToY) {
  transformation = Transformation_Shear(1, 0, 0, 0, 0, 0);
  expected = Tuple_CreatePoint(5, 3, 4);
}

TEST(Shears, ShearXInProportionToZ) {
  transformation = Transformation_Shear(0, 1, 0, 0, 0, 0);
  expected = Tuple_CreatePoint(6, 3, 4);
}

TEST(Shears, ShearYInProportionToX) {
  transformation = Transformation_Shear(0, 0, 1, 0, 0, 0);
  expected = Tuple_CreatePoint(2, 5, 4);
}

TEST(Shears, ShearYInProportionToZ) {
  transformation = Transformation_Shear(0, 0, 0, 1, 0, 0);
  expected = Tuple_CreatePoint(2, 7, 4);
}

TEST(Shears, ShearZInProportionToX) {
  transformation = Transformation_Shear(0, 0, 0, 0, 1, 0);
  expected = Tuple_CreatePoint(2, 3, 6);
}

TEST(Shears, ShearZInProportionToY) {
  transformation = Transformation_Shear(0, 0, 0, 0, 0, 1);
  expected = Tuple_CreatePoint(2, 3, 7);
}

TEST_GROUP(TransformationSequence);

static Matrix rotation, scale, translation;

TEST_SETUP(TransformationSequence) {
  point = Tuple_CreatePoint(1, 0, 1);
  rotation = Transformation_RotationX(M_PI / 2);
  scale = Transformation_Scale(5, 5, 5);
  translation = Transformation_Translation(10, 5, 7);
}

TEST_TEAR_DOWN(TransformationSequence) {
  Matrix_Destroy(&rotation);
  Matrix_Destroy(&scale);
  Matrix_Destroy(&translation);
}

TEST(TransformationSequence, IndividualTransformationsAreAppliedSequentially) {
  actual = Matrix_MultiplyTuple(rotation, point);
  expected = Tuple_CreatePoint(1, -1, 0);
  AssertTuplesEqual(expected, actual);
  actual = Matrix_MultiplyTuple(scale, actual);
  expected = Tuple_CreatePoint(5, -5, 0);
  AssertTuplesEqual(expected, actual);
  actual = Matrix_MultiplyTuple(translation, actual);
  expected = Tuple_CreatePoint(15, 0, 7);
  AssertTuplesEqual(expected, actual);
}

TEST(TransformationSequence, ChainedTransformationsAreAppliedInReverseOrder) {
  transformation = Matrix_Multiply(scale, rotation);
  Matrix_Transfer(transformation, Matrix_Multiply(translation, transformation));
  actual = Matrix_MultiplyTuple(transformation, point);
  Matrix_Destroy(&transformation);
  expected = Tuple_CreatePoint(15, 0, 7);
  AssertTuplesEqual(expected, actual);
}
