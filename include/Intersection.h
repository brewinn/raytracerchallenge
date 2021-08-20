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
int Intersection_GetCount(const Intersections xs);
float Intersection_GetTime(const Intersections xs, int index);
objType Intersection_GetObjectType(const Intersections xs, int index);
Intersection Intersection_GetIntersection(const Intersections xs, int index);
Intersections Intersection_Aggregate(int count, const Intersection* intersections);
bool Intersection_Hit(const Intersections xs, Intersection* hitPtr);
Intersections Intersection_Combine(const Intersections xs1, const Intersections xs2);
void Intersection_Sort(Intersections xs);

#endif /* __INTERSECTION__ */
