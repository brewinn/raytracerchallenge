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

void Intersection_SetObject(Intersections xs, int index, Sphere object)
{
	CheckWithinBounds(xs, index);
	xs->intersections[index].object = object;
}

void Intersection_SetIntersection(Intersections xs, int index, Intersection intersection)
{
	CheckWithinBounds(xs, index);
	xs->intersections[index] = intersection;
}

int Intersection_GetCount(const Intersections xs)
{
	return xs->count;
}

float Intersection_GetTime(const Intersections xs, int index)
{
	CheckWithinBounds(xs, index);
	return xs->intersections[index].time;
}

Sphere Intersection_GetObject(const Intersections xs, int index)
{
	CheckWithinBounds(xs, index);
	return xs->intersections[index].object;
}

Intersection Intersection_GetIntersection(const Intersections xs, int index)
{
	CheckWithinBounds(xs, index);
	return xs->intersections[index];
}

Intersections Intersection_Aggregate(int count, const Intersection* intersections)
{
	Intersections xs = Intersection_Create(count);
	for(int k = 0; k < count; k++)
	{
		xs->intersections[k] = intersections[k];
	}
	return xs;
}

bool Intersection_Hit(const Intersections xs, Intersection* hitPtr)
{
	Intersection currentHit = {-1, NULL};
	for(int k = 0; k < xs->count; k++)
	{
		float xtime = xs->intersections[k].time;
		if(xtime > 0 && (xtime < currentHit.time || currentHit.time < 0))
		{
			currentHit.time = xtime;
			currentHit.object = xs->intersections[k].object;
		}
	}

	if(currentHit.time > 0)
	{
		*hitPtr = currentHit;
		return true;
	}
	return false;

}

Intersections Intersection_Combine(Intersections xs1, Intersections xs2)
{
	int count1 = xs1->count;
	int count2 = xs2->count;
	if(count1 == 0)
	{
		Intersection_Destroy(&xs1);
		return xs2;
	}
	if(count2 == 0)
	{
		Intersection_Destroy(&xs2);
		return xs1;
	}
	Intersections xs = Intersection_Create(count1 + count2);
	for(int i = 0; i < xs->count; i++)
	{
		if(i < count1)
			Intersection_SetIntersection(
					xs, 
					i, 
					Intersection_GetIntersection(xs1, i)
					);
		else
			Intersection_SetIntersection(
					xs, 
					i, 
					Intersection_GetIntersection(xs2, i - count1)
					);
	}
	Intersection_Destroy(&xs1);
	Intersection_Destroy(&xs2);
	return xs;
}

static void MergeSortIntersections(int i, int j, Intersections xs, Intersections dummy)
{
	if( i >= j)
		return;

	int middle = (i+j)/2;
	MergeSortIntersections(i, middle, xs, dummy);
	MergeSortIntersections(middle + 1, j, xs, dummy);

	int leftSide = i;
	int rightSide = middle + 1;
	for(int k = i; k <= j; k++)
	{
		if(leftSide == middle + 1)
		{
			Intersection_SetIntersection(dummy, 
					k, 
					Intersection_GetIntersection(
						xs,
						rightSide
						)
					 );
			rightSide++;
		}
		else if(rightSide == j + 1)
		{
			Intersection_SetIntersection(
					dummy, 
					k, 
					Intersection_GetIntersection(
						xs,
						leftSide
						)
					);
			leftSide++;
		}
		else if(Intersection_GetTime(xs, leftSide) < Intersection_GetTime(xs, rightSide))
		{
			Intersection_SetIntersection(
					dummy, 
					k, 
					Intersection_GetIntersection(
						xs,
						leftSide
						)
					);
			leftSide++;
		}
		else{
			Intersection_SetIntersection(dummy, 
					k, 
					Intersection_GetIntersection(
						xs,
						rightSide
						)
					 );
			rightSide++;
		}
	}
	for(int k = i; k <= j; k++)
		Intersection_SetIntersection(
				xs,
				k,
				Intersection_GetIntersection(
					dummy,
					k
					)
				);
}

static void SortIntersections(Intersections xs)
{
	//Set up merge sort
	int i = 0;
	int j = xs->count - 1;
	Intersections dummy = Intersection_Create(xs->count);
	MergeSortIntersections(i, j, xs, dummy);
	Intersection_Destroy(&dummy);
}

void Intersection_Sort(Intersections xs)
{
	if(xs->count <= 1)
		return;
	SortIntersections(xs);
}
