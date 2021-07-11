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

TEST(Color, ColorIsThreeTuple)
{
	color = Color_Create(-0.5, 0.4, 1.7);
	AssertColorEquals(-0.5, 0.4, 1.7);
}

TEST(Color, ColorAdditionYieldsAnotherColor)
{
	color1 = Color_Create(0.9, 0.6, 0.75);
	color2 = Color_Create(0.7, 0.1, 0.25);
	color  = Color_Add(color1, color2);
	AssertColorEquals(1.6, 0.7, 1.0);
}

TEST(Color, ColorSubtractionYieldsAnotherColor)
{
	color1 = Color_Create(0.9, 0.6, 0.75);
	color2 = Color_Create(0.7, 0.1, 0.25);
	color = Color_Subtract(color1, color2);
	AssertColorEquals(0.2, 0.5, 0.5);
}
