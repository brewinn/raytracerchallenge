#include "unity_fixture.h"
#include "Intersection.h"

static Intersections xs;
static int xsCount = 2;

TEST_GROUP(Intersections);

TEST_SETUP(Intersections)
{
	xs = Intersection_Create(xsCount);
}

TEST_TEAR_DOWN(Intersections)
{
	Intersection_Destroy(&xs);
}

TEST(Intersections, IntersectionsStoresIntersectionCount)
{
	int actualCount = Intersection_GetCount(xs);
	TEST_ASSERT_EQUAL_INT(xsCount, actualCount);
}

TEST(Intersections, IntersectionsStoresTimes)
{
	Intersection_SetTime(xs, 0, 0.5);
	Intersection_SetTime(xs, 1, -1.0);
	float xsZero = Intersection_GetTime(xs, 0);
	float xsOne = Intersection_GetTime(xs, 1);
	TEST_ASSERT_EQUAL_FLOAT(0.5, xsZero);
	TEST_ASSERT_EQUAL_FLOAT(-1.0, xsOne);
}

TEST(Intersections, IntersectionsStoresObjectType)
{
	Intersection_SetObjectType(xs, 0, SPHERE);
	Intersection_SetObjectType(xs, 1, SPHERE);
	objType xsZeroType = Intersection_GetObjectType(xs, 0);
	objType xsOneType = Intersection_GetObjectType(xs, 1);
	TEST_ASSERT_EQUAL_INT(SPHERE, xsZeroType);
	TEST_ASSERT_EQUAL_INT(SPHERE, xsOneType);
}

TEST(Intersections, CanSetAndReturnIntersections)
{
	Intersection x = { 
		.time = 1,
		.type = SPHERE
	};
	Intersection_SetIntersection(xs, 0, x);
	Intersection actualIntersection = Intersection_GetIntersection(xs, 0);
	TEST_ASSERT_EQUAL_FLOAT(1, actualIntersection.time);
	TEST_ASSERT_EQUAL_INT(SPHERE, actualIntersection.type);
}

TEST(Intersections, HitForTwoPositiveTimesReturnsSmallerTime)
{
	Intersection_SetTime(xs, 0, 1.0);
	Intersection_SetTime(xs, 1, 2.0);
	Intersection_SetObjectType(xs, 0, SPHERE);
	Intersection_SetObjectType(xs, 1, SPHERE);
	Intersection hit;
	Intersection_Hit(xs, &hit);
	TEST_ASSERT_EQUAL_FLOAT(1.0, hit.time);
	TEST_ASSERT_EQUAL_INT(SPHERE, hit.type);
}

TEST(Intersections, HitForOnePositiveTimeReturnsPositiveTime)
{
	Intersection_SetTime(xs, 0, -1.0);
	Intersection_SetTime(xs, 1, 1.0);
	Intersection_SetObjectType(xs, 0, SPHERE);
	Intersection_SetObjectType(xs, 1, SPHERE);
	Intersection hit;
	Intersection_Hit(xs, &hit);
	TEST_ASSERT_EQUAL_FLOAT(1.0, hit.time);
	TEST_ASSERT_EQUAL_INT(SPHERE, hit.type);
}

TEST(Intersections, HitForAllNegativeTimesReturnsFalse)
{
	Intersection_SetTime(xs, 0, -2.0);
	Intersection_SetTime(xs, 1, -1.0);
	Intersection_SetObjectType(xs, 0, SPHERE);
	Intersection_SetObjectType(xs, 1, SPHERE);
	Intersection hit;
	TEST_ASSERT_FALSE(Intersection_Hit(xs, &hit));
}

TEST_GROUP(Intersection);

TEST_SETUP(Intersection)
{
}

TEST_TEAR_DOWN(Intersection)
{
}

TEST(Intersection, IntersectionStoresTimeAndType)
{
	Intersection x = { 
		.time = 3.5,
		.type = SPHERE
	};
	TEST_ASSERT_EQUAL_FLOAT(3.5, x.time);
	TEST_ASSERT_EQUAL_INT(SPHERE, x.type);
}

TEST(Intersection, AggregateCombinesIntersectionsToIntersections)
{
	Intersection x1 = { 
		.time = 1.0,
		.type = SPHERE
	};
	Intersection x2 = { 
		.time = 2.0,
		.type = SPHERE
	};
	Intersection array[2] = {x1, x2};
	Intersections xs = Intersection_Aggregate(2, array);
	int count = Intersection_GetCount(xs);
	int xZero = Intersection_GetTime(xs,0);
	int xOne = Intersection_GetTime(xs,1);
	Intersection_Destroy(&xs);
	TEST_ASSERT_EQUAL_INT(2, count);
	TEST_ASSERT_EQUAL_FLOAT(1.0, xZero);
	TEST_ASSERT_EQUAL_FLOAT(2.0, xOne);
}

TEST(Intersection, HitAlwaysGivesLowestNonnegativeIntersection)
{
	Intersection x1 = { 
		.time = 5,
		.type = SPHERE
	};
	Intersection x2 = { 
		.time = 7,
		.type = SPHERE
	};
	Intersection x3 = { 
		.time = -3,
		.type = SPHERE
	};
	Intersection x4 = { 
		.time = 2,
		.type = SPHERE
	};
	Intersection array[4]  = {x1, x2, x3, x4};
	Intersections xs = Intersection_Aggregate(4, array);
	Intersection hit;
	Intersection_Hit(xs, &hit);
	Intersection_Destroy(&xs);
	TEST_ASSERT_EQUAL_FLOAT(2, hit.time);
	TEST_ASSERT_EQUAL_INT(SPHERE, hit.type);
}