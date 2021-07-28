#include "unity_fixture.h"
#include "Transformations.h"
#include "Utilities.h"

static Tuple point, expected, actual;
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
	point = Tuple_CreatePoint(-3, 4, 5);
	transformation = Transformation_Translation(5, -3, 2);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreatePoint(2, 1, 7);
	AssertTuplesEqual();
}

TEST(Transformations, InverseTranslationMovesPointInOtherDirection)
{
	point = Tuple_CreatePoint(-3, 4, 5);
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
	point = Tuple_CreatePoint(-4, 6, 8);
	transformation = Transformation_Scale(2, 3, 4);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreatePoint(-8, 18, 32);
	AssertTuplesEqual();
}

TEST(Transformations, ScalingAffectsVectors)
{
	point = Tuple_CreateVector(-4, 6, 8);
	transformation = Transformation_Scale(2, 3, 4);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreateVector(-8, 18, 32);
	AssertTuplesEqual();
}

TEST(Transformations, InverseScalingDividesComponents)
{
	point = Tuple_CreateVector(-4, 6, 8);
	Matrix scale = Transformation_Scale(2, 3, 4);
	transformation = Matrix_Inverse(scale);
	actual = Matrix_MultiplyTuple(transformation, point);
	Matrix_Destroy(&scale);
	expected = Tuple_CreateVector(-2, 2, 2);
	AssertTuplesEqual();
}

TEST(Transformations, NegativeScalingReflects)
{
	point = Tuple_CreateVector(2, 3, 4);
	transformation = Transformation_Scale(-1, 1, 1);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreateVector(-2, 3, 4);
	AssertTuplesEqual();
}

TEST(Transformations, RotationAboutXAxisMovesPoint)
{
	point = Tuple_CreatePoint(0, 1, 0);
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
	point = Tuple_CreatePoint(0, 1, 0);
	Matrix rotation = Transformation_RotationX(M_PI/4);
	transformation = Matrix_Inverse(rotation);
	actual = Matrix_MultiplyTuple(transformation, point);
	expected = Tuple_CreatePoint(0, sqrtf(2)/2, -sqrtf(2)/2);
	Matrix_Destroy(&rotation);
	AssertTupleFloatsEqual();
}

TEST(Transformations, RotationAboutYAxisMovesPoint)
{
	point = Tuple_CreatePoint(0, 0, 1);
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
	point = Tuple_CreatePoint(0, 1, 0);
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

TEST_GROUP(Shears);

TEST_SETUP(Shears)
{
	point = Tuple_CreatePoint(2, 3, 4);
}

TEST_TEAR_DOWN(Shears)
{
	actual = Matrix_MultiplyTuple(transformation, point);
	Matrix_Destroy(&transformation);
	AssertTuplesEqual();
}

TEST(Shears, ShearXInProportionToY)
{
	transformation = Transformation_Shear(1, 0, 0, 0, 0, 0);
	expected = Tuple_CreatePoint(5, 3, 4);
}

TEST(Shears, ShearXInProportionToZ)
{
	transformation = Transformation_Shear(0, 1, 0, 0, 0, 0);
	expected = Tuple_CreatePoint(6, 3, 4);
}

TEST(Shears, ShearYInProportionToX)
{
	transformation = Transformation_Shear(0, 0, 1, 0, 0, 0);
	expected = Tuple_CreatePoint(2, 5, 4);
}

TEST(Shears, ShearYInProportionToZ)
{
	transformation = Transformation_Shear(0, 0, 0, 1, 0, 0);
	expected = Tuple_CreatePoint(2, 7, 4);
}

TEST(Shears, ShearZInProportionToX)
{
	transformation = Transformation_Shear(0, 0, 0, 0, 1, 0);
	expected = Tuple_CreatePoint(2, 3, 6);
}

TEST(Shears, ShearZInProportionToY)
{
	transformation = Transformation_Shear(0, 0, 0, 0, 0, 1);
	expected = Tuple_CreatePoint(2, 3, 7);
}

TEST_GROUP(TransformationSequence);

static Matrix rotation, scale, translation;

TEST_SETUP(TransformationSequence)
{
	point = Tuple_CreatePoint(1, 0, 1);
	rotation = Transformation_RotationX(M_PI/2);
	scale = Transformation_Scale(5, 5, 5);
	translation = Transformation_Translation(10, 5, 7);
}

TEST_TEAR_DOWN(TransformationSequence)
{
	Matrix_Destroy(&rotation);
	Matrix_Destroy(&scale);
	Matrix_Destroy(&translation);
}

TEST(TransformationSequence, IndividualTransformationsAreAppliedSequentially)
{
	actual = Matrix_MultiplyTuple(rotation, point);
	expected = Tuple_CreatePoint(1, -1, 0);
	AssertTupleFloatsEqual();
	actual = Matrix_MultiplyTuple(scale, actual);
	expected = Tuple_CreatePoint(5, -5, 0);
	AssertTupleFloatsEqual();
	actual = Matrix_MultiplyTuple(translation, actual);
	expected = Tuple_CreatePoint(15, 0, 7);
	AssertTupleFloatsEqual();
}

TEST(TransformationSequence, ChainedTransformationsAreAppliedInReverseOrder)
{
	transformation = Matrix_Multiply(scale, rotation);
	Matrix_Copy(transformation, Matrix_Multiply(translation, transformation));
	actual = Matrix_MultiplyTuple(transformation, point);
	Matrix_Destroy(&transformation);
	expected = Tuple_CreatePoint(15, 0, 7);
	AssertTupleFloatsEqual();
}
