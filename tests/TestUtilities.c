#include "unity_fixture.h"
#include "TestUtilities.h"

void AssertTuplesEqual(Tuple expected, Tuple actual)
{
    TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.x, actual.x);
    TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.y, actual.y);
    TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.z, actual.z);
    TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.w, actual.w);
}

void AssertColorsEqual(Color expected, Color actual)
{
    TEST_ASSERT_FLOAT_WITHIN(1e-4, expected.red, actual.red);
    TEST_ASSERT_FLOAT_WITHIN(1e-4, expected.green, actual.green);
    TEST_ASSERT_FLOAT_WITHIN(1e-4, expected.blue, actual.blue);
}

void AssertRaysEqual(Ray expected, Ray actual)
{
    AssertTuplesEqual(expected.origin, actual.origin);
    AssertTuplesEqual(expected.direction, actual.direction);
}

void AssertMatricesEqual(Matrix expected, Matrix actual)
{
    int expectedRows = Matrix_GetRows(expected);
    int expectedColumns = Matrix_GetColumns(expected);
    TEST_ASSERT_EQUAL_INT(expectedColumns, Matrix_GetColumns(actual));
    TEST_ASSERT_EQUAL_INT(expectedRows, Matrix_GetRows(actual));
    for(int i = 0; i < expectedRows; i++)
        for(int j = 0; j < expectedColumns; j++)
        {
            TEST_ASSERT_FLOAT_WITHIN(1e-5, 
                    Matrix_ValueAt(expected, i, j),
                    Matrix_ValueAt(actual, i, j)
                    );
        }
}

void AssertMaterialsEqual(Material expected, Material actual)
{
    AssertColorsEqual(expected.color, actual.color);
    TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.ambient, actual.ambient);
    TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.diffuse, actual.diffuse);
    TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.specular, actual.specular);
    TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.shininess, actual.shininess);
}

void AssertLightsEqual(Light expected, Light actual)
{
    AssertTuplesEqual(expected.position, actual.position);
    AssertColorsEqual(expected.intensity, actual.intensity);
}

