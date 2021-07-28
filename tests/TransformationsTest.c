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
	Tuple point = Tuple_CreatePoint(5, -3, 2);
	Matrix translation = Transformation_Translation(-3, 4, 5);
	point = Matrix_MultiplyTuple(translation, point);
	Matrix_Destroy(&translation);

	TEST_ASSERT_EQUAL_FLOAT(2, point.x);
	TEST_ASSERT_EQUAL_FLOAT(1, point.y);
	TEST_ASSERT_EQUAL_FLOAT(7, point.z);
}
