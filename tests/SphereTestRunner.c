#include "unity_fixture.h"

TEST_GROUP_RUNNER(Sphere)
{
	RUN_TEST_CASE(Sphere, SphereCreateReturnsSphere);
	RUN_TEST_CASE(Sphere, SphereReturnsUniqueID);
}

TEST_GROUP_RUNNER(SphereIntersections)
{
	RUN_TEST_CASE(SphereIntersections, RaySphereIntersectionAtTwoPoints);
	RUN_TEST_CASE(SphereIntersections, RaySphereIntersectionAtTangent);
	RUN_TEST_CASE(SphereIntersections, RayMissesSphereYieldsZeroIntersections);
	RUN_TEST_CASE(SphereIntersections, RayInsideSphereIntersectsBothSides);
	RUN_TEST_CASE(SphereIntersections, RayIntersectsSphereBehindIt);
}
