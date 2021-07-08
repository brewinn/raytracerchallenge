#ifndef __TUPLE__
#define __TUPLE__

typedef struct Tuple Tuple;

struct Tuple{
	float x;
	float y;
	float z;
	float w;
};

Tuple Tuple_Create(float x, float y, float z, float w);
Tuple Tuple_CreatePoint(float x, float y, float z);
Tuple Tuple_CreateVector(float x, float y, float z);

#endif /* __TUPLE__ */
