#ifndef __INTERSECTION__
#define __INTERSECTION__

#include <stdbool.h>

typedef enum objectType{
	NONE, SPHERE
} objType;

typedef struct IntersectionsStruct* Intersections;
typedef struct Intersection{
	float time;
	enum objectType type;
} Intersection;

Intersections Intersection_Create(int xsCount);
void Intersection_Destroy(Intersections* xsPtr);
void Intersection_SetTime(Intersections xs, int index, float time);
void Intersection_SetObjectType(Intersections xs, int index, objType type);
void Intersection_SetIntersection(Intersections xs, int index, Intersection intersection);
int Intersection_GetCount(Intersections xs);
float Intersection_GetTime(Intersections xs, int index);
objType Intersection_GetObjectType(Intersections xs, int index);
Intersection Intersection_GetIntersection(Intersections xs, int index);
Intersections Intersection_Aggregate(int count, Intersection* intersections);
bool Intersection_Hit(Intersections xs, Intersection* hitPtr);

#endif /* __INTERSECTION__ */
