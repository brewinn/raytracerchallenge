#include "Ray.h"

Ray Ray_Create(Tuple origin, Tuple direction)
{
	Ray ray;
	ray.origin = origin;
	ray.direction = direction;
	return ray;
}

Tuple Ray_Position(Ray ray, float time)
{
	Tuple distance = Tuple_Multiply(ray.direction, time);
	return Tuple_Add(ray.origin, distance);
}
