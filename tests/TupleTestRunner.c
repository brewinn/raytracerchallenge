#include "unity_fixture.h"

TEST_GROUP_RUNNER(Tuple)
{
	RUN_TEST_CASE(Tuple, TupleWithWEqualsOneIsAPoint);
	RUN_TEST_CASE(Tuple, TupleWithWEqualsZeroIsAVector);
	RUN_TEST_CASE(Tuple, PointCreatesTupleWithWEqualsOne);
	RUN_TEST_CASE(Tuple, VectorCreatesTupleWithWEqualsZero);
	RUN_TEST_CASE(Tuple, EqualsIsTrueForIdenticalTuples);
	RUN_TEST_CASE(Tuple, EqualsIsFalseForDifferentTuples);
	RUN_TEST_CASE(Tuple, TupleAdditionAddsComponentwise);
	RUN_TEST_CASE(Tuple, TupleSubtractionSubtractsComponentwise);
	RUN_TEST_CASE(Tuple, SubtractingTwoPointsYieldsAVector);
	RUN_TEST_CASE(Tuple, SubtractingAPointAndAVectorYieldsAPoint);
	RUN_TEST_CASE(Tuple, SubtractingTwoVectorsYieldsAVector);
	RUN_TEST_CASE(Tuple, SubtractingAVectorFromTheZeroVector);
	RUN_TEST_CASE(Tuple, TupleNegationNegatesComponentwise);
	RUN_TEST_CASE(Tuple, MultiplyTupleByScalar);
	RUN_TEST_CASE(Tuple, DivideTupleByScalar);
	RUN_TEST_CASE(Tuple, MagnitudeCalculatesVectorLength);
	RUN_TEST_CASE(Tuple, NormalizeReturnsUnitVector);
	RUN_TEST_CASE(Tuple, DotProductOfTwoTuples);
	RUN_TEST_CASE(Tuple, CrossProductOfTwoVectors);
	RUN_TEST_CASE(Tuple, ReflectingAVectorAt45Degrees);
	RUN_TEST_CASE(Tuple, ReflectingAVectorOffASlantedSurface);
}
