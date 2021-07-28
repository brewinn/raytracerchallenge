#include "unity_fixture.h"
#include "Transformations.h"

TEST_GROUP(Transformations);

TEST_SETUP(Transformations)
{
}

TEST_TEAR_DOWN(Transformations)
{
}


TEST(Transformations, TranslationMovesAPoint)
{
	Tuple point = Tuple_CreatePoint(-3, 4, 5);
	Matrix translation = Transformation_Translation(5, -3, 2);
	point = Matrix_MultiplyTuple(translation, point);
	Matrix_Destroy(&translation);

	TEST_ASSERT_EQUAL_FLOAT(2, point.x);
	TEST_ASSERT_EQUAL_FLOAT(1, point.y);
	TEST_ASSERT_EQUAL_FLOAT(7, point.z);
}

TEST(Transformations, InverseTranslationMovesPointInOtherDirection)
{
	Tuple point = Tuple_CreatePoint(-3, 4, 5);
	Matrix translation = Transformation_Translation(5, -3, 2);
	Matrix_Copy(translation, Matrix_Inverse(translation));
	point = Matrix_MultiplyTuple(translation, point);
	Matrix_Destroy(&translation);

	TEST_ASSERT_EQUAL_FLOAT(-8, point.x);
	TEST_ASSERT_EQUAL_FLOAT(7, point.y);
	TEST_ASSERT_EQUAL_FLOAT(3, point.z);
}

TEST(Transformations, TranslationDoesNotAffectVectors)
{
	Tuple vector = Tuple_CreateVector(-3, 4, 5);
	Matrix translation = Transformation_Translation(5, -3, 2);
	vector = Matrix_MultiplyTuple(translation, vector);
	Matrix_Destroy(&translation);

	TEST_ASSERT_EQUAL_FLOAT(-3, vector.x);
	TEST_ASSERT_EQUAL_FLOAT(4, vector.y);
	TEST_ASSERT_EQUAL_FLOAT(5, vector.z);
}
