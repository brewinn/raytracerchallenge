#include "unity_fixture.h"

TEST_GROUP_RUNNER(Intersections)
{
	RUN_TEST_CASE(Intersections, IntersectionsStoresIntersectionCount);
	RUN_TEST_CASE(Intersections, IntersectionsStoresTimes);
	RUN_TEST_CASE(Intersections, IntersectionsStoresObjectType);
	RUN_TEST_CASE(Intersections, CanSetAndReturnIntersections);
	RUN_TEST_CASE(Intersections, HitForTwoPositiveTimesReturnsSmallerTime);
	RUN_TEST_CASE(Intersections, HitForOnePositiveTimeReturnsPositiveTime);
	RUN_TEST_CASE(Intersections, HitForAllNegativeTimesReturnsFalse);
}

TEST_GROUP_RUNNER(Intersection)
{
	RUN_TEST_CASE(Intersection, IntersectionStoresTimeAndType);
	RUN_TEST_CASE(Intersection, AggregateCombinesIntersectionsToIntersections);
	RUN_TEST_CASE(Intersection, HitAlwaysGivesLowestNonnegativeIntersection);
}