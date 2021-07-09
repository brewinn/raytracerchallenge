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
}
