#include "unity_fixture.h"
#include "Tuple.h"
#include "TestUtilities.h"
#include <math.h>

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
    TEST_ASSERT_FLOAT_WITHIN(1e-5, x, tuple.x);
    TEST_ASSERT_FLOAT_WITHIN(1e-5, y, tuple.y);
    TEST_ASSERT_FLOAT_WITHIN(1e-5, z, tuple.z);
    TEST_ASSERT_FLOAT_WITHIN(1e-5, w, tuple.w);
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
    AssertTuplesEqual(tuple1, tuple2);
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
    AssertTuplesEqual(tuple, Tuple_CreateVector(0, 1, 1));
}

TEST(Tuple, SubtractingAPointAndAVectorYieldsAPoint)
{
    tuple1 = Tuple_CreatePoint(1, 1, 1);
    tuple2 = Tuple_CreateVector(1, 0, 0);
    tuple = Tuple_Subtract(tuple1, tuple2);
    AssertTuplesEqual(tuple, Tuple_CreatePoint(0, 1, 1));
}

TEST(Tuple, SubtractingTwoVectorsYieldsAVector)
{
    tuple1 = Tuple_CreateVector(1, 1, 1);
    tuple2 = Tuple_CreateVector(1, 0, 0);
    tuple = Tuple_Subtract(tuple1, tuple2);
    AssertTuplesEqual(tuple, Tuple_CreateVector(0, 1, 1));
}

TEST(Tuple, SubtractingAVectorFromTheZeroVector)
{
    tuple1 = Tuple_CreateVector(0, 0, 0);
    tuple2 = Tuple_CreateVector(1, -2, 3);
    tuple = Tuple_Subtract(tuple1, tuple2);
    AssertTuplesEqual(tuple, Tuple_CreateVector(-1, 2, -3));
}

TEST(Tuple, TupleNegationNegatesComponentwise)
{
    tuple = Tuple_Negate(Tuple_Create(1, -2, 3, -4));
    AssertTupleEquals(-1, 2, -3, 4);
}

TEST(Tuple, MultiplyTupleByScalar)
{
    tuple = Tuple_Multiply(Tuple_Create(1, -2, 3, -4), 3.5);
    AssertTupleEquals(3.5, -7, 10.5, -14);
}

TEST(Tuple, DivideTupleByScalar)
{
    tuple = Tuple_Divide(Tuple_Create(1, -2, 3, -4), 2);
    AssertTupleEquals(0.5, -1, 1.5, -2);
}

TEST(Tuple, MagnitudeCalculatesVectorLength)
{
    float magnitude1, magnitude2, magnitude3;
    magnitude1 = Tuple_Magnitude(Tuple_CreateVector(1, 0, 0));
    magnitude2 = Tuple_Magnitude(Tuple_CreateVector(0, 3, 4));
    magnitude3 = Tuple_Magnitude(Tuple_CreateVector(1, 2, 2));
    TEST_ASSERT(magnitude1 == 1);
    TEST_ASSERT(magnitude2 == 5);
    TEST_ASSERT(magnitude3 == 3);
}

TEST(Tuple, NormalizeReturnsUnitVector)
{
    tuple = Tuple_Normalize(Tuple_CreateVector(2, 1, 2));
    AssertTupleEquals(2.0/3, 1.0/3, 2.0/3, 0);
}

TEST(Tuple, DotProductOfTwoTuples)
{
    tuple1 = Tuple_Create(1, 2, 3, 4);
    tuple2 = Tuple_Create(4, 3, 2, 1);
    float dotProduct = Tuple_Dot(tuple1, tuple2);
    TEST_ASSERT(dotProduct == 20);
}

TEST(Tuple, CrossProductOfTwoVectors)
{
    tuple1 = Tuple_CreateVector(1, 2, 3);
    tuple2 = Tuple_CreateVector(2, 3, 4);
    tuple = Tuple_Cross(tuple1, tuple2);
    AssertTupleEquals(-1, 2, -1, 0);
    tuple = Tuple_Cross(tuple2, tuple1);
    AssertTupleEquals(1, -2, 1, 0);
}

TEST(Tuple, ReflectingAVectorAt45Degrees)
{
    tuple1 = Tuple_CreateVector(1, -1, 0);
    tuple2 = Tuple_CreateVector(0, 1, 0);
    tuple = Tuple_Reflect(tuple1, tuple2);
    AssertTupleEquals(1, 1, 0, 0);
}

TEST(Tuple, ReflectingAVectorOffASlantedSurface)
{
    tuple1 = Tuple_CreateVector(0, -1, 0);
    float value = sqrtf(2)/2;
    tuple2 = Tuple_CreateVector(value, value, 0);
    tuple = Tuple_Reflect(tuple1, tuple2);
    AssertTupleEquals(1, 0, 0, 0);
}
