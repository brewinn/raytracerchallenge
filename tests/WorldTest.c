#include "unity_fixture.h"
#include "World.h"
#include "Transformations.h"
#include "TestUtilities.h"
#include <stdlib.h>
#include <stdio.h>

static World world;
static Color actualColor, expectedColor;

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

static Light* pointlight;

TEST(World, ShadeHitGivenAnIntersectionInShadow)
{
    world = World_Create();
    pointlight = Light_AllocatePointLight(
                    Tuple_CreatePoint(0, 0, -10),
                    Color_Create(1, 1, 1)
                );
    World_AddLight(world, pointlight);
    Sphere s1 = Sphere_Create();
    World_AddObject(world, s1);
    Sphere s2 = Sphere_Create();
    Matrix transform = Transformation_Translation(0, 0, 10);
    Sphere_SetTransformation(s2, transform);
    World_AddObject(world, s2);
    Ray r = Ray_Create(
                Tuple_CreatePoint(0, 0, 5),
                Tuple_CreateVector(0, 0, 1)
            );
    Intersection i = {4, s2};
    Computation comps = Intersection_PrepareComputations(i, r);
    actualColor = World_ShadeHit(world, comps);
    expectedColor = Color_Create(0.1, 0.1, 0.1);
    AssertColorsEqual(expectedColor, actualColor);
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
    Light expectedLight = Light_CreatePointLight(
            Tuple_CreatePoint(-10, 10, -10),
            Color_Create(1, 1, 1)
            );
    AssertLightsEqual(expectedLight, defaultLight);
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
    AssertMatricesEqual(expectedTransformation, actualTransformation);
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

TEST(DefaultWorld, ShadingAnExteriorIntersection)
{
    Ray ray = Ray_Create(
            Tuple_CreatePoint(0, 0, -5),
            Tuple_CreateVector(0, 0, 1)
            );
    Sphere shape = World_GetObject(world, 0);
    Intersection x = {4, shape};
    Computation comp = Intersection_PrepareComputations(x, ray);
    actualColor = World_ShadeHit(world, comp);
    expectedColor = Color_Create(0.38066, 0.47583, 0.2854959);
    AssertColorsEqual(expectedColor, actualColor);
}

TEST(DefaultWorld, ShadingAnInteriorIntersection)
{
    Light* light = World_GetLight(world, 0);
    light->position = Tuple_CreatePoint(0, 0.25, 0);
    Ray ray = Ray_Create(
            Tuple_CreatePoint(0, 0, 0),
            Tuple_CreateVector(0, 0, 1)
            );
    Sphere shape = World_GetObject(world, 1);
    Intersection x = {0.5, shape};
    Computation comp = Intersection_PrepareComputations(x, ray);
    actualColor = World_ShadeHit(world, comp);
    expectedColor = Color_Create(0.90498, 0.90498, 0.90498);
    AssertColorsEqual(expectedColor, actualColor);
}

TEST(DefaultWorld, ColorWhenRayMisses)
{
    Ray ray = Ray_Create(
            Tuple_CreatePoint(0, 0, -5),
            Tuple_CreateVector(0, 1, 0)
            );
    actualColor = World_ColorAt(world, ray);
    expectedColor = Color_Create(0, 0, 0);
    AssertColorsEqual(expectedColor, actualColor);
}

TEST(DefaultWorld, ColorWhenRayHits)
{
    Ray ray = Ray_Create(
            Tuple_CreatePoint(0, 0, -5),
            Tuple_CreateVector(0, 0, 1)
            );
    actualColor = World_ColorAt(world, ray);
    expectedColor = Color_Create(0.38066, 0.47583, 0.2854959);
    AssertColorsEqual(expectedColor, actualColor);
}

TEST(DefaultWorld, ColorWithIntersectionBehindRay)
{
    Sphere outer = World_GetObject(world, 0);
    Material outerMat = Sphere_GetMaterial(outer);
    outerMat.ambient = 1;
    Sphere_SetMaterial(outer, outerMat);
    Sphere inner = World_GetObject(world, 1);
    Material innerMat = Sphere_GetMaterial(inner);
    innerMat.ambient = 1;
    Sphere_SetMaterial(inner, innerMat);
    Ray ray = Ray_Create(
            Tuple_CreatePoint(0, 0, 0.75),
            Tuple_CreateVector(0, 0, -1)
            );
    actualColor = World_ColorAt(world, ray);
    AssertColorsEqual(innerMat.color, actualColor);
}

TEST(DefaultWorld, NoShadowWhenNothingIsCollinearWithPointAndLight)
{
    Tuple point = Tuple_CreatePoint(0, 10, 0);
    bool pointIsShadowed = World_IsShadowed(world, point);
    TEST_ASSERT_FALSE(pointIsShadowed);
}

TEST(DefaultWorld, ShadowWhenObjectBetweenThePointAndTheLight)
{
    Tuple point = Tuple_CreatePoint(10, -10, 10);
    bool pointIsShadowed = World_IsShadowed(world, point);
    TEST_ASSERT_TRUE(pointIsShadowed);
}

TEST(DefaultWorld, NoShadowWhenObjectIsBehindTheLight)
{
    Tuple point = Tuple_CreatePoint(-20, 20, -20);
    bool pointIsShadowed = World_IsShadowed(world, point);
    TEST_ASSERT_FALSE(pointIsShadowed);
}

TEST(DefaultWorld, NoShadowWhenObjectIsBehindThePoint)
{
    Tuple point = Tuple_CreatePoint(-2, 2, -2);
    bool pointIsShadowed = World_IsShadowed(world, point);
    TEST_ASSERT_FALSE(pointIsShadowed);
}
