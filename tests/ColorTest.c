#include "unity_fixture.h"
#include "Color.h"

TEST_GROUP(Color);

static Color color;
static Color color1;
static Color color2;

TEST_SETUP(Color)
{
}

TEST_TEAR_DOWN(Color)
{
}

void AssertColorEquals(float red, float green, float blue)
{
	TEST_ASSERT_EQUAL_FLOAT(red, color.red);
	TEST_ASSERT_EQUAL_FLOAT(green, color.green);
	TEST_ASSERT_EQUAL_FLOAT(blue, color.blue);
}

TEST(Color, ColorCreateStoresThreeTuple)
{
	color = Color_Create(-0.5, 0.4, 1.7);
	AssertColorEquals(-0.5, 0.4, 1.7);
}

TEST(Color, ColorAdditionAddsComponents)
{
	color1 = Color_Create(0.9, 0.6, 0.75);
	color2 = Color_Create(0.7, 0.1, 0.25);
	color  = Color_Add(color1, color2);
	AssertColorEquals(1.6, 0.7, 1.0);
}

TEST(Color, ColorSubtractionSubtractsComponents)
{
	color1 = Color_Create(0.9, 0.6, 0.75);
	color2 = Color_Create(0.7, 0.1, 0.25);
	color = Color_Subtract(color1, color2);
	AssertColorEquals(0.2, 0.5, 0.5);
}

TEST(Color, ColorMultiplicationWithScalarMultipliesComponentsByScalar)
{
	color = Color_Multiply(Color_Create(0.2, 0.3, 0.4), 2);
	AssertColorEquals(0.4, 0.6, 0.8);
}
