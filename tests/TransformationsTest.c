#include "unity_fixture.h"
#include "Transformations.h"
#include "Utilities.h"

static Tuple expected, actual;
static Matrix transformation;

TEST_GROUP(Transformations);

TEST_SETUP(Transformations)
{
}

TEST_TEAR_DOWN(Transformations)
{
	Matrix_Destroy(&transformation);
}

static void AssertTuplesEqual()
{
	TEST_ASSERT_EQUAL_FLOAT(expected.x, actual.x);
	TEST_ASSERT_EQUAL_FLOAT(expected.y, actual.y);
	TEST_ASSERT_EQUAL_FLOAT(expected.z, actual.z);
	TEST_ASSERT_EQUAL_FLOAT(expected.w, actual.w);
}

static void AssertTupleFloatsEqual()
{
	/* Theses asserts are slightly more lenient than Unity's
	 * default assertion when comparing two floats */
	TEST_ASSERT_MESSAGE(floatsEqual(expected.x, actual.x), "Expected x and actual x differ!");
	TEST_ASSERT_MESSAGE(floatsEqual(expected.y, actual.y), "Expected y and actual y differ!");
	TEST_ASSERT_MESSAGE(floatsEqual(expected.z, actual.z), "Expected z and actual z differ!");
	TEST_ASSERT_MESSAGE(floatsEqual(expected.w, actual.w), "Expected w and actual w differ!");
}

TEST(Transformations, TranslationMovesAPoint)
{
	Tuple point = Tuple_CreatePoint(-3, 4, 5);
	transformation = Transformation_Translation(5, -3, 2);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreatePoint(2, 1, 7);
	AssertTuplesEqual();
}

TEST(Transformations, InverseTranslationMovesPointInOtherDirection)
{
	Tuple point = Tuple_CreatePoint(-3, 4, 5);
	Matrix translation = Transformation_Translation(5, -3, 2);
	transformation = Matrix_Inverse(translation);
	actual = Matrix_MultiplyTuple(transformation, point);
	Matrix_Destroy(&translation);
	expected = Tuple_CreatePoint(-8, 7, 3);
	AssertTuplesEqual();
}

TEST(Transformations, TranslationDoesNotAffectVectors)
{
	Tuple vector = Tuple_CreateVector(-3, 4, 5);
	transformation = Transformation_Translation(5, -3, 2);
	actual = Matrix_MultiplyTuple(transformation, vector);
	expected = Tuple_CreateVector(-3, 4, 5);
	AssertTuplesEqual();
}

TEST(Transformations, ScalingMultipliesComponents)
{
	Tuple point = Tuple_CreatePoint(-4, 6, 8);
	transformation = Transformation_Scale(2, 3, 4);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreatePoint(-8, 18, 32);
	AssertTuplesEqual();
}

TEST(Transformations, ScalingAffectsVectors)
{
	Tuple point = Tuple_CreateVector(-4, 6, 8);
	transformation = Transformation_Scale(2, 3, 4);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreateVector(-8, 18, 32);
	AssertTuplesEqual();
}

TEST(Transformations, InverseScalingDividesComponents)
{
	Tuple point = Tuple_CreateVector(-4, 6, 8);
	Matrix scale = Transformation_Scale(2, 3, 4);
	transformation = Matrix_Inverse(scale);
	actual = Matrix_MultiplyTuple(transformation, point);
	Matrix_Destroy(&scale);
	expected = Tuple_CreateVector(-2, 2, 2);
	AssertTuplesEqual();
}

TEST(Transformations, NegativeScalingReflects)
{
	Tuple point = Tuple_CreateVector(2, 3, 4);
	transformation = Transformation_Scale(-1, 1, 1);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreateVector(-2, 3, 4);
	AssertTuplesEqual();
}

TEST(Transformations, RotationAboutXAxisMovesPoint)
{
	Tuple point = Tuple_CreatePoint(0, 1, 0);
	transformation = Transformation_RotationX(M_PI/4);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreatePoint(0, sqrtf(2)/2, sqrtf(2)/2);
	Matrix_Destroy(&transformation);
	AssertTupleFloatsEqual();
	transformation = Transformation_RotationX(M_PI/2);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreatePoint(0, 0, 1);
	AssertTupleFloatsEqual();
}

TEST(Transformations, InverseXRotationRotatesInOppositeDirection)
{
	Tuple point = Tuple_CreatePoint(0, 1, 0);
	Matrix rotation = Transformation_RotationX(M_PI/4);
	transformation = Matrix_Inverse(rotation);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreatePoint(0, sqrtf(2)/2, -sqrtf(2)/2);
	Matrix_Destroy(&rotation);
	AssertTupleFloatsEqual();
}

TEST(Transformations, RotationAboutYAxisMovesPoint)
{
	Tuple point = Tuple_CreatePoint(0, 0, 1);
	transformation = Transformation_RotationY(M_PI/4);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreatePoint(sqrtf(2)/2, 0, sqrtf(2)/2);
	Matrix_Destroy(&transformation);
	AssertTupleFloatsEqual();
	transformation = Transformation_RotationY(M_PI/2);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreatePoint(1, 0, 0);
	AssertTupleFloatsEqual();
}

TEST(Transformations, RotationAboutZAxisMovesPoint)
{
	Tuple point = Tuple_CreatePoint(0, 1, 0);
	transformation = Transformation_RotationZ(M_PI/4);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreatePoint(-sqrtf(2)/2, sqrtf(2)/2, 0);
	Matrix_Destroy(&transformation);
	AssertTupleFloatsEqual();
	transformation = Transformation_RotationZ(M_PI/2);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreatePoint(-1, 0, 0);
	AssertTupleFloatsEqual();
}
