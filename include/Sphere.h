#ifndef __SPHERE__
#define __SPHERE__

#include "Ray.h"
#include "Intersection.h"

typedef struct SphereStruct* Sphere;

Sphere Sphere_Create(void);
void Sphere_Destroy(Sphere* spherePtr);
int Sphere_GetId(Sphere sphere);
Intersections Sphere_Intersect(Ray ray, Sphere sphere);

#endif /* __SPHERE__ */
