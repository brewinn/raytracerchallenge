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
	RUN_TEST_CASE(DefaultWorld, ShadingAnExteriorIntersection);
	RUN_TEST_CASE(DefaultWorld, ShadingAnInteriorIntersection);
	RUN_TEST_CASE(DefaultWorld, ColorWhenRayMisses);
	RUN_TEST_CASE(DefaultWorld, ColorWhenRayHits);
	RUN_TEST_CASE(DefaultWorld, ColorWithIntersectionBehindRay);
	RUN_TEST_CASE(DefaultWorld, NoShadowWhenNothingIsCollinearWithPointAndLight);
	RUN_TEST_CASE(DefaultWorld, ShadowWhenObjectBetweenThePointAndTheLight);
	RUN_TEST_CASE(DefaultWorld, NoShadowWhenObjectIsBehindTheLight);
	RUN_TEST_CASE(DefaultWorld, NoShadowWhenObjectIsBehindThePoint);
}
