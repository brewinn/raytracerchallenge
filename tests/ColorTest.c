#include "unity_fixture.h"
#include "Color.h"

TEST_GROUP(Color);


TEST_SETUP(Color)
{
}

TEST_TEAR_DOWN(Color)
{
}

TEST(Color, ColorIsThreeTuple)
{
	Color color = Color_Create(-0.5, 0.4, 1.7);
	TEST_ASSERT_EQUAL_FLOAT(-0.5, color.red);
	TEST_ASSERT_EQUAL_FLOAT(0.4, color.green);
	TEST_ASSERT_EQUAL_FLOAT(1.7, color.blue);
}

TEST(Color, TwoColorAdditionYieldsAnotherColor)
{
	Color color1 = Color_Create(0.9, 0.6, 0.75);
	Color color2 = Color_Create(0.7, 0.1, 0.25);
	Color colorSum = Color_Add(color1, color2);
	TEST_ASSERT_EQUAL_FLOAT(1.6, colorSum.red);
	TEST_ASSERT_EQUAL_FLOAT(0.7, colorSum.green);
	TEST_ASSERT_EQUAL_FLOAT(1.0, colorSum.blue);
}
