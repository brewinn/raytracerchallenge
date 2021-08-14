#ifndef __SPHERE__
#define __SPHERE__

#include "Ray.h"
#include "Intersection.h"
#include "Matrix.h"

typedef struct SphereStruct* Sphere;

Sphere Sphere_Create(void);
void Sphere_Destroy(Sphere* spherePtr);
int Sphere_GetId(const Sphere sphere);
Intersections Sphere_Intersect(const Sphere sphere, Ray ray);
Matrix Sphere_GetTransformation(const Sphere sphere);
void Sphere_SetTransformation(Sphere sphere, Matrix transformation);
Tuple Sphere_NormalAt(Sphere sphere, Tuple point);


#endif /* __SPHERE__ */
