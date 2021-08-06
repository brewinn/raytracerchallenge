#include "unity_fixture.h"
#include "Sphere.h"

TEST_GROUP(Sphere);

TEST_SETUP(Sphere)
{
}

TEST_TEAR_DOWN(Sphere)
{
}

TEST(Sphere, Fail)
{
	TEST_FAIL_MESSAGE("Start here");
}
