#include "unity_fixture.h"

TEST_GROUP(Tuple);

TEST_SETUP(Tuple)
{
}

TEST_TEAR_DOWN(Tuple)
{
}

TEST(Tuple, Failure)
{
	TEST_FAIL_MESSAGE("Start here");
}
