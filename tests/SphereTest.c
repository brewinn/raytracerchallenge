#include "unity_fixture.h"
#include "Sphere.h"

static Sphere sphere;

TEST_GROUP(Sphere);

TEST_SETUP(Sphere)
{
	sphere = Sphere_Create();
}

TEST_TEAR_DOWN(Sphere)
{
	Sphere_Destroy(&sphere);
}

TEST(Sphere, SphereCreateReturnsSphere)
{
	TEST_ASSERT_NOT_NULL(sphere);
}

TEST(Sphere, SphereReturnsUniqueID)
{
	int id = Sphere_GetId(sphere);
	TEST_ASSERT_EQUAL_INT(2, id);
	Sphere_Destroy(&sphere);
	sphere = Sphere_Create();
	id = Sphere_GetId(sphere);
	TEST_ASSERT_EQUAL_INT(3, id);
}

static Tuple direction;
static Intersections xs;

TEST_GROUP(SphereIntersections);

TEST_SETUP(SphereIntersections)
{
	direction = Tuple_CreateVector(0, 0, 1);
	sphere = Sphere_Create();
}

TEST_TEAR_DOWN(SphereIntersections)
{
	Intersection_Destroy(&xs);
	Sphere_Destroy(&sphere);
}

TEST(SphereIntersections, RaySphereIntersectionAtTwoPoints)
{
	Tuple origin = Tuple_CreatePoint(0, 0, -5);
	Ray ray = Ray_Create(origin, direction);
	xs = Sphere_Intersect(ray, sphere);
	int xsCount = Intersection_GetCount(xs);
	TEST_ASSERT_EQUAL_INT(2, xsCount);
	float xsZero = Intersection_GetTime(xs, 0);
	float xsOne = Intersection_GetTime(xs, 1);
	TEST_ASSERT_EQUAL_FLOAT(4.0, xsZero);
	TEST_ASSERT_EQUAL_FLOAT(6.0, xsOne);
}

TEST(SphereIntersections, RaySphereIntersectionAtTangent)
{
	Tuple origin = Tuple_CreatePoint(0, 1, -5);
	Ray ray = Ray_Create(origin, direction);
	xs = Sphere_Intersect(ray, sphere);
	int xsCount = Intersection_GetCount(xs);
	TEST_ASSERT_EQUAL_INT(2, xsCount);
	float xsZero = Intersection_GetTime(xs, 0);
	float xsOne = Intersection_GetTime(xs, 1);
	TEST_ASSERT_EQUAL_FLOAT(5.0, xsZero);
	TEST_ASSERT_EQUAL_FLOAT(5.0, xsOne);
}

TEST(SphereIntersections, RayMissesSphereYieldsZeroIntersections)
{
	Tuple origin = Tuple_CreatePoint(0, 2, -5);
	Ray ray = Ray_Create(origin, direction);
	xs = Sphere_Intersect(ray, sphere);
	int xsCount = Intersection_GetCount(xs);
	TEST_ASSERT_EQUAL_INT(0, xsCount);
}

TEST(SphereIntersections, RayInsideSphereIntersectsBothSides)
{
	Tuple origin = Tuple_CreatePoint(0, 0, 0);
	Ray ray = Ray_Create(origin, direction);
	xs = Sphere_Intersect(ray, sphere);
	int xsCount = Intersection_GetCount(xs);
	TEST_ASSERT_EQUAL_INT(2, xsCount);
	float xsZero = Intersection_GetTime(xs, 0);
	float xsOne = Intersection_GetTime(xs, 1);
	TEST_ASSERT_EQUAL_FLOAT(-1.0, xsZero);
	TEST_ASSERT_EQUAL_FLOAT(1.0, xsOne);
}

TEST(SphereIntersections, RayIntersectsSphereBehindIt)
{
	Tuple origin = Tuple_CreatePoint(0, 0, 5);
	Ray ray = Ray_Create(origin, direction);
	xs = Sphere_Intersect(ray, sphere);
	int xsCount = Intersection_GetCount(xs);
	TEST_ASSERT_EQUAL_INT(2, xsCount);
	float xsZero = Intersection_GetTime(xs, 0);
	float xsOne = Intersection_GetTime(xs, 1);
	TEST_ASSERT_EQUAL_FLOAT(-6.0, xsZero);
	TEST_ASSERT_EQUAL_FLOAT(-4.0, xsOne);
}
