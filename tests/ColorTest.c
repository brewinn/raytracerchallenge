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

