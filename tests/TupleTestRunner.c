#include "unity_fixture.h"

TEST_GROUP_RUNNER(Tuple)
{
	RUN_TEST_CASE(Tuple, TupleWithWEqualsOneIsAPoint);
	RUN_TEST_CASE(Tuple, TupleWithWEqualsZeroIsAVector);
}
