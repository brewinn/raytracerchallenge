#include "unity_fixture.h"
#include <math.h>
#include "Camera.h"

static Camera c;
TEST_GROUP(Camera);

TEST_SETUP(Camera)
{
}

TEST_TEAR_DOWN(Camera)
{
	Matrix_Destroy(&c.transform);
}

TEST(Camera, ConstructingACamera)
{
	int hsize = 160;
	int vsize = 120;
	float fieldOfView = M_PI/2;
	c = Camera_Create(hsize, vsize, fieldOfView);
	Matrix matrix = c.transform;
	TEST_ASSERT_EQUAL_INT(hsize, c.hsize);
	TEST_ASSERT_EQUAL_INT(vsize, c.vsize);
	TEST_ASSERT_EQUAL_INT(fieldOfView, c.fieldOfView);
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
		{
			float value = 0;
			if(i == j)
				value = 1;
			TEST_ASSERT_EQUAL_FLOAT(value, Matrix_ValueAt(matrix, i, j));
		}
}
