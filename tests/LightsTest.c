#include "unity_fixture.h"
#include "Lights.h"

TEST_GROUP(Lights);

TEST_SETUP(Lights)
{
}

TEST_TEAR_DOWN(Lights)
{
}

static void AssertTuplesEqual(Tuple expected, Tuple actual)
{
	TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.x, actual.x);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.y, actual.y);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.z, actual.z);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.w, actual.w);
}

static void AssertColorsEqual(Color expected, Color actual)
{
	TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.red, actual.red);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.green, actual.green);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.blue, actual.blue);
}

TEST(Lights, PointLightHasPositionAndIntensity)
{
	Tuple position = Tuple_CreatePoint(0, 0, 0);
	Color intensity = Color_Create(1, 1, 1);
	Light pointLight = Light_CreatePointLight(position, intensity);
	AssertTuplesEqual(pointLight.position, position);
	AssertColorsEqual(pointLight.intensity, intensity);
}
