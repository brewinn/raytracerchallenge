#include "Intersection.h"
#include <stdlib.h>

typedef struct IntersectionsStruct{
	int count;
	Intersection* intersections;
} IntersectionsStruct;

Intersections Intersection_Create(int xsCount)
{
	Intersections xs = malloc(sizeof(IntersectionsStruct));
	xs->count = xsCount;
	xs->intersections = NULL;
	if(xsCount > 0)
		xs->intersections = calloc(xsCount, sizeof(Intersection));
	return xs;
}

void Intersection_Destroy(Intersections* xsPtr)
{
	if(xsPtr == NULL || *xsPtr == NULL)
		return;
	Intersections xs = *xsPtr;
	if(xs->count > 0)
		free((xs)->intersections);
	free(xs);
	*xsPtr = NULL;
}

static void CheckWithinBounds(Intersections xs, int index)
{
	if(index < 0)
		exit(-1);
	if(index > (xs->count - 1))
		exit(-1);
}

void Intersection_SetTime(Intersections xs, int index, float time)
{
	CheckWithinBounds(xs, index);
	xs->intersections[index].time = time;
}

void Intersection_SetObjectType(Intersections xs, int index, objType type)
{
	CheckWithinBounds(xs, index);
	xs->intersections[index].type = type;
}

void Intersection_SetIntersection(Intersections xs, int index, Intersection intersection)
{
	CheckWithinBounds(xs, index);
	xs->intersections[index] = intersection;
}

int Intersection_GetCount(Intersections xs)
{
	return xs->count;
}

float Intersection_GetTime(Intersections xs, int index)
{
	CheckWithinBounds(xs, index);
	return xs->intersections[index].time;
}

objType Intersection_GetObjectType(Intersections xs, int index)
{
	CheckWithinBounds(xs, index);
	return xs->intersections[index].type;
}

Intersection Intersection_GetIntersection(Intersections xs, int index)
{
	CheckWithinBounds(xs, index);
	return xs->intersections[index];
}

Intersections Intersection_Aggregate(int count, Intersection* intersections)
{
	Intersections xs = Intersection_Create(count);
	for(int k = 0; k < count; k++)
	{
		xs->intersections[k] = intersections[k];
	}
	return xs;
}

bool Intersection_Hit(Intersections xs, Intersection* hitPtr)
{
	Intersection currentHit = {-1, NONE};
	for(int k = 0; k < xs->count; k++)
	{
		float xtime = xs->intersections[k].time;
		if(xtime > 0 && (xtime < currentHit.time || currentHit.time < 0))
		{
			currentHit.time = xtime;
			currentHit.type = xs->intersections[k].type;
		}
	}

	if(currentHit.time > 0)
	{
		*hitPtr = currentHit;
		return true;
	}
	return false;

}
