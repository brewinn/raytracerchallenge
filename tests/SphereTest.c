#include "unity_fixture.h"
#include "Sphere.h"
#include "Transformations.h"
#include <math.h>

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

static Tuple pointOnSphere, expectedTuple, actualTuple;

TEST_GROUP(SphereNormals);

TEST_SETUP(SphereNormals)
{
	sphere = Sphere_Create();
}

TEST_TEAR_DOWN(SphereNormals)
{
	Sphere_Destroy(&sphere);
}

static void AssertTuplesEqual()
{
	TEST_ASSERT_FLOAT_WITHIN(1e-5, expectedTuple.x, actualTuple.x);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, expectedTuple.y, actualTuple.y);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, expectedTuple.z, actualTuple.z);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, expectedTuple.w, actualTuple.w);
}

TEST(SphereNormals, NormalAtPointOnXAxis)
{
	pointOnSphere = Tuple_CreatePoint(1, 0, 0);
	actualTuple = Sphere_NormalAt(sphere, pointOnSphere);
	expectedTuple = Tuple_CreateVector(1, 0, 0);
	AssertTuplesEqual();
}

TEST(SphereNormals, NormalAtPointOnYAxis)
{
	pointOnSphere = Tuple_CreatePoint(0, 1, 0);
	actualTuple = Sphere_NormalAt(sphere, pointOnSphere);
	expectedTuple = Tuple_CreateVector(0, 1, 0);
	AssertTuplesEqual();
}

TEST(SphereNormals, NormalAtPointOnZAxis)
{
	pointOnSphere = Tuple_CreatePoint(0, 0, 1);
	actualTuple = Sphere_NormalAt(sphere, pointOnSphere);
	expectedTuple = Tuple_CreateVector(0, 0, 1);
	AssertTuplesEqual();
}

TEST(SphereNormals, NormalAtNonaxialPoint)
{
	float value = sqrtf(3)/3;
	pointOnSphere = Tuple_CreatePoint(value, value, value);
	actualTuple = Sphere_NormalAt(sphere, pointOnSphere);
	expectedTuple = Tuple_CreateVector(value, value, value);
	AssertTuplesEqual();
}

TEST(SphereNormals, NormalIsNormalized)
{
	float value = sqrtf(3)/3;
	pointOnSphere = Tuple_CreatePoint(value, value, value);
	actualTuple = Sphere_NormalAt(sphere, pointOnSphere);
	expectedTuple = Tuple_Normalize(Tuple_CreateVector(value, value, value));
	AssertTuplesEqual();
}

TEST(SphereNormals, NormalOfTranslatedSphere)
{
	float value = sqrtf(2)/2;
	Matrix transformation = Transformation_Translation(0, 1, 0);
	Sphere_SetTransformation(sphere, transformation);
	pointOnSphere = Tuple_CreatePoint(0, 1 + value, value);
	actualTuple = Sphere_NormalAt(sphere, pointOnSphere);
	expectedTuple = Tuple_CreateVector(0, value, value);
	AssertTuplesEqual();
}

TEST(SphereNormals, NormalOfTransformedSphere)
{
	float value = sqrtf(2)/2;
	Matrix t1 = Transformation_Scale(1, 0.5, 1);
	Matrix t2 = Transformation_RotationZ(M_PI/5);
	Matrix transformation = Matrix_Multiply(t1, t2);
	Matrix_Destroy(&t1);
	Matrix_Destroy(&t2);
	Sphere_SetTransformation(sphere, transformation);
	pointOnSphere = Tuple_CreatePoint(0, value, -value);
	actualTuple = Sphere_NormalAt(sphere, pointOnSphere);
	expectedTuple = Tuple_CreateVector(0, 0.97014, -0.24254);
	AssertTuplesEqual();
}

static Matrix expectedMatrix, actualMatrix;

TEST_GROUP(SphereTransformation);

TEST_SETUP(SphereTransformation)
{
	sphere = Sphere_Create();
}

TEST_TEAR_DOWN(SphereTransformation)
{
	Sphere_Destroy(&sphere);
	Matrix_Destroy(&expectedMatrix);
}

static void AssertMatricesEqual(void)
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
		{
			float actualValue = Matrix_ValueAt(actualMatrix, i, j);
			float expectedValue = Matrix_ValueAt(expectedMatrix, i, j);
			TEST_ASSERT_EQUAL_FLOAT(expectedValue, actualValue);
		}
}

TEST(SphereTransformation, DefaultTransformationIsIdentity)
{
	expectedMatrix = Matrix_Identity(4);
	actualMatrix = Sphere_GetTransformation(sphere);
	AssertMatricesEqual();
}

TEST(SphereTransformation, CanChangeSphereTransform)
{
	Matrix transformation = Transformation_Translation(1, 2, 3);
	Sphere_SetTransformation(sphere, transformation);
	expectedMatrix = Transformation_Translation(1, 2, 3);
	actualMatrix = Sphere_GetTransformation(sphere);
	AssertMatricesEqual();
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
	xs = Sphere_Intersect(sphere, ray);
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
	xs = Sphere_Intersect(sphere, ray);
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
	xs = Sphere_Intersect(sphere, ray);
	int xsCount = Intersection_GetCount(xs);
	TEST_ASSERT_EQUAL_INT(0, xsCount);
}

TEST(SphereIntersections, RayInsideSphereIntersectsBothSides)
{
	Tuple origin = Tuple_CreatePoint(0, 0, 0);
	Ray ray = Ray_Create(origin, direction);
	xs = Sphere_Intersect(sphere, ray);
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
	xs = Sphere_Intersect(sphere, ray);
	int xsCount = Intersection_GetCount(xs);
	TEST_ASSERT_EQUAL_INT(2, xsCount);
	float xsZero = Intersection_GetTime(xs, 0);
	float xsOne = Intersection_GetTime(xs, 1);
	TEST_ASSERT_EQUAL_FLOAT(-6.0, xsZero);
	TEST_ASSERT_EQUAL_FLOAT(-4.0, xsOne);
}

TEST_GROUP(TransformedSphereIntersections);

TEST_SETUP(TransformedSphereIntersections)
{
	sphere = Sphere_Create();
}

TEST_TEAR_DOWN(TransformedSphereIntersections)
{
	Intersection_Destroy(&xs);
	Sphere_Destroy(&sphere);
}

TEST(TransformedSphereIntersections, IntersectionWithScaledSphere)
{
	Tuple origin = Tuple_CreatePoint(0, 0, -5);
	direction = Tuple_CreateVector(0, 0, 1);
	Ray ray = Ray_Create(origin, direction);
	Sphere_SetTransformation(sphere, Transformation_Scale(2, 2, 2));
	xs = Sphere_Intersect(sphere, ray);
	int xsCount = Intersection_GetCount(xs);
	TEST_ASSERT_EQUAL_INT(2, xsCount);
	float xsZero = Intersection_GetTime(xs, 0);
	float xsOne = Intersection_GetTime(xs, 1);
	TEST_ASSERT_EQUAL_FLOAT(3, xsZero);
	TEST_ASSERT_EQUAL_FLOAT(7, xsOne);
}

TEST(TransformedSphereIntersections, IntersectionWithTranslatedSphere)
{
	Tuple origin = Tuple_CreatePoint(0, 0, -5);
	direction = Tuple_CreateVector(0, 0, 1);
	Ray ray = Ray_Create(origin, direction);
	Sphere_SetTransformation(sphere, Transformation_Translation(5, 0, 0));
	xs = Sphere_Intersect(sphere, ray);
	int xsCount = Intersection_GetCount(xs);
	TEST_ASSERT_EQUAL_INT(0, xsCount);
}

TEST(TransformedSphereIntersections, IntersectionWithRotatedSphere)
{
	Tuple origin = Tuple_CreatePoint(0, 0, -5);
	direction = Tuple_CreateVector(0, 0, 1);
	Ray ray = Ray_Create(origin, direction);
	Sphere_SetTransformation(sphere, Transformation_RotationX(M_PI/2));
	xs = Sphere_Intersect(sphere, ray);
	int xsCount = Intersection_GetCount(xs);
	TEST_ASSERT_EQUAL_INT(2, xsCount);
	float xsZero = Intersection_GetTime(xs, 0);
	float xsOne = Intersection_GetTime(xs, 1);
	TEST_ASSERT_EQUAL_FLOAT(4, xsZero);
	TEST_ASSERT_EQUAL_FLOAT(6, xsOne);
}

TEST(TransformedSphereIntersections, IntersectionWithShearedSphere)
{
	Tuple origin = Tuple_CreatePoint(0, 0, -5);
	direction = Tuple_CreateVector(0, 0, 1);
	Ray ray = Ray_Create(origin, direction);
	Matrix transform = Transformation_Shear(1, 0, 0, 0, 0, 0);
	Sphere_SetTransformation(sphere, transform);
	xs = Sphere_Intersect(sphere, ray);
	int xsCount = Intersection_GetCount(xs);
	TEST_ASSERT_EQUAL_INT(2, xsCount);
	float xsZero = Intersection_GetTime(xs, 0);
	float xsOne = Intersection_GetTime(xs, 1);
	TEST_ASSERT_EQUAL_FLOAT(4, xsZero);
	TEST_ASSERT_EQUAL_FLOAT(6, xsOne);
}
