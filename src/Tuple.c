#include "Tuple.h"

Tuple Tuple_Create(float x, float y, float z, float w)
{
	Tuple tuple = {x, y, z, w};
	return tuple;
}
