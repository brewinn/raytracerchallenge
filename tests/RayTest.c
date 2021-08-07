#include "unity_fixture.h"
#include "Ray.h"
#include "Transformations.h"

static Tuple origin, direction;
static Ray ray;

TEST_GROUP(Ray);

TEST_SETUP(Ray)
{
	origin = Tuple_CreatePoint(2, 3, 4);
	direction = Tuple_CreateVector(1, 0, 0);
	ray = Ray_Create(origin, direction);
}

TEST_TEAR_DOWN(Ray)
{
}

TEST(Ray, RayContainsOriginPoint)
{
	TEST_ASSERT_TRUE_MESSAGE(Tuple_Equals(ray.origin, origin),"Ray origin and expected origin differ!");
}

TEST(Ray, RayContainsDirectionVector)
{
	TEST_ASSERT_TRUE_MESSAGE(Tuple_Equals(ray.direction, direction),"Ray direction and expected direction differ!");
}

TEST(Ray, RayOriginIsAPoint)
{
	bool rayOriginIsAPoint = ray.origin.w == 1;
	TEST_ASSERT_TRUE_MESSAGE(rayOriginIsAPoint, "Ray's origin is not a point!");
}

TEST(Ray, RayDirectionIsAVector)
{
	bool rayDirectionIsAVector = ray.direction.w == 0;
	TEST_ASSERT_TRUE_MESSAGE(rayDirectionIsAVector, "Ray's direction is not a vector!");
}

TEST(Ray, PositionComputesPointAlongRay)
{
	Tuple expected = Tuple_CreatePoint(2, 3, 4);
	Tuple actual = Ray_Position(ray, 0);
	TEST_ASSERT_TRUE(Tuple_Equals(expected, actual));
	expected = Tuple_CreatePoint(3, 3, 4);
	actual = Ray_Position(ray, 1);
	TEST_ASSERT_TRUE(Tuple_Equals(expected, actual));
	expected = Tuple_CreatePoint(1, 3, 4);
	actual = Ray_Position(ray, -1);
	TEST_ASSERT_TRUE(Tuple_Equals(expected, actual));
	expected = Tuple_CreatePoint(4.5, 3, 4);
	actual = Ray_Position(ray, 2.5);
	TEST_ASSERT_TRUE(Tuple_Equals(expected, actual));
}

static Matrix transformation;

TEST_GROUP(RayTransforms);

TEST_SETUP(RayTransforms)
{
	origin = Tuple_CreatePoint(1, 2, 3);
	direction = Tuple_CreateVector(0, 1, 0);
	ray = Ray_Create(origin, direction);
}

TEST_TEAR_DOWN(RayTransforms)
{
	Matrix_Destroy(&transformation);
}

TEST(RayTransforms, TransformReturnsRay)
{
	transformation = Matrix_Identity(4);
	Ray transformedRay = Ray_Transform(ray, transformation);
	Tuple expected = Tuple_CreatePoint(1, 2, 3);
	Tuple actual = transformedRay.origin;
	TEST_ASSERT_TRUE(Tuple_Equals(expected, actual));
	expected = Tuple_CreateVector(0, 1, 0);
	actual = transformedRay.direction;
	TEST_ASSERT_TRUE(Tuple_Equals(expected, actual));
}

TEST(RayTransforms, TranslationMovesRayOrigin)
{
	transformation = Transformation_Translation(3, 4, 5);
	Ray transformedRay = Ray_Transform(ray, transformation);
	Tuple expected = Tuple_CreatePoint(4, 6, 8);
	Tuple actual = transformedRay.origin;
	TEST_ASSERT_TRUE(Tuple_Equals(expected, actual));
	expected = Tuple_CreateVector(0, 1, 0);
	actual = transformedRay.direction;
	TEST_ASSERT_TRUE(Tuple_Equals(expected, actual));
}

TEST(RayTransforms, ScaleChangesBothRayOriginAndDirection)
{
	transformation = Transformation_Scale(2, 3, 4);
	Ray transformedRay = Ray_Transform(ray, transformation);
	Tuple expected = Tuple_CreatePoint(2, 6, 12);
	Tuple actual = transformedRay.origin;
	TEST_ASSERT_TRUE(Tuple_Equals(expected, actual));
	expected = Tuple_CreateVector(0, 3, 0);
	actual = transformedRay.direction;
	TEST_ASSERT_TRUE(Tuple_Equals(expected, actual));
}
