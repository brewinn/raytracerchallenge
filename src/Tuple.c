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

bool Tuple_Equals(Tuple tuple1, Tuple tuple2)
{
	if(tuple1.x != tuple2.x)
		return false;
	if(tuple1.y != tuple2.y)
		return false;
	if(tuple1.z != tuple2.z)
		return false;
	if(tuple1.w != tuple2.w)
		return false;
	return true;
}

Tuple Tuple_Add(Tuple tuple1, Tuple tuple2)
{
	float x, y, z, w;
	x = tuple1.x + tuple2.x;
	y = tuple1.y + tuple2.y;
	z = tuple1.z + tuple2.z;
	w = tuple1.w + tuple2.w;
	return Tuple_Create(x, y, z, w);
}

Tuple Tuple_Subtract(Tuple tuple1, Tuple tuple2)
{
	float x, y, z, w;
	x = tuple1.x - tuple2.x;
	y = tuple1.y - tuple2.y;
	z = tuple1.z - tuple2.z;
	w = tuple1.w - tuple2.w;
	return Tuple_Create(x, y, z, w);
}

Tuple Tuple_Negate(Tuple tuple)
{
	return Tuple_Create(-tuple.x, 
			    -tuple.y, 
			    -tuple.z, 
			    -tuple.w);
}

Tuple Tuple_Multiply(Tuple tuple, float scalar)
{
	float x, y, z, w;
	x = tuple.x * scalar;
	y = tuple.y * scalar;
	z = tuple.z * scalar;
	w = tuple.w * scalar;
	return Tuple_Create(x, y, z, w);
}

Tuple Tuple_Divide(Tuple tuple, float scalar)
{
	float x, y, z, w;
	x = tuple.x / scalar;
	y = tuple.y / scalar;
	z = tuple.z / scalar;
	w = tuple.w / scalar;
	return Tuple_Create(x, y, z, w);
}
