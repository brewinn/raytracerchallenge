#include "unity_fixture.h"
#include "World.h"
#include "Transformations.h"

static World world;

TEST_GROUP(World);

TEST_SETUP(World)
{
}

TEST_TEAR_DOWN(World)
{
	World_Destroy(&world);
}

TEST(World, InitializedWorldIsEmpty)
{
	world = World_Create();
	int objectCount = World_GetObjectCount(world);
	int lightCount = World_GetLightCount(world);
	TEST_ASSERT_EQUAL_INT(0, objectCount);
	TEST_ASSERT_EQUAL_INT(0, lightCount);
}

TEST(World, DefaultWorldHasPointLightAndTwoSpheres)
{
	world = World_CreateDefault();
	int objectCount = World_GetObjectCount(world);
	int lightCount = World_GetLightCount(world);
	TEST_ASSERT_EQUAL_INT(2, objectCount);
	TEST_ASSERT_EQUAL_INT(1, lightCount);
}

TEST_GROUP(DefaultWorld);

TEST_SETUP(DefaultWorld)
{
	world = World_CreateDefault();
}

TEST_TEAR_DOWN(DefaultWorld)
{
	World_Destroy(&world);
}

TEST(DefaultWorld, DefaultWorldLightHasCorrectCharacteristics)
{
	Light defaultLight = *World_GetLight(world, 0);
	Tuple lightPosition = defaultLight.position;
	Color lightIntensity = defaultLight.intensity;

	TEST_ASSERT_EQUAL_FLOAT(-10, lightPosition.x);
	TEST_ASSERT_EQUAL_FLOAT(10, lightPosition.y);
	TEST_ASSERT_EQUAL_FLOAT(-10, lightPosition.z);
	TEST_ASSERT_EQUAL_FLOAT(1, lightPosition.w);

	TEST_ASSERT_EQUAL_FLOAT(1, lightIntensity.red);
	TEST_ASSERT_EQUAL_FLOAT(1, lightIntensity.green);
	TEST_ASSERT_EQUAL_FLOAT(1, lightIntensity.blue);
}

TEST(DefaultWorld, Sphere1HasCorrectCharacteristics)
{
	Sphere sphere = World_GetObject(world, 0);
	Material actualMaterial = Sphere_GetMaterial(sphere);
	TEST_ASSERT_EQUAL_FLOAT(0.8, actualMaterial.color.red);
	TEST_ASSERT_EQUAL_FLOAT(1.0, actualMaterial.color.green);
	TEST_ASSERT_EQUAL_FLOAT(0.6, actualMaterial.color.blue);
	TEST_ASSERT_EQUAL_FLOAT(0.7, actualMaterial.diffuse);
	TEST_ASSERT_EQUAL_FLOAT(0.2, actualMaterial.specular);
}

TEST(DefaultWorld, Sphere2HasCorrectCharacteristics)
{
	Sphere sphere = World_GetObject(world, 1);
	Matrix actualTransformation = Sphere_GetTransformation(sphere);
	Matrix expectedTransformation = Transformation_Scale(0.5, 0.5, 0.5);
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
		{
			float actual = Matrix_ValueAt(actualTransformation, i , j);
			float expected = Matrix_ValueAt(expectedTransformation, i , j);
			TEST_ASSERT_EQUAL_FLOAT(expected, actual);
		}
	Matrix_Destroy(&expectedTransformation);
}

TEST(DefaultWorld, IntersectionWithRay)
{
	Ray ray = Ray_Create(
			Tuple_CreatePoint(0, 0, -5),
			Tuple_CreateVector(0, 0, 1)
			);
	Intersections xs = World_Intersect(world, ray);
	TEST_ASSERT_EQUAL_INT(4, Intersection_GetCount(xs));
	TEST_ASSERT_EQUAL_FLOAT(4, Intersection_GetTime(xs, 0));
	TEST_ASSERT_EQUAL_FLOAT(4.5, Intersection_GetTime(xs, 1));
	TEST_ASSERT_EQUAL_FLOAT(5.5, Intersection_GetTime(xs, 2));
	TEST_ASSERT_EQUAL_FLOAT(6, Intersection_GetTime(xs, 3));
	Intersection_Destroy(&xs);
}
