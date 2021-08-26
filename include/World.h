#ifndef __WORLD__
#define __WORLD__

#include "Sphere.h"
#include "Lights.h"
#include "Intersection.h"

typedef struct WorldStruct* World;

World World_Create(void);
void World_Destroy(World* worldPtr);
int World_GetObjectCount(const World world);
int World_GetLightCount(const World world);
World World_CreateDefault(void);
Light* World_GetLight(const World world, int index);
Sphere World_GetObject(const World world, int index);
Intersections World_Intersect(const World world, Ray ray);
Color World_ShadeHit(const World world, Computation comp);
Color World_ColorAt(const World world, Ray ray);

#endif /* __WORLD__ */
