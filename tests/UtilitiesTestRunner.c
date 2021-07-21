#include "unity_fixture.h"

TEST_GROUP_RUNNER(Utilities)
{
	RUN_TEST_CASE(Utilities, FloatEqualsTrueForIdenticalFloats);
	RUN_TEST_CASE(Utilities, FloatEqualsFalseForDifferentFloats);
}
