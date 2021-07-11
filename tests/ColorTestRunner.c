#include "unity_fixture.h"

TEST_GROUP_RUNNER(Color)
{
	RUN_TEST_CASE(Color, ColorIsThreeTuple);
	RUN_TEST_CASE(Color, ColorAdditionYieldsAnotherColor);
	RUN_TEST_CASE(Color, ColorSubtractionYieldsAnotherColor);
	RUN_TEST_CASE(Color, ColorMultiplicationWithScalarYieldsAnotherColor);
}
