#include "Sphere.h"
#include <stdlib.h>
#include <math.h>

static int idCounter = 0;

typedef struct SphereStruct{
	int id;
} SphereStruct;

Sphere Sphere_Create(void)
{
	Sphere sphere = malloc(sizeof(SphereStruct));
	sphere->id = ++idCounter;
	return sphere;
}

void Sphere_Destroy(Sphere* spherePtr)
{
	free(*spherePtr);
	*spherePtr = NULL;
}

int Sphere_GetId(Sphere sphere)
{
	return sphere->id;
}

Intersections Sphere_Intersect(Ray ray, Sphere sphere)
{
	Tuple sphereOrigin = Tuple_CreatePoint(0, 0, 0);
	Tuple sphereToRay = Tuple_Subtract(ray.origin, sphereOrigin);

	float a = Tuple_Dot(ray.direction, ray.direction); 
	float b = 2 * Tuple_Dot(ray.direction, sphereToRay);
	float c = Tuple_Dot(sphereToRay, sphereToRay) - 1;

	float discriminant = b * b - 4 * a * c;

	if(discriminant < 0)
		return Intersection_Create(0);

	float timeOne = (-b - sqrtf(discriminant))/(2 * a);
	float timeTwo = (-b + sqrtf(discriminant))/(2 * a);

	Intersections xs = Intersection_Create(2);
	Intersection_SetTime(xs, 0, timeOne);
	Intersection_SetTime(xs, 1, timeTwo);
	return xs;
}
