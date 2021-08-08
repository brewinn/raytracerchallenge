#include "unity_fixture.h"

TEST_GROUP_RUNNER(Sphere)
{
	RUN_TEST_CASE(Sphere, SphereCreateReturnsSphere);
	RUN_TEST_CASE(Sphere, SphereReturnsUniqueID);
}

TEST_GROUP_RUNNER(SphereTransformation)
{
	RUN_TEST_CASE(SphereTransformation, DefaultTransformationIsIdentity);
	RUN_TEST_CASE(SphereTransformation, CanChangeSphereTransform);
}

TEST_GROUP_RUNNER(SphereIntersections)
{
	RUN_TEST_CASE(SphereIntersections, RaySphereIntersectionAtTwoPoints);
	RUN_TEST_CASE(SphereIntersections, RaySphereIntersectionAtTangent);
	RUN_TEST_CASE(SphereIntersections, RayMissesSphereYieldsZeroIntersections);
	RUN_TEST_CASE(SphereIntersections, RayInsideSphereIntersectsBothSides);
	RUN_TEST_CASE(SphereIntersections, RayIntersectsSphereBehindIt);
}

TEST_GROUP_RUNNER(TransformedSphereIntersections)
{
	RUN_TEST_CASE(TransformedSphereIntersections, IntersectionWithScaledSphere);
	RUN_TEST_CASE(TransformedSphereIntersections, IntersectionWithTranslatedSphere);
	RUN_TEST_CASE(TransformedSphereIntersections, IntersectionWithRotatedSphere);
	RUN_TEST_CASE(TransformedSphereIntersections, IntersectionWithShearedSphere);
}
