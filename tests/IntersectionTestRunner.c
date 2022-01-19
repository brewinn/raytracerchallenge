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
	RUN_TEST_CASE(Intersections, HitShouldOffsetThePoint);
}

TEST_GROUP_RUNNER(Intersection)
{
	RUN_TEST_CASE(Intersection, IntersectionStoresTimeAndType);
	RUN_TEST_CASE(Intersection, AggregateCombinesIntersectionsToIntersections);
}
TEST_GROUP_RUNNER(MultipleIntersection)
{
	RUN_TEST_CASE(MultipleIntersection, HitAlwaysGivesLowestNonnegativeIntersection);
	RUN_TEST_CASE(MultipleIntersection, CombineMergesTwoIntersections);
	RUN_TEST_CASE(MultipleIntersection, SortRearrangesIntersectionsBasedOnTime);
}

TEST_GROUP_RUNNER(Computation)
{
	RUN_TEST_CASE(Computation, ComputationContainsTime);
	RUN_TEST_CASE(Computation, ComputationContainsObject);
	RUN_TEST_CASE(Computation, ComputationContainsPoint);
	RUN_TEST_CASE(Computation, ComputationContainsEyev);
	RUN_TEST_CASE(Computation, ComputationContainsNormalv);
	RUN_TEST_CASE(Computation, InsideFalseWhenIntersectionOutside);
	RUN_TEST_CASE(Computation, InsideTrueWhenIntersectionInside);
}

