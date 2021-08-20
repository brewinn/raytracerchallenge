#include "unity_fixture.h"

TEST_GROUP_RUNNER(World)
{
	RUN_TEST_CASE(World, InitializedWorldIsEmpty);
	RUN_TEST_CASE(World, DefaultWorldHasPointLightAndTwoSpheres);
}

TEST_GROUP_RUNNER(DefaultWorld)
{
	RUN_TEST_CASE(DefaultWorld, DefaultWorldLightHasCorrectCharacteristics);
	RUN_TEST_CASE(DefaultWorld, Sphere1HasCorrectCharacteristics);
	RUN_TEST_CASE(DefaultWorld, Sphere2HasCorrectCharacteristics);
	RUN_TEST_CASE(DefaultWorld, IntersectionWithRay);
}
