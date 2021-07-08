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

TEST(Tuple, TupleWithWEqualsZeroIsAVector)
{
	Tuple tuple;
	tuple = Tuple_Create(4.3, -4.2, 3.1, 0.0);
	TEST_ASSERT_EQUAL_FLOAT(4.3, tuple.x);
	TEST_ASSERT_EQUAL_FLOAT(-4.2, tuple.y);
	TEST_ASSERT_EQUAL_FLOAT(3.1, tuple.z);
	TEST_ASSERT_EQUAL_FLOAT(0.0, tuple.w);
}

TEST(Tuple, PointCreatesTupleWithWEqualsOne)
{
	Tuple tuple;
	tuple = Tuple_CreatePoint(4, -4, 3);
	TEST_ASSERT_EQUAL_FLOAT(4, tuple.x);
	TEST_ASSERT_EQUAL_FLOAT(-4, tuple.y);
	TEST_ASSERT_EQUAL_FLOAT(3, tuple.z);
	TEST_ASSERT_EQUAL_FLOAT(1, tuple.w);
}

TEST(Tuple, VectorCreatesTupleWithWEqualsZero)
{
	Tuple tuple;
	tuple = Tuple_CreateVector(4, -4, 3);
	TEST_ASSERT_EQUAL_FLOAT(4, tuple.x);
	TEST_ASSERT_EQUAL_FLOAT(-4, tuple.y);
	TEST_ASSERT_EQUAL_FLOAT(3, tuple.z);
	TEST_ASSERT_EQUAL_FLOAT(0, tuple.w);
}

TEST(Tuple, EqualsIsTrueForIdenticalTuples)
{
	Tuple tuple1, tuple2;
	tuple1 = Tuple_Create(1, 1, 1, 1);
	tuple2 = Tuple_Create(1, 1, 1, 1);
	TEST_ASSERT(Tuple_Equals(tuple1, tuple2));
}

TEST(Tuple, EqualsIsFalseForDifferentTuples)
{
	Tuple tuple1, tuple2;
	tuple1 = Tuple_Create(1, 1, 1, 1);
	tuple2 = Tuple_Create(1, 0, 1, 1);
	TEST_ASSERT(!Tuple_Equals(tuple1, tuple2));
}

