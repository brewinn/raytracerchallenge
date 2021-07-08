#include "Tuple.h"

Tuple Tuple_Create(float x, float y, float z, float w)
{
	Tuple tuple = {x, y, z, w};
	return tuple;
}

Tuple Tuple_CreatePoint(float x, float y, float z)
{
	return Tuple_Create(x, y, z, 1);
}

Tuple Tuple_CreateVector(float x, float y, float z)
{
	return Tuple_Create(x, y, z, 0);
}
