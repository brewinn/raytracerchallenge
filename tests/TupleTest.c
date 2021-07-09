#include "unity_fixture.h"
#include "Tuple.h"

TEST_GROUP(Tuple);

static Tuple tuple, tuple1, tuple2;

TEST_SETUP(Tuple)
{
}

TEST_TEAR_DOWN(Tuple)
{
}

static void AssertTupleEquals(float x, float y, float z, float w)
{
	TEST_ASSERT_EQUAL_FLOAT(x, tuple.x);
	TEST_ASSERT_EQUAL_FLOAT(y, tuple.y);
	TEST_ASSERT_EQUAL_FLOAT(z, tuple.z);
	TEST_ASSERT_EQUAL_FLOAT(w, tuple.w);
}

static void AssertTwoTuplesEqual(Tuple t1, Tuple t2)
{
	TEST_ASSERT(Tuple_Equals(t1, t2));
}

TEST(Tuple, TupleWithWEqualsOneIsAPoint)
{
	tuple = Tuple_Create(4.3, -4.2, 3.1, 1.0);
	AssertTupleEquals(4.3, -4.2, 3.1, 1.0);
}

TEST(Tuple, TupleWithWEqualsZeroIsAVector)
{
	tuple = Tuple_Create(4.3, -4.2, 3.1, 0.0);
	AssertTupleEquals(4.3, -4.2, 3.1, 0.0);
}

TEST(Tuple, PointCreatesTupleWithWEqualsOne)
{
	tuple = Tuple_CreatePoint(4, -4, 3);
	AssertTupleEquals(4, -4, 3, 1);
}

TEST(Tuple, VectorCreatesTupleWithWEqualsZero)
{
	tuple = Tuple_CreateVector(4, -4, 3);
	AssertTupleEquals(4, -4, 3, 0);
}

TEST(Tuple, EqualsIsTrueForIdenticalTuples)
{
	tuple1 = Tuple_Create(1, 1, 1, 1);
	tuple2 = Tuple_Create(1, 1, 1, 1);
	AssertTwoTuplesEqual(tuple1, tuple2);
}

TEST(Tuple, EqualsIsFalseForDifferentTuples)
{
	tuple1 = Tuple_Create(1, 1, 1, 1);
	tuple2 = Tuple_Create(1, 0, 1, 1);
	TEST_ASSERT(!Tuple_Equals(tuple1, tuple2));
}

TEST(Tuple, TupleAdditionAddsComponentwise)
{
	tuple1 = Tuple_Create(1, 2, 7, 1);
	tuple2 = Tuple_Create(1, 1.5, 0, -1);
	tuple = Tuple_Add(tuple1, tuple2);
	AssertTupleEquals(2, 3.5, 7, 0);
}

TEST(Tuple, TupleSubtractionSubtractsComponentwise)
{
	tuple1 = Tuple_Create(1, 2, 0, 1);
	tuple2 = Tuple_Create(1, 1.5, 7, -1);
	tuple = Tuple_Subtract(tuple1, tuple2);
	AssertTupleEquals(0, 0.5, -7, 2);
}

TEST(Tuple, SubtractingTwoPointsYieldsAVector)
{
	tuple1 = Tuple_CreatePoint(1, 1, 1);
	tuple2 = Tuple_CreatePoint(1, 0, 0);
	tuple = Tuple_Subtract(tuple1, tuple2);
	AssertTwoTuplesEqual(tuple, Tuple_CreateVector(0, 1, 1));
}

TEST(Tuple, SubtractingAPointAndAVectorYieldsAPoint)
{
	tuple1 = Tuple_CreatePoint(1, 1, 1);
	tuple2 = Tuple_CreateVector(1, 0, 0);
	tuple = Tuple_Subtract(tuple1, tuple2);
	AssertTwoTuplesEqual(tuple, Tuple_CreatePoint(0, 1, 1));
}

TEST(Tuple, SubtractingTwoVectorsYieldsAVector)
{
	tuple1 = Tuple_CreateVector(1, 1, 1);
	tuple2 = Tuple_CreateVector(1, 0, 0);
	tuple = Tuple_Subtract(tuple1, tuple2);
	AssertTwoTuplesEqual(tuple, Tuple_CreateVector(0, 1, 1));
}
