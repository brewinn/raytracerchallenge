#include "Canvas.h"
#include "Sphere.h"
#include "Ray.h"
#include "Intersection.h"
#include "Transformations.h"

static void CastRay(Canvas canvas, int x, int y, Sphere sphere, Ray ray, Light light)
{
	Intersections xs = Sphere_Intersect(sphere, ray);
	Intersection hit;
	if(Intersection_Hit(xs, &hit))
	{
		Tuple point = Ray_Position(ray, hit.time);
		Tuple normal = Sphere_NormalAt(sphere, point);
		Tuple eye = Tuple_Negate(ray.direction);
		Color color = Material_Lighting(Sphere_GetMaterial(sphere), light, point, eye, normal);
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

static void CastAllRays(Canvas canvas, Sphere sphere, Tuple rayOrigin, float wallSize, float wallZ, Light light)
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
			ray.direction = Tuple_Normalize(ray.direction);
			CastRay(canvas, x, y, sphere, ray, light);
		}
	}
}

static void CastSphere(Canvas canvas, Sphere sphere, Light light)
{
	Tuple rayOrigin = Tuple_CreatePoint(0, 0, -5);
	float wallZ = 10;
	float wallSize = 7;
	int canvasPixels = canvas.width;
	float pixelSize = wallSize/canvasPixels;
	float half = wallSize/2;

	CastAllRays(canvas, sphere, rayOrigin, wallSize, wallZ, light);
}

int main(int argc, char ** argv)
{
	int canvasPixels = 100;
	Canvas canvas = Canvas_Create(canvasPixels, canvasPixels);

	Color red = Color_Create(1, 0, 0);

	Matrix transformation = Matrix_Identity(4);

	Material sphereMaterial = Material_Create();
	sphereMaterial.color = Color_Create(1, 0.2, 1);

	Sphere sphere = Sphere_Create();
	Sphere_SetTransformation(sphere, transformation);
	Sphere_SetMaterial(sphere, sphereMaterial);

	Tuple lightPosition = Tuple_CreatePoint(-10, 10, -10);
	Color lightIntensity = Color_Create(1, 1, 1);
	Light light = Light_CreatePointLight(lightPosition, lightIntensity);

	CastSphere(canvas, sphere, light);

	Canvas_WriteToPPM(canvas, "lightSphereCast.ppm");

	Sphere_Destroy(&sphere);
	Canvas_Destroy(canvas);

	return 0;
}


