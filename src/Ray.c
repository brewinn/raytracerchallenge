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

Ray Ray_Transform(Ray ray, const Matrix transformation)
{
	Tuple origin = Matrix_MultiplyTuple(transformation, ray.origin);
	Tuple direction = Matrix_MultiplyTuple(transformation, ray.direction);
	return Ray_Create(origin, direction);
}
