#include "unity_fixture.h"
#include "Materials.h"
#include "TestUtilities.h"
#include <math.h>

static Material material;

TEST_GROUP(Materials);

TEST_SETUP(Materials)
{
}

TEST_TEAR_DOWN(Materials)
{
}

TEST(Materials, DefaultMaterialValues)
{
    material = Material_Create();
    TEST_ASSERT_EQUAL_FLOAT(1, material.color.red);
    TEST_ASSERT_EQUAL_FLOAT(1, material.color.green);
    TEST_ASSERT_EQUAL_FLOAT(1, material.color.blue);
    TEST_ASSERT_EQUAL_FLOAT(0.1, material.ambient);
    TEST_ASSERT_EQUAL_FLOAT(0.9, material.diffuse);
    TEST_ASSERT_EQUAL_FLOAT(0.9, material.specular);
    TEST_ASSERT_EQUAL_FLOAT(200.0, material.shininess);
}

static Tuple position;

TEST_GROUP(MaterialLighting);

TEST_SETUP(MaterialLighting)
{
    material = Material_Create();
    position = Tuple_CreatePoint(0, 0, 0);
}

TEST_TEAR_DOWN(MaterialLighting)
{
}

TEST(MaterialLighting, LightingWithEyeBetweenTheLightAndTheSurface)
{
    Tuple eyev = Tuple_CreateVector(0, 0, -1);
    Tuple normalv = Tuple_CreateVector(0, 0, -1);
    Light light = Light_CreatePointLight(
            Tuple_CreatePoint(0, 0, -10),
            Color_Create(1, 1, 1)
            ); 
    bool inShadow = false;
    Color result = Material_Lighting(
            material, 
            light, 
            position, 
            eyev, 
            normalv,
            inShadow
            );
    Color expected = Color_Create(1.9, 1.9, 1.9);
    AssertColorsEqual(expected, result);
}

TEST(MaterialLighting, LightingWithTheSurfaceInShadow)
{
    Tuple eyev = Tuple_CreateVector(0, 0, -1);
    Tuple normalv = Tuple_CreateVector(0, 0, -1);
    Light light = Light_CreatePointLight(
            Tuple_CreatePoint(0, 0, -10),
            Color_Create(1, 1, 1)
            ); 
    bool inShadow = true;
    Color result = Material_Lighting(
            material, 
            light, 
            position, 
            eyev, 
            normalv,
            inShadow
            );
    Color expected = Color_Create(0.1, 0.1, 0.1);
    AssertColorsEqual(expected, result);
}

TEST(MaterialLighting, LightingWithEyeBetweenTheLightAndTheSurfaceOffset45Degrees)
{
    float value = sqrtf(2)/2;
    Tuple eyev = Tuple_CreateVector(0, value, -value);
    Tuple normalv = Tuple_CreateVector(0, 0, -1);
    Light light = Light_CreatePointLight(
            Tuple_CreatePoint(0, 0, -10),
            Color_Create(1, 1, 1)
            ); 
    bool inShadow = false;
    Color result = Material_Lighting(
            material, 
            light, 
            position, 
            eyev, 
            normalv,
            inShadow
            );
    Color expected = Color_Create(1.0, 1.0, 1.0);
    AssertColorsEqual(expected, result);
}

TEST(MaterialLighting, LightingWithEyeOppositeSurfaceAndLightOffset45Degrees)
{
    Tuple eyev = Tuple_CreateVector(0, 0, -1);
    Tuple normalv = Tuple_CreateVector(0, 0, -1);
    Light light = Light_CreatePointLight(
            Tuple_CreatePoint(0, 10, -10),
            Color_Create(1, 1, 1)
            ); 
    bool inShadow = false;
    Color result = Material_Lighting(
            material, 
            light, 
            position, 
            eyev, 
            normalv,
            inShadow
            );
    Color expected = Color_Create(0.7364, 0.7364, 0.7364);
    AssertColorsEqual(expected, result);
}

TEST(MaterialLighting, LightingWithEyeInPathOfReflectionVector)
{
    float value = sqrtf(2)/2;
    Tuple eyev = Tuple_CreateVector(0, -value, -value);
    Tuple normalv = Tuple_CreateVector(0, 0, -1);
    Light light = Light_CreatePointLight(
            Tuple_CreatePoint(0, 10, -10),
            Color_Create(1, 1, 1)
            ); 
    bool inShadow = false;
    Color result = Material_Lighting(
            material, 
            light, 
            position, 
            eyev, 
            normalv,
            inShadow
            );
    Color expected = Color_Create(1.636385, 1.636385, 1.636385);
    AssertColorsEqual(expected, result);
}

TEST(MaterialLighting, LightingWithTheLightBehindTheSurface)
{
    Tuple eyev = Tuple_CreateVector(0, 0, -1);
    Tuple normalv = Tuple_CreateVector(0, 0, -1);
    Light light = Light_CreatePointLight(
            Tuple_CreatePoint(0, 0, 10),
            Color_Create(1, 1, 1)
            ); 
    bool inShadow = false;
    Color result = Material_Lighting(
            material, 
            light, 
            position, 
            eyev, 
            normalv,
            inShadow
            );
    Color expected = Color_Create(0.1, 0.1, 0.1);
    AssertColorsEqual(expected, result);
}
