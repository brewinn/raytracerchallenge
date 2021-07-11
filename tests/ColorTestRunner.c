#include "unity_fixture.h"

TEST_GROUP_RUNNER(Color)
{
	RUN_TEST_CASE(Color, ColorCreateStoresThreeTuple);
	RUN_TEST_CASE(Color, ColorAdditionAddsComponents);
	RUN_TEST_CASE(Color, ColorSubtractionSubtractsComponents);
	RUN_TEST_CASE(Color, ColorMultiplicationWithScalarMultipliesComponentsByScalar);
}
