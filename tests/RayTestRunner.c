#include "unity_fixture.h"

TEST_GROUP_RUNNER(Ray)
{
	RUN_TEST_CASE(Ray, RayContainsOriginPoint);
	RUN_TEST_CASE(Ray, RayContainsDirectionVector);
	RUN_TEST_CASE(Ray, RayOriginIsAPoint);
	RUN_TEST_CASE(Ray, RayDirectionIsAVector);
	RUN_TEST_CASE(Ray, PositionComputesPointAlongRay);
}
