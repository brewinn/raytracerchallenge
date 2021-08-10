#include "Canvas.h"
#include "Sphere.h"
#include "Ray.h"
#include "Intersection.h"
#include "Transformations.h"

static void CastRay(Canvas canvas, int x, int y, Sphere sphere, Ray ray, Color color)
{
	Intersections xs = Sphere_Intersect(sphere, ray);
	Intersection dummy;
	if(Intersection_Hit(xs, &dummy))
	{
		Canvas_WritePixel(canvas, x, y, color);
	}
	Intersection_Destroy(&xs);
}

static Ray CalculateRay(float worldX, float worldY, float wallZ, Tuple rayOrigin)
{
	Tuple position = Tuple_CreatePoint(worldX, worldY, wallZ);
	Tuple direction = Tuple_Normalize(Tuple_Subtract(position, rayOrigin));
	return Ray_Create(rayOrigin, direction);
}

static void CastAllRays(Canvas canvas, Sphere sphere, Tuple rayOrigin, float wallSize, float wallZ, Color color)
{
	int canvasPixels = canvas.width;
	float pixelSize = wallSize/canvasPixels;
	float half = wallSize/2;

	for(int y = 0; y < canvasPixels; y++)
	{
		float worldY = half - pixelSize * y;
		for(int x = 0; x < canvasPixels; x++)
		{
			float worldX = -half + pixelSize * x;
			Ray ray = CalculateRay(worldX, worldY, wallZ, rayOrigin);
			CastRay(canvas, x, y, sphere, ray, color);
		}
	}
}

static void CastSphere(Canvas canvas, Sphere sphere, Color color)
{
	Tuple rayOrigin = Tuple_CreatePoint(0, 0, -5);
	float wallZ = 10;
	float wallSize = 7;
	int canvasPixels = canvas.width;
	float pixelSize = wallSize/canvasPixels;
	float half = wallSize/2;

	CastAllRays(canvas, sphere, rayOrigin, wallSize, wallZ, color);
}

int main(int argc, char ** argv)
{
	int canvasPixels = 100;
	Canvas canvas = Canvas_Create(canvasPixels, canvasPixels);

	Color red = Color_Create(1, 0, 0);

	Matrix t1 = Transformation_Scale(0.5, 0.5, 0.5);
	Matrix t2 = Transformation_Shear(1, 0, 0, 0, 0, 0);
	Matrix transformation = Matrix_Multiply(t2, t1);
	Matrix_Destroy(&t1);
	Matrix_Destroy(&t2);

	Sphere sphere = Sphere_Create();
	Sphere_SetTransformation(sphere, transformation);

	CastSphere(canvas, sphere, red);

	Canvas_WriteToPPM(canvas, "sphereCast.ppm");

	Sphere_Destroy(&sphere);
	Canvas_Destroy(canvas);

	return 0;
}


