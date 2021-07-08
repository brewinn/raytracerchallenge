#include "unity_fixture.h"
#include "Tuple.h"

TEST_GROUP(Tuple);

TEST_SETUP(Tuple)
{
}

TEST_TEAR_DOWN(Tuple)
{
}

TEST(Tuple, TupleWithWEqualsOneIsAPoint)
{
	Tuple tuple;
	tuple = Tuple_Create(4.3, -4.2, 3.1, 1.0);
	TEST_ASSERT_EQUAL_FLOAT(4.3, tuple.x);
	TEST_ASSERT_EQUAL_FLOAT(-4.2, tuple.y);
	TEST_ASSERT_EQUAL_FLOAT(3.1, tuple.z);
	TEST_ASSERT_EQUAL_FLOAT(1.0, tuple.w);
}
