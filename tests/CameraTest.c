#include "unity_fixture.h"
#include "Camera.h"
#include "Transformations.h"
#include <math.h>

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


TEST(Camera, PixelSizeForHorizontalCanvas)
{
	int hsize = 200;
	int vsize = 125;
	float fieldOfView = M_PI/2;
	c = Camera_Create(hsize, vsize, fieldOfView);
	TEST_ASSERT_EQUAL_FLOAT(0.01, c.pixelSize);
}

TEST(Camera, PixelSizeForVerticalCanvas)
{
	int hsize = 125;
	int vsize = 200;
	float fieldOfView = M_PI/2;
	c = Camera_Create(hsize, vsize, fieldOfView);
	TEST_ASSERT_EQUAL_FLOAT(0.01, c.pixelSize);
}

TEST(Camera, ConstructingARayThroughTheCenterOfTheCanvas)
{
	int hsize = 201;
	int vsize = 101;
	float fieldOfView = M_PI/2;
	c = Camera_Create(hsize, vsize, fieldOfView);
	Ray ray = Camera_RayForPixel(c, 100, 50);

	TEST_ASSERT_FLOAT_WITHIN(1e-5, 0, ray.origin.x);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, 0, ray.origin.y);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, 0, ray.origin.z);

	TEST_ASSERT_FLOAT_WITHIN(1e-5, 0, ray.direction.x);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, 0, ray.direction.y);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, -1, ray.direction.z);
}

TEST(Camera, ConstructingARayThroughTheCornerOfTheCanvas)
{
	int hsize = 201;
	int vsize = 101;
	float fieldOfView = M_PI/2;
	c = Camera_Create(hsize, vsize, fieldOfView);
	Ray ray = Camera_RayForPixel(c, 0, 0);

	TEST_ASSERT_EQUAL_FLOAT(0, ray.origin.x);
	TEST_ASSERT_EQUAL_FLOAT(0, ray.origin.y);
	TEST_ASSERT_EQUAL_FLOAT(0, ray.origin.z);

	TEST_ASSERT_EQUAL_FLOAT(0.66519, ray.direction.x);
	TEST_ASSERT_EQUAL_FLOAT(0.33259, ray.direction.y);
	TEST_ASSERT_EQUAL_FLOAT(-0.66851, ray.direction.z);
}

TEST(Camera, ConstructingARayWhenTheCameraIsTransformed)
{
	int hsize = 201;
	int vsize = 101;
	float fieldOfView = M_PI/2;
	c = Camera_Create(hsize, vsize, fieldOfView);
	Matrix_Destroy(&c.transform);
	Matrix t1 = Transformation_RotationY(M_PI / 4);
	Matrix t2 = Transformation_Translation(0, -2, 5);
	c.transform = Matrix_Multiply(t1, t2);
	Matrix_Destroy(&t1);
	Matrix_Destroy(&t2);
	Ray ray = Camera_RayForPixel(c, 100, 50);

	TEST_ASSERT_FLOAT_WITHIN(1e-5, 0, ray.origin.x);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, 2, ray.origin.y);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, -5, ray.origin.z);

	TEST_ASSERT_FLOAT_WITHIN(1e-5, sqrtf(2)/2, ray.direction.x);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, 0, ray.direction.y);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, -sqrtf(2)/2, ray.direction.z);
}

TEST(Camera, RenderingAWorldWithACamera)
{
	World w = World_CreateDefault();
	int hsize = 11;
	int vsize = 11;
	float fieldOfView = M_PI/2;
	c = Camera_Create(hsize, vsize, fieldOfView);

	Tuple from = Tuple_CreatePoint(0, 0, -5);
	Tuple to = Tuple_CreatePoint(0, 0, 0);
	Tuple up = Tuple_CreateVector(0, 1, 0);

	Matrix_Destroy(&c.transform);
	c.transform = Transformation_ViewTransform(from, to, up);

	Canvas canvas = Camera_Render(c, w);
	World_Destroy(&w);
	Color actual = Canvas_PixelAt(canvas, 5, 5);
	Canvas_Destroy(canvas);
	Color expected = Color_Create(0.38066, 0.47583, 0.2855);


	TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.red, actual.red);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.green, actual.green);
	TEST_ASSERT_FLOAT_WITHIN(1e-5, expected.blue, actual.blue);
}
