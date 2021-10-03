#include "unity_fixture.h"
#include "Color.h"
#include "TestUtilities.h"

TEST_GROUP(Color);

static Color actual, expected;

TEST_SETUP(Color)
{
}

TEST_TEAR_DOWN(Color)
{
}

TEST(Color, ColorCreateStoresThreeTuple)
{
    actual = Color_Create(-0.5, 0.4, 1.7);
    expected = Color_Create(-0.5, 0.4, 1.7);
    AssertColorsEqual(expected, actual);
}

TEST(Color, ColorAdditionAddsComponents)
{
    actual  = Color_Add(
            Color_Create(0.9, 0.6, 0.75), 
            Color_Create(0.7, 0.1, 0.25)
            );
    expected = Color_Create(1.6, 0.7, 1.0);
    AssertColorsEqual(expected, actual);
}

TEST(Color, ColorSubtractionSubtractsComponents)
{
    actual = Color_Subtract(
            Color_Create(0.9, 0.6, 0.75), 
            Color_Create(0.7, 0.1, 0.25)
            );
    expected = Color_Create(0.2, 0.5, 0.5);
    AssertColorsEqual(expected, actual);
}

TEST(Color, ColorMultiplicationWithScalarMultipliesComponentsByScalar)
{
    actual = Color_ScalarMultiply(Color_Create(0.2, 0.3, 0.4), 2);
    expected = Color_Create(0.4, 0.6, 0.8);
    AssertColorsEqual(expected, actual);
}

TEST(Color, TwoColorMultiplicationMultipliesComponents)
{
    actual = Color_Multiply(
            Color_Create(1, 0.2, 0.4), 
            Color_Create(0.9, 1, 0.1)
            );
    expected = Color_Create(0.9, 0.2, 0.04);
    AssertColorsEqual(expected, actual);
}
